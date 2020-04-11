#include "gpu.h"

#include <stdlib.h>
#include <stdio.h>

#include <SDL.h>
#include <SDL_video.h>

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
	state->texture = SDL_CreateTexture(state->renderer, SDL_PIXELFORMAT_RGBA4444, SDL_TEXTUREACCESS_STREAMING, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (state->texture == NULL) {
		goto err;
	}
	// Allocate pixel format
	state->pixel_format = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA4444);
	if (state->pixel_format == NULL) {
		goto err;
	}
	// Initialize timer values
	state->timer_rem = 0;
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
				// TODO: renderscan
			}
			break;
		case GPU_HBLANK:
			if (state->timer >= GPU_HBLANK_TIME) {
				state->timer %= GPU_HBLANK_TIME;
				state->line++;
				if (state->line == WINDOW_HEIGHT - 1) {
					state->state = GPU_VBLANK;
					// TODO: putImageData
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

