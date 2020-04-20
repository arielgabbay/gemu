#include "mmu.h"

#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdio.h>

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

typedef enum {
	MBC_TYPE_NONE=0,
	MBC_TYPE_MBC1=1,
	MBC_TYPE_MBC1_ERAM=2,
	MBC_TYPE_MBC1_BBERAM=3
} mbc_type_t;

static struct {
	mbc_type_t mbc_type;
	int eram_enabled;
	mbc_mode_t mbc_mode;
	int map_rom;
	int map_ram;
	uint8_t rom_bank_low;
	uint8_t rom_bank_high;
	int rom_fd;
	int sav_fd;
	uint8_t * rom_bank;
	uint8_t * ram_bank;
} mbc_state = {0};

#define MBC_TYPE_ADDR 0x147

#define RAM_ENABLE_MAGIC 0xA
#define RAM_ENABLE_MASK 0xF

#define ROM_BANK_LOW_MASK 0x1F
#define ROM_BANK_HIGH_MASK 0x3

#define RAM_ENABLE_START   0x0000
#define ROM_BANK_NUM_START 0x2000
#define ROM_BANK_SET_START 0x4000
#define ROM_RAM_MODE_START 0x6000

static uint8_t eram_banks[SIZEOF(struct gmem, eram) * 3] = {0};

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
	(void)extra;
	if (mbc_state.eram_enabled) {
		*(uint8_t *)val = mbc_state.ram_bank[addr - OFFSETOF(struct gmem, eram)];
	}
}

DEF_SPECIAL_WRITER(eram) {
	(void)extra;
	if (mbc_state.eram_enabled) {
		mbc_state.ram_bank[addr - OFFSETOF(struct gmem, eram)] = *(uint8_t *)val;
	}
}

DEF_SPECIAL_READER(rom) {
	if (IN_SECTION(addr, rom_bank)) {
		SPECIAL_READER(simple)(addr, val, size, extra);
	}
	else {
		*(uint8_t *)val = mbc_state.rom_bank[addr - OFFSETOF(struct gmem, rom_bank_2)];
	}
}

static mmu_ret_t map_banks();

DEF_SPECIAL_WRITER(rom) {
	(void)extra;
	uint8_t value = *(uint8_t *)val;
	if (addr < ROM_BANK_NUM_START) {
		if ((value & RAM_ENABLE_MASK) == RAM_ENABLE_MAGIC) {
			mbc_state.eram_enabled = 1;		
		}
		else {
			mbc_state.eram_enabled = 0;
		}
	}
	else if (addr < ROM_BANK_SET_START) {
		if (mbc_state.rom_bank_low != (value & ROM_BANK_LOW_MASK)) {
			mbc_state.rom_bank_low = value & ROM_BANK_LOW_MASK;
			if (map_banks() != MMU_SUCCESS) {
				fprintf(stderr, "ERROR: failed to map banks after rom bank change\n");
			}
		}
	}
	else if (addr < ROM_RAM_MODE_START) {
		if (mbc_state.rom_bank_high != (value & ROM_BANK_HIGH_MASK)) {
			mbc_state.rom_bank_high = value & ROM_BANK_HIGH_MASK;
			if (map_banks() != MMU_SUCCESS) {
				fprintf(stderr, "ERROR: failed to map banks after rom/ram bank change\n");
			}
		}
	}
	else {
		mbc_mode_t prev_mode = mbc_state.mbc_mode;
		if (value == 0) {
			mbc_state.mbc_mode = MBC_MODE_ROM;
		}
		else {
			mbc_state.mbc_mode = MBC_MODE_RAM;
		}
		if (prev_mode != mbc_state.mbc_mode) {
			if (map_banks() != MMU_SUCCESS) {
				fprintf(stderr, "ERROR: failed to map banks after MBC mode change\n");
			}
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

static mmu_ret_t map_banks() {
	uint32_t rom_offs = mbc_state.rom_bank_high << 5;
	uint32_t ram_offs = 0;
	if (mbc_state.mbc_mode == MBC_MODE_ROM) {
		rom_offs |= mbc_state.rom_bank_low;
	}
	else {
		ram_offs = mbc_state.rom_bank_high * sizeof(gmem.eram);
	}
	if ((mbc_state.rom_bank_low % 0x20) == 0) {
		rom_offs++;
	}
	rom_offs *= sizeof(gmem.rom_bank_2);
	if (mbc_state.mbc_type == MBC_TYPE_NONE) {
		if (mbc_state.rom_bank) {
			return MMU_SUCCESS;
		}
		rom_offs = OFFSETOF(struct gmem, rom_bank_2);
	}
	// Map ROM bank
	if (mbc_state.map_rom) {
		// Map ROM to file
		if (mbc_state.rom_bank != NULL) {
			munmap(mbc_state.rom_bank, sizeof(gmem.rom_bank_2));
		}
		mbc_state.rom_bank = mmap(NULL, sizeof(gmem.rom_bank_2), PROT_READ, MAP_PRIVATE, mbc_state.rom_fd, rom_offs);
		if (mbc_state.rom_bank == (void *)-1) {
			return MMU_FAILURE;
		}
	}
	else {
		// Read ROM from file
		if (lseek(mbc_state.rom_fd, rom_offs, SEEK_SET) != rom_offs) {
			return MMU_FAILURE;
		}
		if (read(mbc_state.rom_fd, gmem.rom_bank_2, sizeof(gmem.rom_bank_2)) != sizeof(gmem.rom_bank_2)) {
			return MMU_FAILURE;
		}
	}
	// Map ERAM bank
	if (mbc_state.mbc_type != MBC_TYPE_NONE && mbc_state.mbc_type != MBC_TYPE_MBC1) {
		if (mbc_state.map_ram && mbc_state.mbc_type == MBC_TYPE_MBC1_BBERAM) {
			// Map ERAM to save file
			if (mbc_state.ram_bank != NULL) {
				munmap(mbc_state.ram_bank, sizeof(gmem.eram));
			}
			mbc_state.ram_bank = mmap(NULL, sizeof(gmem.eram), PROT_READ | PROT_WRITE, MAP_SHARED, mbc_state.sav_fd, ram_offs);
			if (mbc_state.ram_bank == (void *)-1) {
				return MMU_FAILURE;
			}
		}
		else {
			// Map ERAM to data
			if (ram_offs == 0) {
				mbc_state.ram_bank = gmem.eram;
			}
			else {
				mbc_state.ram_bank = &eram_banks[ram_offs - sizeof(gmem.eram)];
			}
		}
	}
	return MMU_SUCCESS;
}

mmu_ret_t init_mmu(int boot_rom_fd, int rom_fd, int sav_fd) {
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
	mbc_state.mbc_type = (mbc_type_t)gmem.rom_bank[MBC_TYPE_ADDR];
	// Map/read second ROM bank from rom_fd and save file from sav_fd (if given)
	if ((sizeof(gmem.rom_bank_2) % sysconf(_SC_PAGE_SIZE)) == 0) {
		mbc_state.map_rom = 1;
	}
	else {
		mbc_state.rom_bank = gmem.rom_bank_2;
	}
	if ((sizeof(gmem.eram) % sysconf(_SC_PAGE_SIZE)) == 0 && sav_fd >= 0) {
		mbc_state.map_ram = 1;
	}
	mbc_state.sav_fd = sav_fd;
	ret = map_banks();
cleanup:
	return ret;
}

