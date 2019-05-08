#include <stdint.h>

#include "mmu.h"

#define HW_REGS(n1, n2) \
	union { \
		struct { \
			uint8_t n2; \
			uint8_t n1; \
		}; \
		uint16_t n1##n2; \
	}

typedef uint16_t ea_t;
typedef uint8_t clk_t;

#pragma pack(push, 1)

struct flags {
	union {
		uint8_t all;
		struct {
			uint8_t oth : 4;
			uint8_t C : 1;
			uint8_t H : 1;
			uint8_t N : 1;
			uint8_t Z : 1;
		};
	};
};

struct regs {
	HW_REGS(A, F);
	HW_REGS(B, C);
	HW_REGS(D, E);
	HW_REGS(H, L);
	ea_t SP;
	ea_t PC;
	struct flags flags;
};

struct cpu_state {
	struct regs regs;
	clk_t mclk;
	clk_t tclk;
};

#pragma pack(pop)

typedef uint8_t inst_t;

#define MAX_OP_ARGS 2

#define OP_HANDLER(op) void op(uint8_t * args, struct cpu_state * state)

OP_HANDLER(ld_b_imm) {
	state->regs.B = args[0];
}

OP_HANDLER(ld_c_imm) {
	state->regs.C = args[0];
}

OP_HANDLER(ld_d_imm) {
	state->regs.D = args[0];
}

OP_HANDLER(ld_e_imm) {
	state->regs.E = args[0];
}

OP_HANDLER(ld_h_imm) {
	state->regs.H = args[0];
}

OP_HANDLER(ld_l_imm) {
	state->regs.L = args[0];
}

struct op {
	void (*handler)(uint8_t *, struct cpu_state *);
	uint8_t num_args;
	uint8_t cycles;
	inst_t opcode;
};

struct op OPS[] = {
	{ld_b_imm, 1, 8, 0x06},
	{ld_c_imm, 1, 8, 0x0E},
	{ld_d_imm, 1, 8, 0x16},
	{ld_e_imm, 1, 8, 0x1E},
	{ld_h_imm, 1, 8, 0x26},
	{ld_l_imm, 1, 8, 0x2E},
};

#include <stdio.h>

void reset(struct cpu_state * state) {
	state->regs.AF = 0;
	state->regs.BC = 0;
	state->regs.DE = 0;
	state->regs.HL = 0;
	state->regs.SP = 0;
	state->regs.PC = 0;
	state->regs.flags.all = 0;
	state->mclk = 0;
	state->tclk = 0;
}

int main(void) {
	struct cpu_state state = {1};
	reset(&state);
	printf("%lu\n", sizeof(struct flags));
	return 0;
}

