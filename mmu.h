#ifndef __GEMU_MMU_H
#define __GEMU_MMU_H

struct __attribute__((__packed__)) gmem {
	uint8_t rom_bank[0x4000];
	uint8_t rom_bank_2[0x4000];
	uint8_t vram[0x2000];
	uint8_t eram[0x2000];
	uint8_t wram[0x2000];
	uint8_t ram_bac[0x1E00];
	uint8_t oam[0xA0];
	uint8_t non_1[0x60];
	uint8_t io[0x80];
	uint8_t non_2[0x7F];
	uint8_t intr_reg;
};

uint8_t read8();
void write8(uint8_t);

#endif /* __GEMU_MMU_H */

