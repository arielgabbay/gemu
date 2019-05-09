#include <stdlib.h>

#include "ops.h"
#include "mmu.h"

#define OP_HANDLER(op) static void op(uint8_t * args, struct cpu_state * state)

/* LD reg, imm */

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

/* LD reg, reg */

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

/* LD reg, [HL] */

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

/* LD [HL], reg */

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

/* LD [HL], imm */

OP_HANDLER(ld_hld_imm) {
	write8(state->regs.HL, args[0]);
}

/* LD A, [reg] */

OP_HANDLER(ld_a_bc) {
	state->regs.A = read8(state->regs.BC);
}

OP_HANDLER(ld_a_de) {
	state->regs.A = read8(state->regs.DE);
}

/* LD A, [imm] */

OP_HANDLER(ld_a_immd) {
	state->regs.A = read8(*(uint16_t *)args);
}

/* LD [reg], A */

OP_HANDLER(ld_bc_a) {
	write8(state->regs.BC, state->regs.A);
}

OP_HANDLER(ld_de_a) {
	write8(state->regs.BC, state->regs.A);
}

OP_HANDLER(ld_hl_a) {
	write8(state->regs.HL, state->regs.A);
}

/* LD [imm], A */

OP_HANDLER(ld_imm_a) {
	write8(*(uint16_t *)args, state->regs.A);
}

/* LD A, [0xFF00 + C] */

OP_HANDLER(ld_a_ioc) {
	state->regs.A = read8(0xFF00 + state->regs.C);
}

/* LD [0xFF00 + C], A */

OP_HANDLER(ld_ioc_a) {
	write8(0xFF00 + state->regs.C, state->regs.A);
}

/* LDD A, [HL] */

OP_HANDLER(ldd_a_hl) {
	state->regs.A = read8(state->regs.HL);
	state->regs.HL--;
}

/* LDD [HL], A */

OP_HANDLER(ldd_hl_a) {
	write8(state->regs.HL, state->regs.A);
	state->regs.HL--;
}

/* LDI A, [HL] */

OP_HANDLER(ldi_a_hl) {
	state->regs.A = read8(state->regs.HL);
	state->regs.HL++;
}

/* LDI [HL], A */

OP_HANDLER(ldi_hl_a) {
	write8(state->regs.HL, state->regs.A);
	state->regs.HL++;
}

/* LDH [0xFF00 + imm], A */

OP_HANDLER(ldh_imm_a) {
	write8(0xFF00 + args[0], state->regs.A);
}

/* LDH A, [0xFF00 + imm] */

OP_HANDLER(ldh_a_imm) {
	state->regs.A = read8(0xFF00 + args[0]);
}

/* LD reg, imm (16) */

OP_HANDLER(ld_bc_imm) {
	state->regs.BC = *(uint16_t *)args;
}

OP_HANDLER(ld_de_imm) {
	state->regs.DE = *(uint16_t *)args;
}

OP_HANDLER(ld_hl_imm) {
	state->regs.HL = *(uint16_t *)args;
}

OP_HANDLER(ld_sp_imm) {
	state->regs.SP = *(uint16_t *)args;
}

/* LD SP, HL */

OP_HANDLER(ld_sp_hl) {
	state->regs.SP = state->regs.HL;
}

#define SET_FLAG_COND(flag, cond) state->regs.flags.flag = (cond) ? 1 : 0
#define CLEAR_FLAG(flag) state->regs.flags.flag = 0
#define SET_FLAG(flag) state->regs.flags.flag = 1

static inline void set_h_flag(uint8_t new, uint8_t ori, struct cpu_state * state) {
	SET_FLAG_COND(H, new & 0xF < ori & 0xF);
}

static inline void set_c_flag(uint8_t new, uint8_t ori, struct cpu_state * state) {
	SET_FLAG_COND(C, new < ori);
}

static inline void set_ch_flags(uint8_t new, uint8_t ori, struct cpu_state * state) {
	set_h_flag(new, ori, state);
	set_c_flag(new, ori, state);
}

static inline void set_z_flag(uint8_t new, struct cpu_state * state) {
	SET_FLAG_COND(Z, new == 0);
}

/* LD HL [SP + imm] */

OP_HANDLER(ldhl_sp_imm) {
	state->regs.HL = state->regs.SP + args[0];
	CLEAR_FLAG(Z);
	CLEAR_FLAG(N);
	set_ch_flags(state->regs.HL, state->regs.SP, state);
}

/* LD [imm], SP */

OP_HANDLER(ld_imm_sp) {
	write8(*(uint16_t *)args, state->regs.SP);
}

/* PUSH reg (16) */

OP_HANDLER(push_af) {
	write16(state->regs.SP, state->regs.AF);
	state->regs.SP -= 2;
}

OP_HANDLER(push_bc) {
	write16(state->regs.SP, state->regs.BC);
	state->regs.SP -= 2;
}

OP_HANDLER(push_de) {
	write16(state->regs.SP, state->regs.DE);
	state->regs.SP -= 2;
}

OP_HANDLER(push_hl) {
	write16(state->regs.SP, state->regs.HL);
	state->regs.SP -= 2;
}

/* POP reg (16) */

OP_HANDLER(pop_af) {
	state->regs.AF = read16(state->regs.SP);
	state->regs.SP += 2;
}

OP_HANDLER(pop_bc) {
	state->regs.BC = read16(state->regs.SP);
	state->regs.SP += 2;
}

OP_HANDLER(pop_de) {
	state->regs.DE = read16(state->regs.SP);
	state->regs.SP += 2;
}

OP_HANDLER(pop_hl) {
	state->regs.HL = read16(state->regs.SP);
	state->regs.SP += 2;
}

/* ADD A, reg */

OP_HANDLER(add_a_a) {
	uint8_t ori = state->regs.A;
	state->regs.A += state->regs.A;
	set_z_flag(state->regs.A, state);
	CLEAR_FLAG(N);
	set_ch_flags(state->regs.A, ori, state);
}

OP_HANDLER(add_a_b) {
	uint8_t ori = state->regs.A;
	state->regs.A += state->regs.B;
	set_z_flag(state->regs.A, state);
	CLEAR_FLAG(N);
	set_ch_flags(state->regs.A, ori, state);
}

OP_HANDLER(add_a_c) {
	uint8_t ori = state->regs.A;
	state->regs.A += state->regs.C;
	set_z_flag(state->regs.A, state);
	CLEAR_FLAG(N);
	set_ch_flags(state->regs.A, ori, state);
}

OP_HANDLER(add_a_d) {
	uint8_t ori = state->regs.A;
	state->regs.A += state->regs.D;
	set_z_flag(state->regs.A, state);
	CLEAR_FLAG(N);
	set_ch_flags(state->regs.A, ori, state);
}

OP_HANDLER(add_a_e) {
	uint8_t ori = state->regs.A;
	state->regs.A += state->regs.E;
	set_z_flag(state->regs.A, state);
	CLEAR_FLAG(N);
	set_ch_flags(state->regs.A, ori, state);
}

OP_HANDLER(add_a_h) {
	uint8_t ori = state->regs.A;
	state->regs.A += state->regs.H;
	set_z_flag(state->regs.A, state);
	CLEAR_FLAG(N);
	set_ch_flags(state->regs.A, ori, state);
}

OP_HANDLER(add_a_l) {
	uint8_t ori = state->regs.A;
	state->regs.A += state->regs.L;
	set_z_flag(state->regs.A, state);
	CLEAR_FLAG(N);
	set_ch_flags(state->regs.A, ori, state);
}

/* ADD A, [HL] */

OP_HANDLER(add_a_hl) {
	uint8_t ori = state->regs.A;
	state->regs.A += read8(state->regs.HL);
	set_z_flag(state->regs.A, state);
	CLEAR_FLAG(N);
	set_ch_flags(state->regs.A, ori, state);
}

/* ADD A, imm */

OP_HANDLER(add_a_imm) {
	uint8_t ori = state->regs.A;
	state->regs.A += args[0];
	set_z_flag(state->regs.A, state);
	CLEAR_FLAG(N);
	set_ch_flags(state->regs.A, ori, state);
}

/* ADC A, reg */

OP_HANDLER(adc_a_a) {
	uint8_t ori = state->regs.A;
	state->regs.A += state->regs.A + state->regs.flags.C;
	set_z_flag(state->regs.A, state);
	CLEAR_FLAG(N);
	set_ch_flags(state->regs.A, ori, state);
}

OP_HANDLER(adc_a_b) {
	uint8_t ori = state->regs.A;
	state->regs.A += state->regs.B + state->regs.flags.C;
	set_z_flag(state->regs.A, state);
	CLEAR_FLAG(N);
	set_ch_flags(state->regs.A, ori, state);
}

OP_HANDLER(adc_a_c) {
	uint8_t ori = state->regs.A;
	state->regs.A += state->regs.C + state->regs.flags.C;
	set_z_flag(state->regs.A, state);
	CLEAR_FLAG(N);
	set_ch_flags(state->regs.A, ori, state);
}

OP_HANDLER(adc_a_d) {
	uint8_t ori = state->regs.A;
	state->regs.A += state->regs.D + state->regs.flags.C;
	set_z_flag(state->regs.A, state);
	CLEAR_FLAG(N);
	set_ch_flags(state->regs.A, ori, state);
}

OP_HANDLER(adc_a_e) {
	uint8_t ori = state->regs.A;
	state->regs.A += state->regs.E + state->regs.flags.C;
	set_z_flag(state->regs.A, state);
	CLEAR_FLAG(N);
	set_ch_flags(state->regs.A, ori, state);
}

OP_HANDLER(adc_a_h) {
	uint8_t ori = state->regs.A;
	state->regs.A += state->regs.H + state->regs.flags.C;
	set_z_flag(state->regs.A, state);
	CLEAR_FLAG(N);
	set_ch_flags(state->regs.A, ori, state);
}

OP_HANDLER(adc_a_l) {
	uint8_t ori = state->regs.A;
	state->regs.A += state->regs.L + state->regs.flags.C;
	set_z_flag(state->regs.A, state);
	CLEAR_FLAG(N);
	set_ch_flags(state->regs.A, ori, state);
}

/* ADC A, [HL] */

OP_HANDLER(adc_a_hl) {
	uint8_t ori = state->regs.A;
	state->regs.A += read8(state->regs.HL) + state->regs.flags.C;
	set_z_flag(state->regs.A, state);
	CLEAR_FLAG(N);
	set_ch_flags(state->regs.A, ori, state);
}

/* ADC A, imm */

OP_HANDLER(adc_a_imm) {
	uint8_t ori = state->regs.A;
	state->regs.A += args[0] + state->regs.flags.C;
	set_z_flag(state->regs.A, state);
	CLEAR_FLAG(N);
	set_ch_flags(state->regs.A, ori, state);
}

/* SUB A, reg */

OP_HANDLER(sub_a) {
	uint8_t ori = state->regs.A;
	state->regs.A -= state->regs.A;
	set_z_flag(state->regs.A, state);
	SET_FLAG(N);
	set_ch_flags(ori, state->regs.A, state);
}

OP_HANDLER(sub_b) {
	uint8_t ori = state->regs.A;
	state->regs.A -= state->regs.B;
	set_z_flag(state->regs.A, state);
	SET_FLAG(N);
	set_ch_flags(ori, state->regs.A, state);
}

OP_HANDLER(sub_c) {
	uint8_t ori = state->regs.A;
	state->regs.A -= state->regs.C;
	set_z_flag(state->regs.A, state);
	SET_FLAG(N);
	set_ch_flags(ori, state->regs.A, state);
}

OP_HANDLER(sub_d) {
	uint8_t ori = state->regs.A;
	state->regs.A -= state->regs.D;
	set_z_flag(state->regs.A, state);
	SET_FLAG(N);
	set_ch_flags(ori, state->regs.A, state);
}

OP_HANDLER(sub_e) {
	uint8_t ori = state->regs.A;
	state->regs.A -= state->regs.E;
	set_z_flag(state->regs.A, state);
	SET_FLAG(N);
	set_ch_flags(ori, state->regs.A, state);
}

OP_HANDLER(sub_h) {
	uint8_t ori = state->regs.A;
	state->regs.A -= state->regs.H;
	set_z_flag(state->regs.A, state);
	SET_FLAG(N);
	set_ch_flags(ori, state->regs.A, state);
}

OP_HANDLER(sub_l) {
	uint8_t ori = state->regs.A;
	state->regs.A -= state->regs.L;
	set_z_flag(state->regs.A, state);
	SET_FLAG(N);
	set_ch_flags(ori, state->regs.A, state);
}

/* SUB A, [HL] */

OP_HANDLER(sub_hl) {
	uint8_t ori = state->regs.A;
	state->regs.A -= read8(state->regs.HL);
	set_z_flag(state->regs.A, state);
	SET_FLAG(N);
	set_ch_flags(ori, state->regs.A, state);
}

/* SUB A, imm */

OP_HANDLER(sub_imm) {
	uint8_t ori = state->regs.A;
	state->regs.A -= args[0];
	set_z_flag(state->regs.A, state);
	SET_FLAG(N);
	set_ch_flags(ori, state->regs.A, state);
}

struct op OPS[] = {
	{ld_a_imm, 1, 8, 0x3E},
	{ld_b_imm, 1, 8, 0x06},
	{ld_c_imm, 1, 8, 0x0E},
	{ld_d_imm, 1, 8, 0x16},
	{ld_e_imm, 1, 8, 0x1E},
	{ld_h_imm, 1, 8, 0x26},
	{ld_l_imm, 1, 8, 0x2E},
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
	{ld_a_hl, 0, 8, 0x7E},
	{ld_b_hl, 0, 8, 0x46},
	{ld_c_hl, 0, 8, 0x4E},
	{ld_d_hl, 0, 8, 0x56},
	{ld_e_hl, 0, 8, 0x5E},
	{ld_h_hl, 0, 8, 0x66},
	{ld_l_hl, 0, 8, 0x6E},
	{ld_hl_b, 0, 8, 0x70},
	{ld_hl_c, 0, 8, 0x71},
	{ld_hl_d, 0, 8, 0x72},
	{ld_hl_e, 0, 8, 0x73},
	{ld_hl_h, 0, 8, 0x74},
	{ld_hl_l, 0, 8, 0x75},
	{ld_hld_imm, 1, 12, 0x36},
	{ld_a_bc, 0, 8, 0x0A},
	{ld_a_de, 0, 8, 0x1A},
	{ld_a_immd, 2, 16, 0xFA},
	{ld_bc_a, 0, 8, 0x02},
	{ld_de_a, 0, 8, 0x12},
	{ld_hl_a, 0, 8, 0x77},
	{ld_imm_a, 0, 16, 0xEA},
	{ld_a_ioc, 0, 8, 0xF2},
	{ld_ioc_a, 0, 8, 0xE2},
	{ldd_a_hl, 0, 8, 0x3A},
	{ldd_hl_a, 0, 8, 0x32},
	{ldi_a_hl, 0, 8, 0x2A},
	{ldi_hl_a, 0, 8, 0x22},
	{ldh_imm_a, 1, 12, 0xE0},
	{ldh_a_imm, 1, 12, 0xF0},
	{ld_bc_imm, 2, 12, 0x01},
	{ld_de_imm, 2, 12, 0x11},
	{ld_hl_imm, 2, 12, 0x21},
	{ld_sp_imm, 2, 12, 0x31},
	{ld_sp_hl, 0, 8, 0xF9},
	{ldhl_sp_imm, 1, 12, 0xF8},
	{ld_imm_sp, 2, 20, 0x08},
	{push_af, 0, 16, 0xF5},
	{push_bc, 0, 16, 0xC5},
	{push_de, 0, 16, 0xD5},
	{push_hl, 0, 16, 0xE5},
	{pop_af, 0, 12, 0xF1},
	{pop_bc, 0, 12, 0xC1},
	{pop_de, 0, 12, 0xD1},
	{pop_hl, 0, 12, 0xE1},
	{add_a_a, 0, 4, 0x87},
	{add_a_b, 0, 4, 0x80},
	{add_a_c, 0, 4, 0x81},
	{add_a_d, 0, 4, 0x82},
	{add_a_e, 0, 4, 0x83},
	{add_a_h, 0, 4, 0x84},
	{add_a_l, 0, 4, 0x85},
	{add_a_hl, 0, 8, 0x86},
	{add_a_imm, 1, 8, 0xC6},
	{adc_a_a, 0, 4, 0x8F},
	{adc_a_b, 0, 4, 0x88},
	{adc_a_c, 0, 4, 0x89},
	{adc_a_d, 0, 4, 0x8A},
	{adc_a_e, 0, 4, 0x8B},
	{adc_a_h, 0, 4, 0x8C},
	{adc_a_l, 0, 4, 0x8D},
	{adc_a_hl, 0, 8, 0x8E},
	{adc_a_imm, 1, 8, 0xCE},
	{sub_a, 0, 4, 0x97},
	{sub_b, 0, 4, 0x90},
	{sub_c, 0, 4, 0x91},
	{sub_d, 0, 4, 0x92},
	{sub_e, 0, 4, 0x93},
	{sub_h, 0, 4, 0x94},
	{sub_l, 0, 4, 0x95},
	{sub_hl, 0, 8, 0x96},
	{sub_imm, 1, 8, 0xD6},
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

#include <stdio.h>

int main() {
	uint16_t i = 0;
	printf("number of ops: %lu\n", sizeof(OPS) / sizeof(struct op));
	for (i = 0; i <= 0xFF; i++) {
		int ctr = 0;
		for (int j = 0; j < sizeof(OPS) / sizeof(struct op); j++) {
			if (OPS[j].opcode == i) {
				ctr++;
			}
		}
		if (ctr > 1) {
			printf("%02X dup!\n", i);
			break;
		}
	}
}


