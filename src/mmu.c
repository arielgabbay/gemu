#include "mmu.h"

#include <string.h>
#include <unistd.h>

#include "input.h"

#define IN_SECTION(addr, section) (addr >= OFFSETOF(struct gmem, section) && addr < OFFSETOF(struct gmem, section) + sizeof(gmem.section))
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))

#define INTERNAL_ROM_START 0

struct gmem gmem = {0};

struct special_addr {
	ea_t addr;
	size_t size;
	void (*reader)(ea_t, void * res, size_t size);
	void (*writer)(ea_t, void * val, size_t size);
};

struct special_addr special_addrs[] = {
	{OFFSETOF(struct gmem, ioregs._ioregs.joyp), sizeof(struct joyp), read_joyp, write_joyp}
};

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

uint8_t read8(ea_t addr) {
	struct special_addr * special = NULL;
	// TODO: consider making this a special addr
	if (IN_SECTION(addr, wram_bac)) {
		addr -= sizeof(gmem.wram);
	}
	if (!gmem.ioregs._ioregs.ext_rom_page && addr < INTERNAL_ROM_START + sizeof(gmem.boot)) {
		return gmem.boot[addr];
	}
	special = check_special_addr(addr);
	if (special != NULL) {
		uint8_t res = 0;
		special->reader(addr, &res, sizeof(res));
		return res;
	}
	return gmem.flat[addr];
}

uint8_t read8_inst(ea_t addr) {
	if (!gmem.ioregs._ioregs.ext_rom_page && addr >= INTERNAL_ROM_START + sizeof(gmem.boot)) {
		gmem.ioregs._ioregs.ext_rom_page = 1;
	}
	return read8(addr);
}

void write8(ea_t addr, uint8_t val) {
	struct special_addr * special = NULL;
	// TODO: consider making this a special addr
	if (IN_SECTION(addr, wram_bac)) {
		return;
	}
	special = check_special_addr(addr);
	if (special != NULL) {
		special->writer(addr, &val, sizeof(val));
	}
	else {
		gmem.flat[addr] = val;
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
	// Read ROM from rom_fd
	if (read(rom_fd, gmem.rom_bank, sizeof(gmem.rom_bank)) < 0) {
		goto cleanup;
	}
	if (read(rom_fd, gmem.rom_bank_2, sizeof(gmem.rom_bank_2)) < 0) {
		goto cleanup;
	}
	ret = MMU_SUCCESS;
cleanup:
	return ret;
}

