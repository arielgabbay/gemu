#include "mmu.h"

#include <string.h>
#include <unistd.h>
#include <sys/mman.h>

#include "input.h"

#define IN_SECTION(addr, section) (addr >= OFFSETOF(struct gmem, section) && addr < OFFSETOF(struct gmem, section) + sizeof(gmem.section))
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))

#define INTERNAL_ROM_START 0

#define LCDSTAT_MASK 0xF8

static struct gmem gmem = {0};

typedef enum {
	MBC_MODE_ROM=0,
	MBC_MODE_RAM=1
} mbc_mode_t;

static struct {
	int eram_enabled;
	mbc_mode_t mbc_mode;
	int map_banks;
	uint8_t rom_bank_low;
	uint8_t rom_bank_high;
	int rom_fd;
	uint8_t * curr_bank;
} mbc_state = {0};

#define RAM_ENABLE_MAGIC 0xA
#define RAM_ENABLE_START   0x0000
#define ROM_BANK_NUM_START 0x2000
#define ROM_BANK_SET_START 0x4000
#define ROM_RAM_MODE_START 0x6000

struct special_addr {
	ea_t addr;
	size_t size;
	void (*reader)(ea_t, void *, size_t, uint8_t);
	void (*writer)(ea_t, void *, size_t, uint8_t);
	uint8_t extra;
};

#define SPECIAL_READER(name) read_##name
#define DEF_SPECIAL_READER(name) static void SPECIAL_READER(name)(ea_t addr, void * val, size_t size, uint8_t extra)

#define SPECIAL_WRITER(name) write_##name
#define DEF_SPECIAL_WRITER(name) static void SPECIAL_WRITER(name)(ea_t addr, void * val, size_t size, uint8_t extra)

// For reading/writing to registers which aren't all writable.
DEF_SPECIAL_READER(masked);
DEF_SPECIAL_WRITER(masked);

// For reading/writing from the working RAM shadow.
DEF_SPECIAL_READER(wram_bac);
DEF_SPECIAL_WRITER(wram_bac);

// For writing to ROM addresses (MBC). The reading function simple_reads, so read8 has to handle
//     boot ROM addressing.
DEF_SPECIAL_READER(rom);
DEF_SPECIAL_WRITER(rom);

// For reading/writing from the external RAM (which may be disabled).
DEF_SPECIAL_READER(eram);
DEF_SPECIAL_WRITER(eram);

// Currently we assume that only read8/write8 invoke special readers/writers, so these functions
//     can rely on the values to read/write being bytes.
struct special_addr special_addrs[] = {
	{OFFSETOF(struct gmem, ioregs._ioregs.joyp), sizeof(struct joyp), SPECIAL_READER(joyp), SPECIAL_WRITER(joyp), 0},
	{OFFSETOF(struct gmem, ioregs._ioregs.lcdstat), sizeof(struct lcdstat), SPECIAL_READER(masked), SPECIAL_WRITER(masked), LCDSTAT_MASK},
	{OFFSETOF(struct gmem, ioregs._ioregs.oam_dma), SIZEOF(struct gmem, ioregs._ioregs.oam_dma), SPECIAL_READER(masked), SPECIAL_WRITER(oam_dma), 0},
	{OFFSETOF(struct gmem, wram_bac), SIZEOF(struct gmem, wram_bac), SPECIAL_READER(wram_bac), SPECIAL_WRITER(wram_bac), 0},
	{OFFSETOF(struct gmem, rom_bank), SIZEOF(struct gmem, rom_bank) + SIZEOF(struct gmem, rom_bank_2), SPECIAL_READER(rom), SPECIAL_WRITER(rom), 0},
	{OFFSETOF(struct gmem, eram), SIZEOF(struct gmem, eram), SPECIAL_READER(eram), SPECIAL_WRITER(eram), 0}
};

DEF_SPECIAL_READER(simple) {
	(void)extra;
	*(uint8_t *)val = read8_simple(addr);
}

DEF_SPECIAL_WRITER(simple) {
	(void)extra;
	gmem.flat[addr] = *(uint8_t *)val;
}

DEF_SPECIAL_READER(masked) {
	SPECIAL_READER(simple)(addr, val, size, extra);
}

DEF_SPECIAL_WRITER(masked) {
	gmem.flat[addr] = (gmem.flat[addr] & (~extra)) | ((*(uint8_t *)val) & extra);
}

DEF_SPECIAL_READER(wram_bac) {
	(void)extra;
	*(uint8_t *)val = read8_simple(addr - SIZEOF(struct gmem, wram));
}

DEF_SPECIAL_WRITER(wram_bac) {}

DEF_SPECIAL_READER(eram) {
	if (mbc_state.eram_enabled) {
		SPECIAL_READER(simple)(addr, val, size, extra);
	}
}

DEF_SPECIAL_WRITER(eram) {
	if (mbc_state.eram_enabled) {
		SPECIAL_WRITER(simple)(addr, val, size, extra);
	}
}

DEF_SPECIAL_READER(rom) {
	if (IN_SECTION(addr, rom_bank)) {
		SPECIAL_READER(simple)(addr, val, size, extra);
	}
	else {
		*(uint8_t *)val = mbc_state.curr_bank[addr - OFFSETOF(struct gmem, rom_bank_2)];
	}
}

static mmu_ret_t map_bank();

DEF_SPECIAL_WRITER(rom) {
	(void)extra;
	uint8_t value = *(uint8_t *)val;
	if (addr < ROM_BANK_NUM_START) {
		if (value == RAM_ENABLE_MAGIC) {
			mbc_state.eram_enabled = 1;		
		}
		else {
			mbc_state.eram_enabled = 0;
		}
	}
	else if (addr < ROM_BANK_SET_START) {
		if (mbc_state.rom_bank_low != value) {
			mbc_state.rom_bank_low = value;
			map_bank();
		}
	}
	else if (addr < ROM_RAM_MODE_START) {
		if (mbc_state.mbc_mode == MBC_MODE_ROM) {
			
		}
		else {

		}
	}
	else {
		if (value == 0) {
			mbc_state.mbc_mode = MBC_MODE_ROM;
		}
		else {
			mbc_state.mbc_mode = MBC_MODE_RAM;
		}
	}
}

struct special_addr * check_special_addr(ea_t addr) {
	struct special_addr * curr = NULL;
	for (int i = 0; i < ARRAY_SIZE(special_addrs); i++) {
		curr = &special_addrs[i];
		if (curr->addr <= addr && addr < curr->addr + curr->size) {
			return curr;
		}
	}
	return NULL;
}

uint8_t read8_simple(ea_t addr) {
	return gmem.flat[addr];
}

uint8_t read8(ea_t addr) {
	struct special_addr * special = NULL;
	if (!gmem.ioregs._ioregs.ext_rom_page && addr < INTERNAL_ROM_START + sizeof(gmem.boot)) {
		return gmem.boot[addr];
	}
	special = check_special_addr(addr);
	if (special != NULL) {
		uint8_t res = 0;
		special->reader(addr, &res, sizeof(res), special->extra);
		return res;
	}
	return read8_simple(addr);
}

uint8_t read8_inst(ea_t addr) {
	if (!gmem.ioregs._ioregs.ext_rom_page && addr >= INTERNAL_ROM_START + sizeof(gmem.boot)) {
		gmem.ioregs._ioregs.ext_rom_page = 1;
	}
	return read8(addr);
}

void write8_simple(ea_t addr, uint8_t val) {
	gmem.flat[addr] = val;
}

void write8(ea_t addr, uint8_t val) {
	struct special_addr * special = check_special_addr(addr);
	if (special != NULL) {
		special->writer(addr, &val, sizeof(val), special->extra);
	}
	else {
		write8_simple(addr, val);
	}
}

uint16_t read16(ea_t addr) {
	return read8(addr) + (read8(addr + 1) << 8);
}

void write16(ea_t addr, uint16_t val) {
	write8(addr, val & 0xFF);
	write8(addr + 1, val >> 8);
}

struct sprite * get_sprite(uint8_t idx) {
	if (idx >= SIZEOF(struct oam, sprites) / sizeof(struct sprite)) {
		return NULL;
	}
	return (struct sprite *)((char *)&gmem._oam + OFFSETOF(struct oam, sprites) + idx * sizeof(struct sprite));
}

static mmu_ret_t map_bank() {
	uint32_t bank_offs = (mbc_state.rom_bank_high << 5) | mbc_state.rom_bank_low;
	if (mbc_state.rom_bank_low == 0) {
		bank_offs++;
	}
	if ((bank_offs % 0x20) == 0) {
		return MMU_FAILURE;
	}
	bank_offs *= sizeof(gmem.rom_bank_2);
	if (mbc_state.map_banks) {
		if (mbc_state.curr_bank != NULL) {
			munmap(mbc_state.curr_bank, sizeof(gmem.rom_bank_2));
		}
		mbc_state.curr_bank = mmap(NULL, sizeof(gmem.rom_bank_2), PROT_READ, MAP_PRIVATE, mbc_state.rom_fd, bank_offs);
		if (mbc_state.curr_bank == (void *)-1) {
			return MMU_FAILURE;
		}
	}
	else {
		if (lseek(mbc_state.rom_fd, bank_offs, SEEK_SET) != bank_offs) {
			return MMU_FAILURE;
		}
		if (read(mbc_state.rom_fd, gmem.rom_bank_2, sizeof(gmem.rom_bank_2)) != sizeof(gmem.rom_bank_2)) {
			return MMU_FAILURE;
		}
	}
	return MMU_SUCCESS;
}

mmu_ret_t init_mmu(int boot_rom_fd, int rom_fd) {
	off_t fsize = 0;
	mmu_ret_t ret = MMU_FAILURE;
	memset(&gmem, 0, sizeof(gmem));
	// Read BOOT rom from boot_rom_fd
	fsize = lseek(boot_rom_fd, 0, SEEK_END);
	if (fsize > BOOT_ROM_SIZE || fsize <= 0) {
		goto cleanup;
	}
	if (lseek(boot_rom_fd, 0, SEEK_SET) != 0) {
		goto cleanup;
	}
	if (read(boot_rom_fd, gmem.boot, fsize) < 1) {
		goto cleanup;
	}
	// Read first ROM bank from rom_fd
	if (read(rom_fd, gmem.rom_bank, sizeof(gmem.rom_bank)) < 0) {
		goto cleanup;
	}
	mbc_state.rom_fd = rom_fd;
	// Map/read second ROM bank from rom_fd
	if ((sizeof(gmem.rom_bank_2) % sysconf(_SC_PAGE_SIZE)) == 0) {
		mbc_state.map_banks = 1;
	}
	else {
		mbc_state.curr_bank = gmem.rom_bank_2;
	}
	ret = map_bank();
cleanup:
	return ret;
}

