#ifndef __GEMU_MMU_H
#define __GEMU_MMU_H

#include <stdint.h>

typedef uint16_t ea_t;

#define BOOT_ROM_SIZE 0x100

#pragma pack(push, 1)

struct ioregs {
	union {
		struct {
			uint8_t stuff1[0x50];
			uint8_t ext_rom_page;
			uint8_t stuff2[0x2F];
		};
		uint8_t flat[0x80];
	};
};

struct gmem {
	union {
		struct {
			uint8_t rom_bank[0x4000];
			uint8_t rom_bank_2[0x4000];
			uint8_t vram[0x2000];
			uint8_t eram[0x2000];
			uint8_t wram[0x2000];
			uint8_t wram_bac[0x1E00];
			uint8_t oam[0xA0];
			uint8_t non_1[0x60];
			struct ioregs ioregs;
			uint8_t non_2[0x7F];
			uint8_t intr_reg;
		};
		uint8_t flat[0x10000];
	};
	uint8_t boot[BOOT_ROM_SIZE];
};

#pragma pack(pop)

uint8_t read8(ea_t);
void write8(ea_t, uint8_t);
uint16_t read16(ea_t);
void write16(ea_t, uint16_t);
void init_gmem(uint8_t * boot_rom);

#endif /* __GEMU_MMU_H */

