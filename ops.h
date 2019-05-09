#ifndef __GEMU_OPS_H
#define __GEMU_OPS_H

#include <stdint.h>

#include "cpu.h"

#define MAX_OP_ARGS 2

typedef uint8_t inst_t;

struct op {
	void (*handler)(uint8_t *, struct cpu_state *);
	uint8_t num_args;
	uint8_t cycles;
	inst_t opcode;
};

struct op * get_op(inst_t op);
void handle_op(struct op * op_desc, uint8_t * args, struct cpu_state * state);

#endif /* __GEMU_OPS_H */

