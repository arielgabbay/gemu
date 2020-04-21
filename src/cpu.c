#include "cpu.h"

#include <stdint.h>
#include <stdlib.h>

#include "ops.h"
#include "input.h"
#include "gpu.h"

void reset(struct cpu_state * state, int debug) {
	state->regs.AF = 0;
	state->regs.BC = 0;
	state->regs.DE = 0;
	state->regs.HL = 0;
	state->regs.SP = 0;
	state->regs.PC = 0;
	state->mclk = 0;
	state->tclk = 0;
	state->debug = debug;
}

uint8_t cpu_fetch(struct cpu_state * state) {
	uint8_t val = read8_inst(state->regs.PC);
	state->regs.PC += sizeof(val);
	return val;
}

#define CHECK_INTR(intr, dst) \
	do { \
		if (intr_enable.intr && read_ioreg_bits(intf, intr)) { \
			write_ioreg_bits(intf, intr, 0); \
			intr_dst = dst; \
       		} \
	} while (0)

static void handle_interrupts(struct cpu_state * state) {
	struct intf intr_enable;
	if (state->rflags.intr == INTR_ENABLED) {
		*(uint8_t *)&intr_enable = read8_from_section(0, intr_enable);
		ea_t intr_dst = 0;
		CHECK_INTR(vblank, 0x40);
		CHECK_INTR(lcdstat, 0x48);
		CHECK_INTR(timer, 0x50);
		CHECK_INTR(serial, 0x58);
		CHECK_INTR(joyp, 0x60);
		if (intr_dst) {  // Assuming here 0 is not an interrupt handled here
			state->rflags.intr = INTR_DISABLED;
			run_exp_op(call_imm, (uint8_t *)&intr_dst, state);
		}
	}
}

int cpu_main(int debug) {
	struct cpu_state state = {0};
	clk_t prev_time = 0;
	struct op * curr_op = NULL;
	uint8_t intr_state;
	reset(&state, debug);
	while (!input_quit) {
		intr_state = state.rflags.intr;
		// Handle next op
		if (handle_op(&state) != CPU_SUCCESS) {
			// TODO: error
			break;
		}
		// Set interrupts if needed
		if (intr_state == INTR_EI) {
			state.rflags.intr = INTR_ENABLED;
		}
		else if (intr_state == INTR_DI) {
			state.rflags.intr = INTR_DISABLED;
		}
		// Check for interrupts
		handle_interrupts(&state);
		// Invoke GPU step (assuming not too many ticks have occurred in the meantime.)
		gpu_step(abs((int8_t)(state.mclk - prev_time)));
		prev_time = state.mclk;
	}
	return 0;
}

