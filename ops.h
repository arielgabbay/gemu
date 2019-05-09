#ifndef __GEMU_OPS_H
#define __GEMU_OPS_H

#include <stdint.h>

#include "cpu.h"

#define MAX_OP_ARGS 2
#define MAX_OP_BYTES 2

typedef uint8_t inst_t;

cpu_ret_t handle_op(struct cpu_state *);

#endif /* __GEMU_OPS_H */

