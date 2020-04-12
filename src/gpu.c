#include "gpu.h"

#include <stdlib.h>
#include <stdio.h>

#include <SDL.h>
#include <SDL_video.h>

#include "mmu.h"

#define WINDOW_WIDTH 160
#define WINDOW_HEIGHT 144

typedef enum {
	GPU_READ_OAM=0,
	GPU_READ_VRAM,
	GPU_HBLANK,
	GPU_VBLANK
} gpu_state_t;

#define GPU_OAM_TIME 80
#define GPU_VRAM_TIME 172
#define GPU_HBLANK_TIME 204
#define GPU_VBLANK_TIME ((GPU_OAM_TIME + GPU_VRAM_TIME + GPU_HBLANK_TIME) * 10)

struct gpu_state {
	SDL_Window * window;
	SDL_Renderer * renderer;
	SDL_Texture * texture;
	SDL_PixelFormat * pixel_format;
	gpu_state_t state;
	unsigned int timer;
	unsigned int line;
};

static uint32_t line_buf[WINDOW_WIDTH];

struct gpu_state * init_gpu() {
	struct gpu_state * state = malloc(sizeof(struct gpu_state));
	if (state == NULL) {
		fprintf(stderr, "Failed to allocate GPU state.\n");
		goto cleanup;
	}
	// Create window
	state->window = SDL_CreateWindow("GEMU", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
	if (state->window == NULL) {
		goto err;
	}
	// Create renderer
	state->renderer = SDL_CreateRenderer(state->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (state->renderer == NULL) {
		goto err;
	}
	// Create texture
	state->texture = SDL_CreateTexture(state->renderer, SDL_PIXELFORMAT_RGB444, SDL_TEXTUREACCESS_STREAMING, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (state->texture == NULL) {
		goto err;
	}
	// Allocate pixel format
	state->pixel_format = SDL_AllocFormat(SDL_PIXELFORMAT_RGB444);
	if (state->pixel_format == NULL) {
		goto err;
	}
	// Initialize timer values
	state->state = GPU_READ_OAM;
	state->timer = 0;
	state->line = 0;
	// Done
	goto cleanup;
err:
	fprintf(stderr, "Initializing GPU failed: %s\n", SDL_GetError());
	exit_gpu(state);
cleanup:
	return state;
}

static uint8_t pixel_rgb_map[] = {255, 192, 96, 0};

static uint8_t map_pixel_in_bgp(uint8_t lineval, uint8_t x) {
	uint8_t pixel = ((lineval << (TILE_LENGTH + x)) >> (2 * TILE_LENGTH - 2)) |
		        ((lineval << x) >> (2 * TILE_LENGTH - 1));
	uint8_t bgp = read8_ioreg(bgp);
	uint8_t val = (bgp << ((3 - pixel) * 2)) >> 6;
	return pixel_rgb_map[val];
}

static void scan_line_bg(struct gpu_state * state, uint32_t * line) {
	uint8_t map_y = ((state->line + read8_ioreg(scy)) % (32 * 8)) / TILE_LENGTH;
	uint8_t tile, tile_idx, line_off, rgb;
	uint16_t tileline_val;
	for (uint8_t x = 0; x < WINDOW_WIDTH; x++) {
		uint8_t map_x = ((read8_ioreg(scx) + x) % (32 * 8)) / TILE_LENGTH;
		if (read_ioreg_bits(lcdc, bg_set)) {
			tile = read8_from_section(map_y * 32 + map_x, _vram.tilemap1);
		}
		else {
			tile = read8_from_section(map_y * 32 + map_x, _vram.tilemap0);
		}
		if (read_ioreg_bits(lcdc, bg_tile_set)) {
			tile_idx = tile;
		}
		else {
			tile_idx = tile + 256;
		}
		line_off = (tile_idx * TILE_LENGTH * sizeof(uint16_t)) + ((state->line % TILE_LENGTH) * sizeof(uint16_t));
		tileline_val = read16_from_section(line_off, _vram.tileset1_0);
		rgb = map_pixel_in_bgp(tileline_val, read8_ioreg(scx) % TILE_LENGTH);
		line[x] = SDL_MapRGB(state->pixel_format, rgb, rgb, rgb);
	}
}

static void scan_line_obj(struct gpu_state * state, uint32_t * line) {
}

static void scan_line(struct gpu_state * state, uint32_t * line) {
	if (!read_ioreg_bits(lcdc, lcd_enable)) {
		return;
	}
	if (read_ioreg_bits(lcdc, bg_enable)) {
		scan_line_bg(state, line);
	}
	if (read_ioreg_bits(lcdc, obj_enable)) {
		scan_line_obj(state, line);
	}
}

static void draw_line(struct gpu_state * state, uint32_t * line) {
	uint32_t tex_format;
	uint8_t * pixel_map;
	int pitch;
	SDL_Rect line_rect = {0};
	line_rect.y = state->line;
	line_rect.w = WINDOW_WIDTH;
	line_rect.h = 1;
	SDL_LockTexture(state->texture, &line_rect, (void **)&pixel_map, &pitch);
	for (uint8_t x = 0; x < WINDOW_WIDTH; x++) {
		*(uint32_t *)(pixel_map + state->line * pitch + x) = line[x];
	}
	SDL_UnlockTexture(state->texture);
	SDL_RenderCopy(state->renderer, state->texture, &line_rect, &line_rect);
	SDL_RenderPresent(state->renderer);
}

void gpu_step(struct gpu_state * state, uint8_t ticks) {
	state->timer += ticks;
	switch (state->state) {
		case GPU_READ_OAM:
			if (state->timer >= GPU_OAM_TIME) {
				state->timer %= GPU_OAM_TIME;
				state->state = GPU_READ_VRAM;
			}
			break;
		case GPU_READ_VRAM:
			if (state->timer >= GPU_VRAM_TIME) {
				state->timer %= GPU_VRAM_TIME;
				state->state = GPU_HBLANK;
				scan_line(state, line_buf);
			}
			break;
		case GPU_HBLANK:
			if (state->timer >= GPU_HBLANK_TIME) {
				state->timer %= GPU_HBLANK_TIME;
				draw_line(state, line_buf);
				state->line++;
				if (state->line == WINDOW_HEIGHT - 1) {
					state->state = GPU_VBLANK;
				}
				else {
					state->state = GPU_READ_OAM;
				}
			}
			break;
		case GPU_VBLANK:
			if (state->timer >= GPU_VBLANK_TIME) {
				state->timer %= GPU_VBLANK_TIME;
				state->line = 0;
				state->state = GPU_READ_OAM;
			}
			break;
	}
}

void exit_gpu(struct gpu_state * state) {
	if (state == NULL) {
		return;
	}
	if (state->pixel_format != NULL) {
		SDL_FreeFormat(state->pixel_format);
	}
	if (state->texture != NULL) {
		SDL_DestroyTexture(state->texture);
	}
	if (state->renderer != NULL) {
		SDL_DestroyRenderer(state->renderer);
	}
	if (state->window != NULL) {
		SDL_DestroyWindow(state->window);
	}
	free(state);
}

