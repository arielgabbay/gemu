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

static struct {
	SDL_Window * window;
	SDL_Renderer * renderer;
	SDL_Texture * texture;
	SDL_PixelFormat * pixel_format;
	unsigned int timer;
	struct lcdstat lcdstat;  // refer to read_lcdstat/write_lcdstat's comments for details.
} gpu_state;

struct gbpixel {
	uint8_t val;
	uint8_t mapped;  // after applying palette
};

static struct gbpixel line_buf[SCREEN_HEIGHT][SCREEN_WIDTH];

gpu_ret_t init_gpu(const char * game_title) {
	gpu_ret_t ret = GPU_FAILURE;
	// Init SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
		goto err;
	}
	// Create window
	gpu_state.window = SDL_CreateWindow("GEMU", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (gpu_state.window == NULL) {
		goto err;
	}
	// Set window title (default title was set to "GEMU" on window initialization)
	if (game_title != NULL) {
		SDL_SetWindowTitle(gpu_state.window, game_title);
	}
	// Create renderer
	gpu_state.renderer = SDL_CreateRenderer(gpu_state.window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (gpu_state.renderer == NULL) {
		goto err;
	}
	// Create texture
	gpu_state.texture = SDL_CreateTexture(gpu_state.renderer, SDL_PIXELFORMAT_RGB565, SDL_TEXTUREACCESS_STREAMING, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (gpu_state.texture == NULL) {
		goto err;
	}
	// Allocate pixel format
	gpu_state.pixel_format = SDL_AllocFormat(SDL_PIXELFORMAT_RGB565);
	if (gpu_state.pixel_format == NULL) {
		goto err;
	}
	// Initialize timer values
	write_ioreg_bits(lcdstat, mode, GPU_READ_OAM);
	gpu_state.timer = 0;
	// Done
	ret = GPU_SUCCESS;
	goto cleanup;
err:
	fprintf(stderr, "Initializing GPU failed: %s\n", SDL_GetError());
	exit_gpu();
cleanup:
	return ret;
}

static uint8_t pixel_rgb_map[] = {255, 192, 96, 0};

static uint8_t extract_pixel_val(uint8_t lineval, uint8_t x) {
	return (((lineval << (TILE_LENGTH + x)) >> (2 * TILE_LENGTH - 2)) & 2) |
	       (((lineval << x) >> (2 * TILE_LENGTH - 1)) & 1);
}

static uint8_t map_pixel_in_palette(uint8_t pixel, uint8_t palette) {
	return ((palette << ((3 - pixel) * 2)) >> 6) & 3;
}

static void scan_line_bg(struct gbpixel * line) {
	uint8_t map_y = ((read8_ioreg(ly) + read8_ioreg(scy)) % (32 * 8)) / TILE_LENGTH;
	uint8_t tile_idx, pixel_val;
	uint16_t tileline_val, line_off;
	for (uint8_t x = 0; x < SCREEN_WIDTH; x++) {
		// If window display is enabled and we're on window tiles, read window tiles.
		if (read_ioreg_bits(lcdc, window_enable) && read8_ioreg(wx) + 7 <= x && read8_ioreg(wy) <= read8_ioreg(ly)) {
			if (read_ioreg_bits(lcdc, window_set)) {
				tile_idx = read8_from_section(read8_ioreg(ly) * 32 + x, _vram.tilemap1);
			}
			else {
				tile_idx = read8_from_section(read8_ioreg(ly) * 32 + x, _vram.tilemap0);
			}
		}
		// Otherwise (not on window), read background tiles.
		else {
			uint8_t map_x = ((read8_ioreg(scx) + x) % (32 * 8)) / TILE_LENGTH;
			if (read_ioreg_bits(lcdc, bg_set)) {
				tile_idx = read8_from_section(map_y * 32 + map_x, _vram.tilemap1);
			}
			else {
				tile_idx = read8_from_section(map_y * 32 + map_x, _vram.tilemap0);
			}
		}
		// Applies to both window and bg tile maps.
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

static void scan_line_obj(struct gbpixel * line) {
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

static void scan_line(uint8_t lineno) {
	struct gbpixel * line = line_buf[lineno];
	if (!read_ioreg_bits(lcdc, lcd_enable)) {
		return;
	}
	if (read_ioreg_bits(lcdc, bg_enable)) {
		scan_line_bg(line);
	}
	if (read_ioreg_bits(lcdc, obj_enable)) {
		scan_line_obj(line);
	}
}

static void draw_lines() {
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
	SDL_LockTexture(gpu_state.texture, NULL, (void **)&pixel_map, &pitch);
	for (uint32_t y = 0; y < SCREEN_HEIGHT; y++) {
		line_map = (uint16_t *)(pixel_map + y * pitch);
		for (uint32_t x = 0; x < SCREEN_WIDTH; x++) {
			rgb = pixel_rgb_map[line_buf[y][x].mapped];
			*(line_map + x) = SDL_MapRGB(gpu_state.pixel_format, rgb, rgb, rgb);
		}
	}
	SDL_UnlockTexture(gpu_state.texture);
	SDL_RenderCopy(gpu_state.renderer, gpu_state.texture, &line_rect, &line_rect);
	SDL_RenderPresent(gpu_state.renderer);
}

void write_oam_dma(ea_t addr, void * val, size_t size, uint8_t extra) {
	(void)extra;
	ea_t src = (*(uint8_t *)val) << 8;
	for (int i = 0; i < sizeof(struct oam); i++) {
		write8_to_section(i, oam, read8(src + i));
	}
}

// On lcdstat handling:
// When a game writes to lcdstat's *_intr flags, it enables/disables the LCDSTAT interrupt for
//     certain events. We catch these writes and store them in the internal gpu_state.lcdstat, and
//     this is where we refer to when checking if to raise these interrupts (in gpu_step).
// When an LCDSTAT interrupt is fired, the *_intr flags in the lcdstat register (the gmem-managed
//     ones in our case) are set according to the interrupt cause and reset when read once - this
//     resetting is done in read_lcdstat here.
// We write to gmem's lcdstat the current line value and the LY-LYC coincidence flag because they're
//     read by the game as well; they're not writable, which is covered because we write to the
//     internal lcdstat, where their values are meaningless.

void read_lcdstat(ea_t addr, void * val, size_t size, uint8_t extra) {
	(void)extra;
	*(uint8_t *)val = read8_simple(addr);
	write_ioreg_bits(lcdstat, hblank_intr, 0);
	write_ioreg_bits(lcdstat, vblank_intr, 0);
	write_ioreg_bits(lcdstat, oam_intr, 0);
	write_ioreg_bits(lcdstat, lyc_intr, 0);
}

void write_lcdstat(ea_t addr, void * val, size_t size, uint8_t extra) {
	(void)extra;
	*(uint8_t *)&gpu_state.lcdstat = *(uint8_t *)val;
}

#define SWITCH_GPU_MODE(modename, intrname) \
	do { \
		write_ioreg_bits(lcdstat, mode, GPU_##modename); \
		if (gpu_state.lcdstat.intrname##_intr) { \
			write_ioreg_bits(intf, lcdstat, 1); \
			write_ioreg_bits(lcdstat, intrname##_intr, 1); \
	       	} \
       	} while (0)

void gpu_step(uint8_t ticks) {
	gpu_state.timer += ticks;
	switch (read_ioreg_bits(lcdstat, mode)) {
		case GPU_READ_OAM:
			if (gpu_state.timer >= GPU_OAM_TIME) {
				gpu_state.timer %= GPU_OAM_TIME;
				write_ioreg_bits(lcdstat, mode, GPU_READ_VRAM);
			}
			break;
		case GPU_READ_VRAM:
			if (gpu_state.timer >= GPU_VRAM_TIME) {
				gpu_state.timer %= GPU_VRAM_TIME;
				SWITCH_GPU_MODE(HBLANK, hblank);
				scan_line(read8_ioreg(ly));
			}
			break;
		case GPU_HBLANK:
			if (gpu_state.timer >= GPU_HBLANK_TIME) {
				gpu_state.timer %= GPU_HBLANK_TIME;
				write8_ioreg(ly, read8_ioreg(ly) + 1);
				if (read8_ioreg(ly) == SCREEN_HEIGHT) {
					draw_lines();
					write_ioreg_bits(intf, vblank, 1);
					SWITCH_GPU_MODE(VBLANK, vblank);
				}
				else {
					SWITCH_GPU_MODE(READ_OAM, oam);
				}
			}
			break;
		case GPU_VBLANK:
			if (gpu_state.timer >= GPU_VBLANK_LINE_TIME) {
				gpu_state.timer %= GPU_VBLANK_LINE_TIME;
				if (read8_ioreg(ly) == SCREEN_HEIGHT + GPU_VBLANK_LINES - 1) {
					write8_ioreg(ly, 0);
					SWITCH_GPU_MODE(READ_OAM, oam);
				}
				else {
					write8_ioreg(ly, read8_ioreg(ly) + 1);
				}
			}
			break;
	}
	if (read8_ioreg(ly) == read8_ioreg(lyc)) {
		write_ioreg_bits(lcdstat, lyc_stat, 1);
		if (gpu_state.lcdstat.lyc_intr) {
			write_ioreg_bits(intf, lcdstat, 1);
			write_ioreg_bits(lcdstat, lyc_intr, 1);
		}
	}
	else {
		write_ioreg_bits(lcdstat, lyc_stat, 0);
	}
}

void exit_gpu() {
	if (gpu_state.pixel_format != NULL) {
		SDL_FreeFormat(gpu_state.pixel_format);
	}
	if (gpu_state.texture != NULL) {
		SDL_DestroyTexture(gpu_state.texture);
	}
	if (gpu_state.renderer != NULL) {
		SDL_DestroyRenderer(gpu_state.renderer);
	}
	if (gpu_state.window != NULL) {
		SDL_DestroyWindow(gpu_state.window);
	}
	SDL_Quit();
}

