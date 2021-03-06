#include "input.h"

#include <SDL_events.h>

pthread_mutex_t input_lock;
int input_quit = 0;

typedef enum {
	GB_KEY_A=1,
	GB_KEY_RIGHT=1,
	GB_KEY_B=2,
	GB_KEY_LEFT=2,
	GB_KEY_SELECT=4,
	GB_KEY_UP=4,
	GB_KEY_START=8,
	GB_KEY_DOWN=8,
	GB_KEY_MASK=0xF
} gb_key_t;

static uint8_t buttons = GB_KEY_MASK;
static uint8_t arrows = GB_KEY_MASK;
static uint8_t joyp_req = 0;

void read_joyp(ea_t addr, void * res, size_t size, uint8_t extra) {
	(void)extra;
	if (size != sizeof(buttons)) {
		return;
	}
	pthread_mutex_lock(&input_lock);
	if (joyp_req == 0x10) {
		*(uint8_t *)res = buttons;
	}
	else if (joyp_req == 0x20) {
		*(uint8_t *)res = arrows;
	}
	pthread_mutex_unlock(&input_lock);
}

// This writer isn't strictly necessary; we could just not really write to joyp ourselves.
void write_joyp(ea_t addr, void * val, size_t size, uint8_t extra) {
	(void)extra;
	if (size == sizeof(joyp_req)) {
		joyp_req = *(uint8_t *)val;
	}
}

static void handle_key(SDL_KeyboardEvent * event) {
	int val = -1;
	uint8_t * keyset = NULL;
	uint8_t keybit = 0;
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
			keybit = GB_KEY_START;
			keyset = &buttons;
			break;
		case SDLK_DOWN:
			keybit = GB_KEY_DOWN;
			keyset = &arrows;
			break;
		case SDLK_SPACE:
			keybit = GB_KEY_SELECT;
			keyset = &buttons;
			break;
		case SDLK_UP:
			keybit = GB_KEY_UP;
			keyset = &arrows;
			break;
		case SDLK_z:
			keybit = GB_KEY_B;
			keyset = &buttons;
			break;
		case SDLK_LEFT:
			keybit = GB_KEY_LEFT;
			keyset = &arrows;
			break;
		case SDLK_x:
			keybit = GB_KEY_A;
			keyset = &buttons;
			break;
		case SDLK_RIGHT:
			keybit = GB_KEY_RIGHT;
			keyset = &arrows;
			break;
		default:
			val = -1;
			break;
	}
	if (val == -1) {
		return;
	}
	pthread_mutex_lock(&input_lock);
	if (val == 1) {
		(*keyset) |= keybit;
	}
	else if (val == 0) {
		if ((*keyset) & keybit) {
			write_ioreg_bits(intf, joyp, 1);
		}
		(*keyset) &= ~keybit;
	}
	pthread_mutex_unlock(&input_lock);
}

void * input_main(void * arg) {
	(void)arg;
	SDL_Event event;
	while (!input_quit) {
		if (SDL_WaitEvent(&event) == 0) {
			break;
		}
		switch (event.type) {
			case SDL_KEYDOWN:
			case SDL_KEYUP:
				handle_key(&event.key);
				break;
			case SDL_QUIT:
				input_quit = 1;
				break;
		}
	}
	return NULL;
}

