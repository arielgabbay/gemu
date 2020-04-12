#ifndef __GEMU_GPU_H
#define __GEMU_GPU_H

#include <stdint.h>

#define TILE_LENGTH 8
#define TILESET_SIZE 0x80
#define TILEMAP_SIZE (32 * 32)

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

struct oam {
	uint8_t x[0xA0];
};

struct gpu_state;

struct gpu_state * init_gpu();
void exit_gpu(struct gpu_state *);

void gpu_step(struct gpu_state *, uint8_t);

#endif

