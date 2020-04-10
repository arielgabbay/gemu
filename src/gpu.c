#include "gpu.h"

#include <stdlib.h>
#include <stdio.h>

#include <SDL_video.h>

#define WINDOW_WIDTH 160
#define WINDOW_HEIGHT 144

static SDL_Window * window = NULL;

int init_gpu() {
	window = SDL_CreateWindow("GEMU", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == NULL) {
		fprintf(stderr, "CreateWindow failed: %s\n", SDL_GetError());
		return 1;
	}
	return 0;
}

void exit_gpu() {
	SDL_DestroyWindow(window);
}

