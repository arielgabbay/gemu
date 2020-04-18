#ifndef __GEMU_INPUT_H
#define __GEMU_INPUT_H

#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>

#include "mmu.h"

extern pthread_mutex_t input_lock;
extern int input_quit;

void * input_main(void *);
void read_joyp(ea_t, void *, size_t, uint8_t);
void write_joyp(ea_t, void *, size_t, uint8_t);

#endif

