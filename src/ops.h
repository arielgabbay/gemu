#ifndef __GEMU_OPS_H
#define __GEMU_OPS_H

#include <stdint.h>

#include "cpu.h"

#define MAX_OP_ARGS 2
#define MAX_OP_BYTES 2

#define EXP_OP_HANDLER(op) void op(uint8_t *, struct cpu_state *)

typedef uint8_t inst_t;

cpu_ret_t handle_op(struct cpu_state *);

void run_exp_op(void (*)(uint8_t *, struct cpu_state *), uint8_t *, struct cpu_state *);

EXP_OP_HANDLER(call_imm);

#endif /* __GEMU_OPS_H */

