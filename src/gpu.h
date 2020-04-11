#ifndef __GEMU_GPU_H
#define __GEMU_GPU_H

#include <stdint.h>

struct gpu_state;

struct gpu_state * init_gpu();
void exit_gpu(struct gpu_state *);

void gpu_step(struct gpu_state *, uint8_t);

#endif

