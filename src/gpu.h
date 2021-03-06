#ifndef __GEMU_GPU_H
#define __GEMU_GPU_H

#include <stdint.h>
#include <stdlib.h>

typedef enum {
	GPU_SUCCESS=0,
	GPU_FAILURE,
} gpu_ret_t;

#define TILE_LENGTH 8
#define TILESET_SIZE 0x80
#define TILEMAP_SIZE (32 * 32)

#define NUM_OF_SPRITES 40

struct vram {
	uint16_t tileset1_0[TILESET_SIZE * TILE_LENGTH];
	union {
		uint16_t tileset1_1[TILESET_SIZE * TILE_LENGTH];
		uint16_t tileset0_1[TILESET_SIZE * TILE_LENGTH];
	};
	uint16_t tileset0_0[TILESET_SIZE * TILE_LENGTH];
	uint8_t tilemap0[TILEMAP_SIZE];
	uint8_t tilemap1[TILEMAP_SIZE];
};

struct sprite {
	uint8_t y;  // real y is y + 16
	uint8_t x;  // real x is x + 8
	uint8_t tile;
	union {
		uint8_t opts;
		struct {
			uint8_t nothing:3;
			uint8_t tile_set:1;
			uint8_t palette:1;
			uint8_t h_flip:1;
			uint8_t v_flip:1;
			uint8_t bg:1;
		};
	};
};

struct oam {
	struct sprite sprites[NUM_OF_SPRITES];
};

gpu_ret_t init_gpu(const char *);
void exit_gpu();

void write_oam_dma(uint16_t, void *, size_t, uint8_t);
void read_lcdstat(uint16_t, void *, size_t, uint8_t);
void write_lcdstat(uint16_t, void *, size_t, uint8_t);

void gpu_step(uint8_t);

#endif

