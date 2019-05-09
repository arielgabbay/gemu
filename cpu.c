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
	reset(&state);
	while (1) {
		if (handle_op(&state) != CPU_SUCCESS) {
			// TODO: error
			break;
		}
	}
	return 0;
}

