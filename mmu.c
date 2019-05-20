#include <string.h>

#include "mmu.h"

#define OFFSETOF(type, field) ((unsigned long)&(((type *)0)->field))
#define IN_SECTION(addr, section) (addr >= OFFSETOF(struct gmem, section) && addr < OFFSETOF(struct gmem, section) + sizeof(gmem.section))

#define INTERNAL_ROM_START 0

struct gmem gmem = {0};

uint8_t read8(ea_t addr) {
	if (IN_SECTION(addr, wram_bac)) {
		addr -= sizeof(gmem.wram);
	}
	if (INTERNAL_ROM_START <= addr && addr < INTERNAL_ROM_START + sizeof(gmem.boot) && \
	    !gmem.ioregs.ext_rom_page) {
		return gmem.boot[addr];
	}
	return gmem.flat[addr];
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

void init_gmem(uint8_t * boot_rom) {
	memcpy(gmem.boot, boot_rom, BOOT_ROM_SIZE);
	memset(&gmem, 0, sizeof(gmem));
}

