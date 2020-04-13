#ifndef __GEMU_MMU_H
#define __GEMU_MMU_H

#include <stdint.h>
#include <assert.h>

#include "gpu.h"

typedef uint16_t ea_t;

typedef enum {
	MMU_SUCCESS=0,
	MMU_FAILURE,
} mmu_ret_t;

#define BOOT_ROM_SIZE 0x100

#pragma pack(push, 1)

struct lcdc {
	uint8_t bg_enable:1;
	uint8_t obj_enable:1;
	uint8_t obj_size:1;
	uint8_t bg_set:1;
	uint8_t bg_tile_set:1;
	uint8_t window_enable:1;
	uint8_t window_tile_set:1;
	uint8_t lcd_enable:1;
};

struct lcdstat {
	uint8_t mode:2;
	uint8_t lyc_flag:1;
	uint8_t hblank_intr:1;
	uint8_t vblank_intr:1;
	uint8_t oam_intr:1;
	uint8_t lyc_intr:1;
};

struct _ioregs {
	uint8_t stuff1[0x40];
	union {               /* FF40 */
		uint8_t lcdc;
		struct lcdc _lcdc;
	};
	union {               /* FF41 */
		uint8_t lcdstat;
		struct lcdstat _lcdstat;
	};
	uint8_t scy;          /* FF42 */
	uint8_t scx;
	uint8_t ly;
	uint8_t lyc;
	uint8_t unk1;         /* FF46 */
	uint8_t bgp;
	uint8_t stuff2[2];
	uint8_t wy;           /* FF4A */
	uint8_t wx;
	uint8_t stuff3[4];
	uint8_t ext_rom_page; /* FF50 */
	uint8_t stuff4[0x2F];
};

#define DEF_FLAT(st) \
	struct st { \
		union { \
			struct _##st _##st; \
			uint8_t flat[sizeof(struct _##st)]; \
		}; \
	} \

DEF_FLAT(ioregs);

struct gmem {
	union {
		struct {
			uint8_t rom_bank[0x4000];   /* 0000 -  4000 */
			uint8_t rom_bank_2[0x4000]; /* 4000 -  8000 */
			uint8_t vram[0x2000];       /* 8000 -  A000 */
			uint8_t eram[0x2000];       /* A000 -  C000 */
			uint8_t wram[0x2000];       /* C000 -  E000 */
			uint8_t wram_bac[0x1E00];   /* E000 -  FE00 */
			uint8_t oam[0xA0];          /* FE00 -  FEA0 */
			uint8_t non_1[0x60];        /* FEA0 -  FF00 */
			struct ioregs ioregs;       /* FF00 -  FF80 */
			uint8_t non_2[0x7F];        /* FF80 -  FFFF */
			uint8_t intr_reg;           /* FFFF - 10000 */
		};
		uint8_t flat[0x10000];
		struct {
			uint8_t vram_off[0x8000];
			struct vram _vram;
			uint8_t oam_off[0x5E00];
			struct oam _oam;
		};
	};
	uint8_t boot[BOOT_ROM_SIZE];
};

#pragma pack(pop)

#define OFFSETOF(type, field) ((unsigned long)&(((type *)0)->field))
#define SIZEOF(type, field) (sizeof(((type *)0)->field))

uint8_t read8(ea_t);
uint8_t read8_inst(ea_t);
void write8(ea_t, uint8_t);
uint16_t read16(ea_t);
void write16(ea_t, uint16_t);
mmu_ret_t init_mmu(int boot_rom_fd, int rom_fd);

#define read8_from_section(addr, section) (read8(OFFSETOF(struct gmem, section) + addr))
#define read16_from_section(addr, section) (read16(OFFSETOF(struct gmem, section) + addr))

#define read8_ioreg(reg) (read8(OFFSETOF(struct gmem, ioregs._ioregs.reg)))
#define write8_ioreg(reg, val) (write8(OFFSETOF(struct gmem, ioregs._ioregs.reg), val))

#define read_ioreg_bits(reg, field) \
	({ \
		struct reg temp_##reg = {0}; \
		*(uint8_t *)&temp_##reg = read8_ioreg(reg); \
		temp_##reg.field; \
	})
#define write_ioreg_bits(reg, field, val) \
	({ \
		struct reg temp_##reg = {0}; \
		temp_##reg.field = val; \
		write8_ioreg(reg, *(uint8_t *)&temp_##reg); \
	})

static_assert(SIZEOF(struct gmem, vram) == SIZEOF(struct gmem, _vram),
	      "Conflicting sizes for GPU- and MMU-defined VRAMs.");
static_assert(SIZEOF(struct gmem, oam) == SIZEOF(struct gmem, _oam),
	      "Conflicting sizes for GPU- and MMU-defined OAMs.");
static_assert(sizeof(struct lcdc) == sizeof(uint8_t),
	      "struct lcdc's size is not 8");

#endif /* __GEMU_MMU_H */

