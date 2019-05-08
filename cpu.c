#include <stdint.h>

#include "mmu.h"

typedef enum {
	CPU_SUCCESS=0,
	CPU_FAILURE,
} cpu_ret_t;

#define HW_REGS(n1, n2) \
	union { \
		struct { \
			uint8_t n2; \
			uint8_t n1; \
		}; \
		uint16_t n1##n2; \
	}

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
	union {
		struct {
			struct flags flags;
			uint8_t A;
		};
		uint16_t AF;
	};
	HW_REGS(B, C);
	HW_REGS(D, E);
	HW_REGS(H, L);
	ea_t SP;
	ea_t PC;
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

/* LD reg, imm (8-bit) */

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

/* LD reg, reg (8-bit) */

OP_HANDLER(ld_a_a) {
	state->regs.A = state->regs.A;
}

OP_HANDLER(ld_a_b) {
	state->regs.A = state->regs.B;
}

OP_HANDLER(ld_a_c) {
	state->regs.A = state->regs.C;
}

OP_HANDLER(ld_a_d) {
	state->regs.A = state->regs.D;
}

OP_HANDLER(ld_a_e) {
	state->regs.A = state->regs.E;
}

OP_HANDLER(ld_a_h) {
	state->regs.A = state->regs.H;
}

OP_HANDLER(ld_a_l) {
	state->regs.A = state->regs.L;
}

OP_HANDLER(ld_b_b) {
	state->regs.B = state->regs.B;
}

OP_HANDLER(ld_b_c) {
	state->regs.B = state->regs.C;
}

OP_HANDLER(ld_b_d) {
	state->regs.B = state->regs.D;
}

OP_HANDLER(ld_b_e) {
	state->regs.B = state->regs.E;
}

OP_HANDLER(ld_b_h) {
	state->regs.B = state->regs.H;
}

OP_HANDLER(ld_b_l) {
	state->regs.B = state->regs.L;
}

OP_HANDLER(ld_c_b) {
	state->regs.C = state->regs.B;
}

OP_HANDLER(ld_c_c) {
	state->regs.C = state->regs.C;
}

OP_HANDLER(ld_c_d) {
	state->regs.C = state->regs.D;
}

OP_HANDLER(ld_c_e) {
	state->regs.C = state->regs.E;
}

OP_HANDLER(ld_c_h) {
	state->regs.C = state->regs.H;
}

OP_HANDLER(ld_c_l) {
	state->regs.C = state->regs.L;
}

OP_HANDLER(ld_d_b) {
	state->regs.D = state->regs.B;
}

OP_HANDLER(ld_d_c) {
	state->regs.D = state->regs.C;
}

OP_HANDLER(ld_d_d) {
	state->regs.D = state->regs.D;
}

OP_HANDLER(ld_d_e) {
	state->regs.D = state->regs.E;
}

OP_HANDLER(ld_d_h) {
	state->regs.D = state->regs.H;
}

OP_HANDLER(ld_d_l) {
	state->regs.D = state->regs.L;
}

OP_HANDLER(ld_e_b) {
	state->regs.E = state->regs.B;
}

OP_HANDLER(ld_e_c) {
	state->regs.E = state->regs.C;
}

OP_HANDLER(ld_e_d) {
	state->regs.E = state->regs.D;
}

OP_HANDLER(ld_e_e) {
	state->regs.E = state->regs.E;
}

OP_HANDLER(ld_e_h) {
	state->regs.E = state->regs.H;
}

OP_HANDLER(ld_e_l) {
	state->regs.E = state->regs.L;
}

OP_HANDLER(ld_h_b) {
	state->regs.H = state->regs.B;
}

OP_HANDLER(ld_h_c) {
	state->regs.H = state->regs.C;
}

OP_HANDLER(ld_h_d) {
	state->regs.H = state->regs.D;
}

OP_HANDLER(ld_h_e) {
	state->regs.H = state->regs.E;
}

OP_HANDLER(ld_h_h) {
	state->regs.H = state->regs.H;
}

OP_HANDLER(ld_h_l) {
	state->regs.H = state->regs.L;
}

OP_HANDLER(ld_l_b) {
	state->regs.L = state->regs.B;
}

OP_HANDLER(ld_l_c) {
	state->regs.L = state->regs.C;
}

OP_HANDLER(ld_l_d) {
	state->regs.L = state->regs.D;
}

OP_HANDLER(ld_l_e) {
	state->regs.L = state->regs.E;
}

OP_HANDLER(ld_l_h) {
	state->regs.L = state->regs.H;
}

OP_HANDLER(ld_l_l) {
	state->regs.L = state->regs.L;
}

struct op {
	void (*handler)(uint8_t *, struct cpu_state *);
	uint8_t num_args;
	uint8_t cycles;
	inst_t opcode;
};

struct op OPS[] = {
	/* LD reg, imm (8-bit) */
	{ld_b_imm, 1, 8, 0x06},
	{ld_c_imm, 1, 8, 0x0E},
	{ld_d_imm, 1, 8, 0x16},
	{ld_e_imm, 1, 8, 0x1E},
	{ld_h_imm, 1, 8, 0x26},
	{ld_l_imm, 1, 8, 0x2E},
	/* LD reg, reg (8-bit) */
	{ld_a_a, 0, 4, 0x7F},
	{ld_a_b, 0, 4, 0x78},
	{ld_a_c, 0, 4, 0x79},
	{ld_a_d, 0, 4, 0x7A},
	{ld_a_e, 0, 4, 0x7B},
	{ld_a_h, 0, 4, 0x7C},
	{ld_a_l, 0, 4, 0x7D},
	{ld_b_b, 0, 4, 0x40},
	{ld_b_c, 0, 4, 0x41},
	{ld_b_d, 0, 4, 0x42},
	{ld_b_e, 0, 4, 0x43},
	{ld_b_h, 0, 4, 0x44},
	{ld_b_l, 0, 4, 0x45},
	{ld_c_b, 0, 4, 0x48},
	{ld_c_c, 0, 4, 0x49},
	{ld_c_d, 0, 4, 0x4A},
	{ld_c_e, 0, 4, 0x4B},
	{ld_c_h, 0, 4, 0x4C},
	{ld_c_l, 0, 4, 0x4D},
	{ld_d_b, 0, 4, 0x50},
	{ld_d_c, 0, 4, 0x51},
	{ld_d_d, 0, 4, 0x52},
	{ld_d_e, 0, 4, 0x53},
	{ld_d_h, 0, 4, 0x54},
	{ld_d_l, 0, 4, 0x55},
	{ld_e_b, 0, 4, 0x58},
	{ld_e_c, 0, 4, 0x59},
	{ld_e_d, 0, 4, 0x5A},
	{ld_e_e, 0, 4, 0x5B},
	{ld_e_h, 0, 4, 0x5C},
	{ld_e_l, 0, 4, 0x5D},
	{ld_h_b, 0, 4, 0x60},
	{ld_h_c, 0, 4, 0x61},
	{ld_h_d, 0, 4, 0x62},
	{ld_h_e, 0, 4, 0x63},
	{ld_h_h, 0, 4, 0x64},
	{ld_h_l, 0, 4, 0x65},
	{ld_l_b, 0, 4, 0x68},
	{ld_l_c, 0, 4, 0x69},
	{ld_l_d, 0, 4, 0x6A},
	{ld_l_e, 0, 4, 0x6B},
	{ld_l_h, 0, 4, 0x6C},
	{ld_l_l, 0, 4, 0x6D},
};

#include <stdio.h>

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

uint8_t cpu_read8(struct cpu_state * state) {
	uint8_t val = read8(state->regs.PC);
	state->regs.PC += sizeof(val);
	return val;
}

cpu_ret_t handle_op(inst_t op, struct cpu_state * state) {
	struct op * op_desc = NULL;
	uint8_t args[MAX_OP_ARGS] = {0};
	int i;
	for (i = 0; i < sizeof(OPS) / sizeof(struct op); i++) {
		if (OPS[i].opcode == op) {
			op_desc = &OPS[i];
			break;
		}
	}
	if (op_desc == NULL) {
		return CPU_FAILURE;
	}
	for (i = 0; i < op_desc->num_args; i++) {
		args[i] = cpu_read8(state);
	}
	op_desc->handler(args, state);
	// TODO: handle op_desc->cycles
	return CPU_SUCCESS;
}

int cpu_main() {
	struct cpu_state state = {0};
	reset(&state);
	while (1) {
		inst_t op = cpu_read8(&state);
		handle_op(op, &state);
	}
	return 0;
}

int main() {
	return 0;
}

