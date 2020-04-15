#include "gpu.h"

#include <stdlib.h>
#include <stdio.h>

#include <SDL.h>
#include <SDL_video.h>

#include "mmu.h"

#define SCREEN_WIDTH 160
#define SCREEN_HEIGHT 144

typedef enum {
	GPU_READ_OAM=2,
	GPU_READ_VRAM=3,
	GPU_HBLANK=0,
	GPU_VBLANK=1
} gpu_state_t;

#define GPU_OAM_TIME 80
#define GPU_VRAM_TIME 172
#define GPU_HBLANK_TIME 204
#define GPU_VBLANK_LINE_TIME (GPU_OAM_TIME + GPU_VRAM_TIME + GPU_HBLANK_TIME)
#define GPU_VBLANK_LINES 10

struct gpu_state {
	SDL_Window * window;
	SDL_Renderer * renderer;
	SDL_Texture * texture;
	SDL_PixelFormat * pixel_format;
	unsigned int timer;
};

struct gbpixel {
	uint8_t val;
	uint8_t mapped;  // after applying palette
};

static struct gbpixel line_buf[SCREEN_HEIGHT][SCREEN_WIDTH];

struct gpu_state * init_gpu() {
	struct gpu_state * state = malloc(sizeof(struct gpu_state));
	if (state == NULL) {
		fprintf(stderr, "Failed to allocate GPU state.\n");
		goto cleanup;
	}
	// Create window
	state->window = SDL_CreateWindow("GEMU", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (state->window == NULL) {
		goto err;
	}
	// Create renderer
	state->renderer = SDL_CreateRenderer(state->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	//state->renderer = SDL_CreateRenderer(state->window, -1, SDL_RENDERER_SOFTWARE);
	if (state->renderer == NULL) {
		goto err;
	}
	// Create texture
	state->texture = SDL_CreateTexture(state->renderer, SDL_PIXELFORMAT_RGB565, SDL_TEXTUREACCESS_STREAMING, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (state->texture == NULL) {
		goto err;
	}
	// Allocate pixel format
	state->pixel_format = SDL_AllocFormat(SDL_PIXELFORMAT_RGB565);
	if (state->pixel_format == NULL) {
		goto err;
	}
	// Initialize timer values
	write_ioreg_bits(lcdstat, mode, GPU_READ_OAM);
	state->timer = 0;
	// Done
	goto cleanup;
err:
	fprintf(stderr, "Initializing GPU failed: %s\n", SDL_GetError());
	exit_gpu(state);
cleanup:
	return state;
}

static uint8_t pixel_rgb_map[] = {255, 192, 96, 0};

static uint8_t extract_pixel_val(uint8_t lineval, uint8_t x) {
	return (((lineval << (TILE_LENGTH + x)) >> (2 * TILE_LENGTH - 2)) & 2) |
	       (((lineval << x) >> (2 * TILE_LENGTH - 1)) & 1);
}

static uint8_t map_pixel_in_palette(uint8_t pixel, uint8_t palette) {
	return ((palette << ((3 - pixel) * 2)) >> 6) & 3;
}

static void scan_line_bg(struct gpu_state * state, struct gbpixel * line) {
	uint8_t map_y = ((read8_ioreg(ly) + read8_ioreg(scy)) % (32 * 8)) / TILE_LENGTH;
	uint8_t tile_idx, pixel_val;
	uint16_t tileline_val, line_off;
	for (uint8_t x = 0; x < SCREEN_WIDTH; x++) {
		uint8_t map_x = ((read8_ioreg(scx) + x) % (32 * 8)) / TILE_LENGTH;
		if (read_ioreg_bits(lcdc, bg_set)) {
			tile_idx = read8_from_section(map_y * 32 + map_x, _vram.tilemap1);
		}
		else {
			tile_idx = read8_from_section(map_y * 32 + map_x, _vram.tilemap0);
		}
		if (!read_ioreg_bits(lcdc, bg_tile_set)) {
			tile_idx += 256;
		}
		line_off = (tile_idx * TILE_LENGTH * sizeof(uint16_t)) + (((read8_ioreg(ly) + read8_ioreg(scy)) % TILE_LENGTH) * sizeof(uint16_t));
		tileline_val = read16_from_section(line_off, _vram.tileset1_0);
		pixel_val = extract_pixel_val(tileline_val, (x + read8_ioreg(scx)) % TILE_LENGTH);
		line[x].val = pixel_val;
		line[x].mapped = map_pixel_in_palette(pixel_val, read8_ioreg(bgp));
	}
}

static void scan_line_obj(struct gpu_state * state, struct gbpixel * line) {
	struct sprite * curr = NULL;
	uint8_t line_y = read8_ioreg(scy) + read8_ioreg(ly);
	for (int i = 0; i < NUM_OF_SPRITES; i++) {
		curr = get_sprite(i);
		if (curr->y + 16 <= line_y && line_y < curr->y + 16 + TILE_LENGTH) {
			uint16_t tileline_val, line_off;
			uint8_t tile_idx = curr->tile;
			if (!curr->tile_set) {
				tile_idx += 256;
			}
			line_off = tile_idx * TILE_LENGTH * sizeof(uint16_t);
			if (curr->v_flip) {
				line_off += (TILE_LENGTH - (line_y % TILE_LENGTH) - 1) * sizeof(uint16_t);
			}
			else {
				line_off += (line_y % TILE_LENGTH) * sizeof(uint16_t);
			}
			tileline_val = read16_from_section(line_off, _vram.tileset1_0);
			for (uint8_t x = curr->x + 8; x < curr->x + 8 + TILE_LENGTH; x++) {
				uint8_t pixel_x, pixel_val, rgb, palette;
				if (x >= SCREEN_WIDTH) {
					continue;
				}
				if (curr->bg && line[x].val != 0) {
					continue;
				}
				if (curr->h_flip) {
					pixel_x = TILE_LENGTH - (x % TILE_LENGTH) - 1;
				}
				else {
					pixel_x = x % TILE_LENGTH;
				}
				if (curr->palette) {
					palette = read8_ioreg(obp1);
				}
				else {
					palette = read8_ioreg(obp0);
				}
				pixel_val = extract_pixel_val(tileline_val, pixel_x);
				if (pixel_val == 0) {
					continue;
				}
				line[x].val = pixel_val;
				line[x].mapped = map_pixel_in_palette(pixel_val, palette);
			}
		}
	}
}

static void scan_line(struct gpu_state * state, uint8_t lineno) {
	struct gbpixel * line = line_buf[lineno];
	if (!read_ioreg_bits(lcdc, lcd_enable)) {
		return;
	}
	if (read_ioreg_bits(lcdc, bg_enable)) {
		scan_line_bg(state, line);
	}
	if (read_ioreg_bits(lcdc, obj_enable)) {
		printf("scanning objects!\n");
		scan_line_obj(state, line);
	}
}

static void draw_lines(struct gpu_state * state) {
	uint8_t * pixel_map;
	uint16_t * line_map;
	uint8_t rgb;
	int pitch;
	SDL_Rect line_rect = {0};
	line_rect.w = SCREEN_WIDTH;
	line_rect.h = SCREEN_HEIGHT;
	if (!read_ioreg_bits(lcdc, lcd_enable)) {
		return;
	}
	SDL_LockTexture(state->texture, NULL, (void **)&pixel_map, &pitch);
	for (uint32_t y = 0; y < SCREEN_HEIGHT; y++) {
		line_map = (uint16_t *)(pixel_map + y * pitch);
		for (uint32_t x = 0; x < SCREEN_WIDTH; x++) {
			rgb = pixel_rgb_map[line_buf[y][x].mapped];
			*(line_map + x) = SDL_MapRGB(state->pixel_format, rgb, rgb, rgb);
		}
	}
	SDL_UnlockTexture(state->texture);
	SDL_RenderCopy(state->renderer, state->texture, &line_rect, &line_rect);
	SDL_RenderPresent(state->renderer);
}

void gpu_step(struct gpu_state * state, uint8_t ticks) {
	state->timer += ticks;
	switch (read_ioreg_bits(lcdstat, mode)) {
		case GPU_READ_OAM:
			if (state->timer >= GPU_OAM_TIME) {
				state->timer %= GPU_OAM_TIME;
				write_ioreg_bits(lcdstat, mode, GPU_READ_VRAM);
			}
			break;
		case GPU_READ_VRAM:
			if (state->timer >= GPU_VRAM_TIME) {
				state->timer %= GPU_VRAM_TIME;
				write_ioreg_bits(lcdstat, mode, GPU_HBLANK);
				scan_line(state, read8_ioreg(ly));
			}
			break;
		case GPU_HBLANK:
			if (state->timer >= GPU_HBLANK_TIME) {
				state->timer %= GPU_HBLANK_TIME;
				write8_ioreg(ly, read8_ioreg(ly) + 1);
				if (read8_ioreg(ly) == SCREEN_HEIGHT) {
					draw_lines(state);
					write_ioreg_bits(intf, vblank, 1);
					write_ioreg_bits(lcdstat, mode, GPU_VBLANK);
				}
				else {
					write_ioreg_bits(lcdstat, mode, GPU_READ_OAM);
				}
			}
			break;
		case GPU_VBLANK:
			if (state->timer >= GPU_VBLANK_LINE_TIME) {
				state->timer %= GPU_VBLANK_LINE_TIME;
				if (read8_ioreg(ly) == SCREEN_HEIGHT + GPU_VBLANK_LINES - 1) {
					write8_ioreg(ly, 0);
					write_ioreg_bits(lcdstat, mode, GPU_READ_OAM);
				}
				else {
					write8_ioreg(ly, read8_ioreg(ly) + 1);
				}
			}
			break;
	}
	if (read8_ioreg(ly) == read8_ioreg(lyc)) {
		write_ioreg_bits(lcdstat, lyc_stat, 1);
		if (read_ioreg_bits(lcdstat, lyc_intr)) {
			write_ioreg_bits(intf, lcdstat, 1);
		}
	}
	else {
		write_ioreg_bits(lcdstat, lyc_stat, 0);
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

