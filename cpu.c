#include <stdint.h>
#include <stdlib.h>

#include "cpu.h"
#include "ops.h"

void reset(struct cpu_state * state) {
	state->regs.AF = 0;
	state->regs.BC = 0;
	state->regs.DE = 0;
	state->regs.HL = 0;
	state->regs.SP = 0;
	state->regs.PC = 0;
	state->mclk = 0;
	state->tclk = 0;
}

uint8_t cpu_fetch(struct cpu_state * state) {
	uint8_t val = read8(state->regs.PC);
	state->regs.PC += sizeof(val);
	return val;
}

int cpu_main() {
	struct cpu_state state = {0};
	struct op * curr_op = NULL;
	uint8_t op_args[MAX_OP_ARGS] = {0};
	reset(&state);
	while (1) {
		inst_t op = cpu_fetch(&state);
		curr_op = get_op(op);
		for (int i = 0; i < curr_op->num_args; i++) {
			op_args[i] = cpu_fetch(&state);
		}
		handle_op(curr_op, op_args, &state);
	}
	return 0;
}

