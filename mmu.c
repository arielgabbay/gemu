#include <string.h>

#include "mmu.h"

struct gmem gmem = {0};

uint8_t read8(ea_t addr) {
	return gmem.flat[addr];
}

void write8(ea_t addr, uint8_t val) {
	gmem.flat[addr] = val;
}

void init_gmem() {
	memset(&gmem, 0, sizeof(gmem));
}

