#include "input.h"

#include <SDL_events.h>

#include "mmu.h"

static void handle_key(SDL_KeyboardEvent * event) {
	int val = 0;
	switch (event->type) {
		case SDL_KEYDOWN:
			val = 0;
			break;
		case SDL_KEYUP:
			val = 1;
			break;
	}
	switch (event->keysym.sym) {
		case SDLK_RETURN:
		case SDLK_DOWN:
			write_ioreg_bits(joyp, d_start, val);
			break;
		case SDLK_SPACE:
		case SDLK_UP:
			write_ioreg_bits(joyp, u_select, val);
			break;
		case SDLK_z:
		case SDLK_LEFT:
			write_ioreg_bits(joyp, l_b, val);
			break;
		case SDLK_x:
		case SDLK_RIGHT:
			write_ioreg_bits(joyp, r_a, val);
			break;
	}
}

int input_step() {
	SDL_Event event;
	if (!SDL_PollEvent(&event)) {
		return 0;
	}
	switch (event.type) {
		case SDL_KEYDOWN:
		case SDL_KEYUP:
			handle_key(&event.key);
			break;
		case SDL_QUIT:
			return 1;
			break;
	}
	return 0;
}

