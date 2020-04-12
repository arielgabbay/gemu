#include "mmu.h"

#include <string.h>
#include <unistd.h>

#define IN_SECTION(addr, section) (addr >= OFFSETOF(struct gmem, section) && addr < OFFSETOF(struct gmem, section) + sizeof(gmem.section))

#define INTERNAL_ROM_START 0

struct gmem gmem = {0};

uint8_t read8(ea_t addr) {
	if (IN_SECTION(addr, wram_bac)) {
		addr -= sizeof(gmem.wram);
	}
	if (!gmem.ioregs._ioregs.ext_rom_page && addr < INTERNAL_ROM_START + sizeof(gmem.boot)) {
		return gmem.boot[addr];
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
	if (IN_SECTION(addr, wram_bac)) {
		return;
	}
	gmem.flat[addr] = val;
}

uint16_t read16(ea_t addr) {
	return read8(addr) + (read8(addr + 1) << 8);
}

void write16(ea_t addr, uint16_t val) {
	write8(addr, val & 0xFF);
	write8(addr + 1, val >> 8);
}

mmu_ret_t init_mmu(int boot_rom_fd, int rom_fd) {
	off_t fsize = 0;
	mmu_ret_t ret = MMU_FAILURE;
	memset(&gmem, 0, sizeof(gmem));
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
	if (read(rom_fd, gmem.rom_bank, sizeof(gmem.rom_bank) < 0)) {
		goto cleanup;
	}
	if (read(rom_fd, gmem.rom_bank_2, sizeof(gmem.rom_bank_2) < 0)) {
		goto cleanup;
	}
	ret = MMU_SUCCESS;
cleanup:
	return ret;
}

