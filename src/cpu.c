#include "cpu.h"

#include <stdint.h>
#include <stdlib.h>

#include "ops.h"

static void reset(struct cpu_state * state, int debugging) {
	state->regs.AF = 0;
	state->regs.BC = 0;
	state->regs.DE = 0;
	state->regs.HL = 0;
	state->regs.SP = 0;
	state->regs.PC = 0;
	state->mclk = 0;
	state->tclk = 0;
	state->debugging = debugging;
}

uint8_t cpu_fetch(struct cpu_state * state) {
	uint8_t val = read8_inst(state->regs.PC);
	state->regs.PC += sizeof(val);
	return val;
}

int cpu_main(struct gpu_state * gpu_state, int debugging) {
	struct cpu_state state = {0};
	clk_t prev_time = 0;
	struct op * curr_op = NULL;
	reset(&state, debugging);
	while (1) {
		uint8_t intr_state = state.rflags.intr;
		if (handle_op(&state) != CPU_SUCCESS) {
			// TODO: error
			break;
		}
		if (intr_state == INTR_EI) {
			state.rflags.intr = INTR_ENABLED;
		}
		else if (intr_state == INTR_DI) {
			state.rflags.intr = INTR_DISABLED;
		}
		gpu_step(gpu_state, state.tclk - prev_time);
		prev_time = state.tclk;
	}
	return 0;
}

