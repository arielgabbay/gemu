#ifndef __GEMU_INPUT_H
#define __GEMU_INPUT_H

#include <stdlib.h>

#include "mmu.h"

int input_step();
void read_joyp(ea_t, void *, size_t);
void write_joyp(ea_t, void *, size_t);

#endif

