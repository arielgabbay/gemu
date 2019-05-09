#include <stdlib.h>

#include "ops.h"
#include "mmu.h"

#define OP_HANDLER(op) void op(uint8_t * args, struct cpu_state * state)

/* LD reg, imm (8-bit) */

OP_HANDLER(ld_a_imm) {
	state->regs.A = args[0];
}

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

OP_HANDLER(ld_b_a) {
	state->regs.B = state->regs.A;
}

OP_HANDLER(ld_c_a) {
	state->regs.C = state->regs.A;
}

OP_HANDLER(ld_d_a) {
	state->regs.D = state->regs.A;
}

OP_HANDLER(ld_e_a) {
	state->regs.E = state->regs.A;
}

OP_HANDLER(ld_h_a) {
	state->regs.H = state->regs.A;
}

OP_HANDLER(ld_l_a) {
	state->regs.L = state->regs.A;
}

/* LD reg, [HL] (8-bit) */

OP_HANDLER(ld_a_hl) {
	state->regs.A = read8(state->regs.HL);
}

OP_HANDLER(ld_b_hl) {
	state->regs.B = read8(state->regs.HL);
}

OP_HANDLER(ld_c_hl) {
	state->regs.C = read8(state->regs.HL);
}

OP_HANDLER(ld_d_hl) {
	state->regs.D = read8(state->regs.HL);
}

OP_HANDLER(ld_e_hl) {
	state->regs.E = read8(state->regs.HL);
}

OP_HANDLER(ld_h_hl) {
	state->regs.H = read8(state->regs.HL);
}

OP_HANDLER(ld_l_hl) {
	state->regs.L = read8(state->regs.HL);
}

/* LD [HL], reg (8-bit) */

OP_HANDLER(ld_hl_b) {
	write8(state->regs.HL, state->regs.B);
}

OP_HANDLER(ld_hl_c) {
	write8(state->regs.HL, state->regs.C);
}

OP_HANDLER(ld_hl_d) {
	write8(state->regs.HL, state->regs.D);
}

OP_HANDLER(ld_hl_e) {
	write8(state->regs.HL, state->regs.E);
}

OP_HANDLER(ld_hl_h) {
	write8(state->regs.HL, state->regs.H);
}

OP_HANDLER(ld_hl_l) {
	write8(state->regs.HL, state->regs.L);
}

/* LD [HL], imm (8-bit) */

OP_HANDLER(ld_hl_imm) {
	write8(state->regs.HL, args[0]);
}

/* LD A, [reg] (8-bit) */

OP_HANDLER(ld_a_bc) {
	state->regs.A = read8(state->regs.BC);
}

OP_HANDLER(ld_a_de) {
	state->regs.A = read8(state->regs.DE);
}

/* LD A, [imm] (8-bit) */

OP_HANDLER(ld_a_immd) {
	state->regs.A = read8(*(uint16_t *)args);
}

/* LD [reg], A (8-bit) */

OP_HANDLER(ld_bc_a) {
	write8(state->regs.BC, state->regs.A);
}

OP_HANDLER(ld_de_a) {
	write8(state->regs.BC, state->regs.A);
}

OP_HANDLER(ld_hl_a) {
	write8(state->regs.HL, state->regs.A);
}

/* LD [imm], A (8-bit) */

OP_HANDLER(ld_imm_a) {
	write8(*(uint16_t *)args, state->regs.A);
}

struct op OPS[] = {
	/* LD reg, imm (8-bit) */
	{ld_a_imm, 1, 8, 0x3E},
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
	{ld_b_a, 0, 4, 0x47},
	{ld_c_a, 0, 4, 0x4F},
	{ld_d_a, 0, 4, 0x57},
	{ld_e_a, 0, 4, 0x5F},
	{ld_h_a, 0, 4, 0x67},
	{ld_l_a, 0, 4, 0x6F},
	/* LD reg, [HL] (8-bit) */
	{ld_a_hl, 0, 8, 0x7E},
	{ld_b_hl, 0, 8, 0x46},
	{ld_c_hl, 0, 8, 0x4E},
	{ld_d_hl, 0, 8, 0x56},
	{ld_e_hl, 0, 8, 0x5E},
	{ld_h_hl, 0, 8, 0x66},
	{ld_l_hl, 0, 8, 0x6E},
	/* LD [HL], reg (8-bit) */
	{ld_hl_b, 0, 8, 0x70},
	{ld_hl_c, 0, 8, 0x71},
	{ld_hl_d, 0, 8, 0x72},
	{ld_hl_e, 0, 8, 0x73},
	{ld_hl_h, 0, 8, 0x74},
	{ld_hl_l, 0, 8, 0x75},
	/* LD [HL], imm (8-bit) */
	{ld_hl_imm, 1, 12, 0x36},
	/* LD A, [reg] (8-bit) */
	{ld_a_bc, 0, 8, 0x0A},
	{ld_a_de, 0, 8, 0x1A},
	/* LD A, [imm] (8-bit) */
	{ld_a_immd, 2, 16, 0xFA},
	/* LD [reg], A (8-bit) */
	{ld_bc_a, 0, 8, 0x02},
	{ld_de_a, 0, 8, 0x12},
	{ld_hl_a, 0, 8, 0x77},
	/* LD [imm], A (8-bit) */
	{ld_imm_a, 0, 16, 0xEA},
};

struct op * get_op(inst_t op) {
	struct op * op_desc = NULL;
	int i;
	for (i = 0; i < sizeof(OPS) / sizeof(struct op); i++) {
		if (OPS[i].opcode == op) {
			op_desc = &OPS[i];
			break;
		}
	}
	return op_desc;
}

void handle_op(struct op * op_desc, uint8_t * args, struct cpu_state * state) {
	op_desc->handler(args, state);
}

