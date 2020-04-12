#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "ops.h"
#include "mmu.h"

struct op {
	void (*handler)(uint8_t *, struct cpu_state *);
	uint8_t num_args;
	uint8_t num_ops;
	uint8_t cycles;
	inst_t opcode[MAX_OP_BYTES];
};

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

static inline void set_h_flag16(uint16_t new, uint16_t ori, struct cpu_state * state) {
	SET_FLAG_COND(H, new & 0xFFF < ori & 0xFFF);
}

static inline void set_c_flag16(uint16_t new, uint16_t ori, struct cpu_state * state) {
	SET_FLAG_COND(C, new < ori);
}

static inline void set_ch_flags16(uint16_t new, uint16_t ori, struct cpu_state * state) {
	set_h_flag16(new, ori, state);
	set_c_flag16(new, ori, state);
}

static inline void set_z_flag(uint8_t new, struct cpu_state * state) {
	SET_FLAG_COND(Z, new == 0);
}

static inline void set_z_flag16(uint16_t new, struct cpu_state * state) {
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

static void push(struct cpu_state * state, uint16_t val) {
	write16(state->regs.SP, val);
	state->regs.SP -= 2;
}

OP_HANDLER(push_af) {
	push(state, state->regs.AF);
}

OP_HANDLER(push_bc) {
	push(state, state->regs.BC);
}

OP_HANDLER(push_de) {
	push(state, state->regs.DE);
}

OP_HANDLER(push_hl) {
	push(state, state->regs.HL);
}

/* POP reg (16) */

static void pop(struct cpu_state * state, uint16_t * dst) {
	*dst = read16(state->regs.SP);
	state->regs.SP += 2;
}

OP_HANDLER(pop_af) {
	pop(state, &state->regs.AF);
}

OP_HANDLER(pop_bc) {
	pop(state, &state->regs.BC);
}

OP_HANDLER(pop_de) {
	pop(state, &state->regs.DE);
}

OP_HANDLER(pop_hl) {
	pop(state, &state->regs.HL);
}

/* ADD A, reg */

static void add(struct cpu_state * state, uint8_t val) {
	uint8_t ori = state->regs.A;
	state->regs.A += val;
	set_z_flag(state->regs.A, state);
	CLEAR_FLAG(N);
	set_ch_flags(state->regs.A, ori, state);
}

OP_HANDLER(add_a_a) {
	add(state, state->regs.A);
}

OP_HANDLER(add_a_b) {
	add(state, state->regs.B);
}

OP_HANDLER(add_a_c) {
	add(state, state->regs.C);
}

OP_HANDLER(add_a_d) {
	add(state, state->regs.D);
}

OP_HANDLER(add_a_e) {
	add(state, state->regs.E);
}

OP_HANDLER(add_a_h) {
	add(state, state->regs.H);
}

OP_HANDLER(add_a_l) {
	add(state, state->regs.L);
}

/* ADD A, [HL] */

OP_HANDLER(add_a_hl) {
	add(state, read8(state->regs.HL));
}

/* ADD A, imm */

OP_HANDLER(add_a_imm) {
	add(state, args[0]);
}

/* ADC A, reg */

static void adc(struct cpu_state * state, uint8_t val) {
	uint8_t ori = state->regs.A;
	state->regs.A += val + state->regs.flags.C;
	set_z_flag(state->regs.A, state);
	CLEAR_FLAG(N);
	set_ch_flags(state->regs.A, ori, state);
}

OP_HANDLER(adc_a_a) {
	adc(state, state->regs.A);
}

OP_HANDLER(adc_a_b) {
	adc(state, state->regs.B);
}

OP_HANDLER(adc_a_c) {
	adc(state, state->regs.C);
}

OP_HANDLER(adc_a_d) {
	adc(state, state->regs.D);
}

OP_HANDLER(adc_a_e) {
	adc(state, state->regs.E);
}

OP_HANDLER(adc_a_h) {
	adc(state, state->regs.H);
}

OP_HANDLER(adc_a_l) {
	adc(state, state->regs.L);
}

/* ADC A, [HL] */

OP_HANDLER(adc_a_hl) {
	adc(state, read8(state->regs.HL));
}

/* ADC A, imm */

OP_HANDLER(adc_a_imm) {
	adc(state, args[0]);
}

/* SUB A, reg */

static void sub(struct cpu_state * state, uint8_t val) {
	uint8_t ori = state->regs.A;
	state->regs.A -= val;
	set_z_flag(state->regs.A, state);
	SET_FLAG(N);
	set_ch_flags(ori, state->regs.A, state);
}

OP_HANDLER(sub_a) {
	sub(state, state->regs.A);
}

OP_HANDLER(sub_b) {
	sub(state, state->regs.B);
}

OP_HANDLER(sub_c) {
	sub(state, state->regs.C);
}

OP_HANDLER(sub_d) {
	sub(state, state->regs.D);
}

OP_HANDLER(sub_e) {
	sub(state, state->regs.E);
}

OP_HANDLER(sub_h) {
	sub(state, state->regs.H);
}

OP_HANDLER(sub_l) {
	sub(state, state->regs.L);
}

/* SUB A, [HL] */

OP_HANDLER(sub_hl) {
	sub(state, read8(state->regs.HL));
}

/* SUB A, imm */

OP_HANDLER(sub_imm) {
	sub(state, args[0]);
}

/* SBC A, reg */

static void sbc(struct cpu_state * state, uint8_t val) {
	uint8_t ori = state->regs.A;
	state->regs.A -= val + state->regs.flags.C;
	set_z_flag(state->regs.A, state);
	SET_FLAG(N);
	set_ch_flags(ori, state->regs.A, state);
}

OP_HANDLER(sbc_a) {
	sbc(state, state->regs.A);
}

OP_HANDLER(sbc_b) {
	sbc(state, state->regs.B);
}

OP_HANDLER(sbc_c) {
	sbc(state, state->regs.C);
}

OP_HANDLER(sbc_d) {
	sbc(state, state->regs.D);
}

OP_HANDLER(sbc_e) {
	sbc(state, state->regs.E);
}

OP_HANDLER(sbc_h) {
	sbc(state, state->regs.H);
}

OP_HANDLER(sbc_l) {
	sbc(state, state->regs.L);
}

/* SBC A, [HL] */

OP_HANDLER(sbc_hl) {
	sbc(state, read8(state->regs.HL));
}

/* SBC A, imm */

OP_HANDLER(sbc_imm) {
	sbc(state, args[0]);
}

/* AND A, reg */

static void and(struct cpu_state * state, uint8_t val) {
	uint8_t ori = state->regs.A;
	state->regs.A &= val;
	set_z_flag(state->regs.A, state);
	CLEAR_FLAG(N);
	SET_FLAG(H);
	CLEAR_FLAG(C);
}

OP_HANDLER(and_a) {
	and(state, state->regs.A);
}

OP_HANDLER(and_b) {
	and(state, state->regs.B);
}

OP_HANDLER(and_c) {
	and(state, state->regs.C);
}

OP_HANDLER(and_d) {
	and(state, state->regs.D);
}

OP_HANDLER(and_e) {
	and(state, state->regs.E);
}

OP_HANDLER(and_h) {
	and(state, state->regs.H);
}

OP_HANDLER(and_l) {
	and(state, state->regs.L);
}

/* AND A, [HL] */

OP_HANDLER(and_hl) {
	and(state, read8(state->regs.HL));
}

/* AND A, imm */

OP_HANDLER(and_imm) {
	and(state, args[0]);
}

/* OR A, reg */

static void or(struct cpu_state * state, uint8_t val) {
	uint8_t ori = state->regs.A;
	state->regs.A |= val;
	set_z_flag(state->regs.A, state);
	CLEAR_FLAG(N);
	CLEAR_FLAG(H);
	CLEAR_FLAG(C);
}

OP_HANDLER(or_a) {
	or(state, state->regs.A);
}

OP_HANDLER(or_b) {
	or(state, state->regs.B);
}

OP_HANDLER(or_c) {
	or(state, state->regs.C);
}

OP_HANDLER(or_d) {
	or(state, state->regs.D);
}

OP_HANDLER(or_e) {
	or(state, state->regs.E);
}

OP_HANDLER(or_h) {
	or(state, state->regs.H);
}

OP_HANDLER(or_l) {
	or(state, state->regs.L);
}

/* OR A, [HL] */

OP_HANDLER(or_hl) {
	or(state, read8(state->regs.HL));
}

/* OR A, imm */

OP_HANDLER(or_imm) {
	or(state, args[0]);
}

/* XOR A, reg */

static void xor(struct cpu_state * state, uint8_t val) {
	uint8_t ori = state->regs.A;
	state->regs.A ^= val;
	set_z_flag(state->regs.A, state);
	CLEAR_FLAG(N);
	CLEAR_FLAG(H);
	CLEAR_FLAG(C);
}

OP_HANDLER(xor_a) {
	xor(state, state->regs.A);
}

OP_HANDLER(xor_b) {
	xor(state, state->regs.B);
}

OP_HANDLER(xor_c) {
	xor(state, state->regs.C);
}

OP_HANDLER(xor_d) {
	xor(state, state->regs.D);
}

OP_HANDLER(xor_e) {
	xor(state, state->regs.E);
}

OP_HANDLER(xor_h) {
	xor(state, state->regs.H);
}

OP_HANDLER(xor_l) {
	xor(state, state->regs.L);
}

/* XOR A, [HL] */

OP_HANDLER(xor_hl) {
	xor(state, read8(state->regs.HL));
}

/* XOR A, imm */

OP_HANDLER(xor_imm) {
	xor(state, args[0]); 
}

/* CP A, reg */

static void cp(struct cpu_state * state, uint8_t val) {
	uint8_t ori = state->regs.A;
	uint8_t res = state->regs.A - val;
	set_z_flag(res, state);
	SET_FLAG(N);
	set_ch_flags(ori, res, state);
}

OP_HANDLER(cp_a) {
	cp(state, state->regs.A);
}

OP_HANDLER(cp_b) {
	cp(state, state->regs.B);
}

OP_HANDLER(cp_c) {
	cp(state, state->regs.C);
}

OP_HANDLER(cp_d) {
	cp(state, state->regs.D);
}

OP_HANDLER(cp_e) {
	cp(state, state->regs.E);
}

OP_HANDLER(cp_h) {
	cp(state, state->regs.H);
}

OP_HANDLER(cp_l) {
	cp(state, state->regs.L);
}

/* CP A, [HL] */

OP_HANDLER(cp_hl) {
	cp(state, read8(state->regs.HL));
}

/* CP A, imm */

OP_HANDLER(cp_imm) {
	cp(state, args[0]);
}

/* INC reg */

static void inc(struct cpu_state * state, uint8_t * dst) {
	uint8_t ori = *dst;
	*dst++;
	set_z_flag(*dst, state);
	CLEAR_FLAG(N);
	set_h_flag(*dst, ori, state);
}

OP_HANDLER(inc_a) {
	inc(state, &state->regs.A);
}

OP_HANDLER(inc_b) {
	inc(state, &state->regs.B);
}

OP_HANDLER(inc_c) {
	inc(state, &state->regs.C);
}

OP_HANDLER(inc_d) {
	inc(state, &state->regs.D);
}

OP_HANDLER(inc_e) {
	inc(state, &state->regs.E);
}

OP_HANDLER(inc_h) {
	inc(state, &state->regs.H);
}

OP_HANDLER(inc_l) {
	inc(state, &state->regs.L);
}

#define HLD_OP(callback) \
	do { \
		uint8_t val = read8(state->regs.HL); \
		callback(state, &val); \
		write8(state->regs.HL, val); \
	} while (0)

#define HLD_OP_BITS(callback, b) \
	do { \
		uint8_t val = read8(state->regs.HL); \
		callback(state, &val, b); \
		write8(state->regs.HL, val); \
	} while (0)

/* INC [HL] */

OP_HANDLER(inc_hld) {
	HLD_OP(inc);
}

/* DEC reg */

static void dec(struct cpu_state * state, uint8_t * dst) {
	uint8_t ori = *dst;
	*dst--;
	set_z_flag(*dst, state);
	SET_FLAG(N);
	set_h_flag(ori, *dst, state);
}

OP_HANDLER(dec_a) {
	dec(state, &state->regs.A);
}

OP_HANDLER(dec_b) {
	dec(state, &state->regs.B);
}

OP_HANDLER(dec_c) {
	dec(state, &state->regs.C);
}

OP_HANDLER(dec_d) {
	dec(state, &state->regs.D);
}

OP_HANDLER(dec_e) {
	dec(state, &state->regs.E);
}

OP_HANDLER(dec_h) {
	dec(state, &state->regs.H);
}

OP_HANDLER(dec_l) {
	dec(state, &state->regs.L);
}

/* DEC [HL] */

OP_HANDLER(dec_hld) {
	HLD_OP(dec);
}

/* ADD HL, reg (16) */

static void add16(struct cpu_state * state, uint16_t val) {
	uint16_t ori = state->regs.HL;
	state->regs.HL += val;
	CLEAR_FLAG(N);
	set_ch_flags16(state->regs.HL, ori, state);
}

OP_HANDLER(add_bc) {
	add16(state, state->regs.BC);
}

OP_HANDLER(add_de) {
	add16(state, state->regs.DE);
}

OP_HANDLER(add_hl) {
	add16(state, state->regs.HL);
}

OP_HANDLER(add_sp) {
	add16(state, state->regs.SP);
}

/* ADD SP, imm */

OP_HANDLER(add_sp_imm) {
	uint16_t ori = state->regs.SP;
	state->regs.SP += (int8_t)args[0];
	CLEAR_FLAG(Z);
	CLEAR_FLAG(N);
	if ((int8_t)args[0] >= 0) {
		set_ch_flags16(state->regs.SP, ori, state);
	}
	else {
		set_ch_flags16(ori, state->regs.SP, state);
	}
}

/* INC reg (16) */

OP_HANDLER(inc_bc) {
	state->regs.BC++;
}

OP_HANDLER(inc_de) {
	state->regs.DE++;
}

OP_HANDLER(inc_hl) {
	state->regs.HL++;
}

OP_HANDLER(inc_sp) {
	state->regs.SP++;
}

/* DEC reg (16) */

OP_HANDLER(dec_bc) {
	state->regs.BC--;
}

OP_HANDLER(dec_de) {
	state->regs.DE--;
}

OP_HANDLER(dec_hl) {
	state->regs.HL--;
}

OP_HANDLER(dec_sp) {
	state->regs.SP--;
}

/* SWAP reg */

static void swap(struct cpu_state * state, uint8_t * dst) {
	*dst = (*dst >> 4) | (*dst << 4);
	set_z_flag(*dst, state);
	CLEAR_FLAG(N);
	CLEAR_FLAG(H);
	CLEAR_FLAG(C);
}

OP_HANDLER(swap_a) {
	swap(state, &state->regs.A);
}

OP_HANDLER(swap_b) {
	swap(state, &state->regs.B);
}

OP_HANDLER(swap_c) {
	swap(state, &state->regs.C);
}

OP_HANDLER(swap_d) {
	swap(state, &state->regs.D);
}

OP_HANDLER(swap_e) {
	swap(state, &state->regs.E);
}

OP_HANDLER(swap_h) {
	swap(state, &state->regs.H);
}

OP_HANDLER(swap_l) {
	swap(state, &state->regs.L);
}

/* SWAP [HL] */

OP_HANDLER(swap_hl) {
	HLD_OP(swap);
}

/* DAA */

OP_HANDLER(daa) {
	uint8_t adjust = 0;
	CLEAR_FLAG(C);
	if (state->regs.flags.H || (!state->regs.flags.N && (state->regs.A & 0xF) > 9)) {
		adjust |= 0x06;
	}
	if (state->regs.flags.C || (!state->regs.flags.N && state->regs.A > 0x99)) {
		adjust |= 0x60;
		SET_FLAG(C);
	}
	state->regs.A += state->regs.flags.N ? -adjust : adjust;
	set_z_flag(state->regs.A, state);
	CLEAR_FLAG(H);
}

/* CPL */

OP_HANDLER(cpl) {
	state->regs.A = ~state->regs.A;
	SET_FLAG(N);
	SET_FLAG(H);
}

/* CCF */

OP_HANDLER(ccf) {
	state->regs.flags.C = !state->regs.flags.C;
	CLEAR_FLAG(N);
	CLEAR_FLAG(H);
}

/* SCF */

OP_HANDLER(scf) {
	SET_FLAG(C);
	CLEAR_FLAG(N);
	CLEAR_FLAG(H);
}

/* NOP */

OP_HANDLER(nop) {}

/* HALT */

OP_HANDLER(halt) {
	state->rflags.halted = 1;
}

/* STOP */

OP_HANDLER(stop) {
	state->rflags.stopped = 1;
}

/* EI/DI */

OP_HANDLER(di) {
	state->rflags.intr = INTR_DI;
}

OP_HANDLER(ei) {
	state->rflags.intr = INTR_EI;
}

/* RLC reg */

static void rlc(struct cpu_state * state, uint8_t * dst) {
	uint8_t msbit = *dst >> (sizeof(*dst) * 8 - 1);
	state->regs.flags.C = msbit;
	*dst <<= 1;
	*dst |= msbit;
	set_z_flag(*dst, state);
	CLEAR_FLAG(N);
	CLEAR_FLAG(H);
}

OP_HANDLER(rlc_a) {
	rlc(state, &state->regs.A);
}

OP_HANDLER(rlc_b) {
	rlc(state, &state->regs.B);
}

OP_HANDLER(rlc_c) {
	rlc(state, &state->regs.C);
}

OP_HANDLER(rlc_d) {
	rlc(state, &state->regs.D);
}

OP_HANDLER(rlc_e) {
	rlc(state, &state->regs.E);
}

OP_HANDLER(rlc_h) {
	rlc(state, &state->regs.H);
}

OP_HANDLER(rlc_l) {
	rlc(state, &state->regs.L);
}

/* RLC [HL] */

OP_HANDLER(rlc_hl) {
	HLD_OP(rlc);
}

/* RL reg */

static void rl(struct cpu_state * state, uint8_t * dst) {
	uint8_t cf = state->regs.flags.C;
	state->regs.flags.C = *dst >> (sizeof(*dst) * 8 - 1);
	*dst << 1;
	*dst |= cf;
	set_z_flag(*dst, state);
	CLEAR_FLAG(N);
	CLEAR_FLAG(H);
}

OP_HANDLER(rl_a) {
	rl(state, &state->regs.A);
}

OP_HANDLER(rl_b) {
	rl(state, &state->regs.B);
}

OP_HANDLER(rl_c) {
	rl(state, &state->regs.C);
}

OP_HANDLER(rl_d) {
	rl(state, &state->regs.D);
}

OP_HANDLER(rl_e) {
	rl(state, &state->regs.E);
}

OP_HANDLER(rl_h) {
	rl(state, &state->regs.H);
}

OP_HANDLER(rl_l) {
	rl(state, &state->regs.L);
}

/* RL [HL] */

OP_HANDLER(rl_hl) {
	HLD_OP(rl);
}

/* RRC reg */

static void rrc(struct cpu_state * state, uint8_t * dst) {
	uint8_t lsbit = *dst & 1;
	state->regs.flags.C = lsbit;
	*dst >>= 1;
	*dst |= lsbit << (sizeof(*dst) * 8 - 1);
	set_z_flag(*dst, state);
	CLEAR_FLAG(N);
	CLEAR_FLAG(H);
}

OP_HANDLER(rrc_a) {
	rrc(state, &state->regs.A);
}

OP_HANDLER(rrc_b) {
	rrc(state, &state->regs.B);
}

OP_HANDLER(rrc_c) {
	rrc(state, &state->regs.C);
}

OP_HANDLER(rrc_d) {
	rrc(state, &state->regs.D);
}

OP_HANDLER(rrc_e) {
	rrc(state, &state->regs.E);
}

OP_HANDLER(rrc_h) {
	rrc(state, &state->regs.H);
}

OP_HANDLER(rrc_l) {
	rrc(state, &state->regs.L);
}

/* RRC [HL] */

OP_HANDLER(rrc_hl) {
	HLD_OP(rrc);
}

/* RR reg */

static void rr(struct cpu_state * state, uint8_t * dst) {
	uint8_t cf = state->regs.flags.C;
	state->regs.flags.C = *dst & 1;
	*dst >>= 1;
	*dst |= cf << (sizeof(*dst) * 8 - 1);
	set_z_flag(*dst, state);
	CLEAR_FLAG(N);
	CLEAR_FLAG(H);
}

OP_HANDLER(rr_a) {
	rr(state, &state->regs.A);
}

OP_HANDLER(rr_b) {
	rr(state, &state->regs.B);
}

OP_HANDLER(rr_c) {
	rr(state, &state->regs.C);
}

OP_HANDLER(rr_d) {
	rr(state, &state->regs.D);
}

OP_HANDLER(rr_e) {
	rr(state, &state->regs.E);
}

OP_HANDLER(rr_h) {
	rr(state, &state->regs.H);
}

OP_HANDLER(rr_l) {
	rr(state, &state->regs.L);
}

/* RR [HL] */

OP_HANDLER(rr_hl) {
	HLD_OP(rr);
}

/* SLA reg */

static void sla(struct cpu_state * state, uint8_t * dst) {
	state->regs.flags.C = *dst >> (sizeof(*dst) * 8 - 1);
	*dst <<= 1;
	set_z_flag(*dst, state);
	CLEAR_FLAG(N);
	CLEAR_FLAG(H);
}

OP_HANDLER(sla_a) {
	sla(state, &state->regs.A);
}

OP_HANDLER(sla_b) {
	sla(state, &state->regs.B);
}

OP_HANDLER(sla_c) {
	sla(state, &state->regs.C);
}

OP_HANDLER(sla_d) {
	sla(state, &state->regs.D);
}

OP_HANDLER(sla_e) {
	sla(state, &state->regs.E);
}

OP_HANDLER(sla_h) {
	sla(state, &state->regs.H);
}

OP_HANDLER(sla_l) {
	sla(state, &state->regs.L);
}

/* SLA [HL] */

OP_HANDLER(sla_hl) {
	HLD_OP(sla);
}

/* SRA reg */

static void sra(struct cpu_state * state, uint8_t * dst) {
	uint8_t msbit = *dst & (1 << (sizeof(*dst) * 8 - 1));
	state->regs.flags.C = *dst & 1;
	*dst >>= 1;
	*dst |= msbit;
	set_z_flag(*dst, state);
	CLEAR_FLAG(N);
	CLEAR_FLAG(H);
}

OP_HANDLER(sra_a) {
	sra(state, &state->regs.A);
}

OP_HANDLER(sra_b) {
	sra(state, &state->regs.B);
}

OP_HANDLER(sra_c) {
	sra(state, &state->regs.C);
}

OP_HANDLER(sra_d) {
	sra(state, &state->regs.D);
}

OP_HANDLER(sra_e) {
	sra(state, &state->regs.E);
}

OP_HANDLER(sra_h) {
	sra(state, &state->regs.H);
}

OP_HANDLER(sra_l) {
	sra(state, &state->regs.L);
}

/* SRA [HL] */

OP_HANDLER(sra_hl) {
	HLD_OP(sra);
}

/* SRL reg */

static void srl(struct cpu_state * state, uint8_t * dst) {
	state->regs.flags.C = *dst & 1;
	*dst >>= 1;
	set_z_flag(*dst, state);
	CLEAR_FLAG(N);
	CLEAR_FLAG(H);
}

OP_HANDLER(srl_a) {
	srl(state, &state->regs.A);
}

OP_HANDLER(srl_b) {
	srl(state, &state->regs.B);
}

OP_HANDLER(srl_c) {
	srl(state, &state->regs.C);
}

OP_HANDLER(srl_d) {
	srl(state, &state->regs.D);
}

OP_HANDLER(srl_e) {
	srl(state, &state->regs.E);
}

OP_HANDLER(srl_h) {
	srl(state, &state->regs.H);
}

OP_HANDLER(srl_l) {
	srl(state, &state->regs.L);
}

/* SRL [HL] */

OP_HANDLER(srl_hl) {
	HLD_OP(srl);
}

/* BIT b, reg */

static void bit(struct cpu_state * state, uint8_t * dst, uint8_t b) {
	uint8_t bitval = (*dst << (sizeof(*dst) * 8 - 1 - b)) >> (sizeof(*dst) * 8 - 1);
	set_z_flag(bitval, state);
	CLEAR_FLAG(N);
	SET_FLAG(H);
}

/* BIT 0 reg */

OP_HANDLER(bit_0_a) {
	bit(state, &state->regs.A, 0);
}

OP_HANDLER(bit_0_b) {
	bit(state, &state->regs.B, 0);
}

OP_HANDLER(bit_0_c) {
	bit(state, &state->regs.C, 0);
}

OP_HANDLER(bit_0_d) {
	bit(state, &state->regs.D, 0);
}

OP_HANDLER(bit_0_e) {
	bit(state, &state->regs.E, 0);
}

OP_HANDLER(bit_0_h) {
	bit(state, &state->regs.H, 0);
}

OP_HANDLER(bit_0_l) {
	bit(state, &state->regs.L, 0);
}

/* BIT 0 [HL] */

OP_HANDLER(bit_0_hl) {
	HLD_OP_BITS(bit, 0);
}

/* BIT 1 reg */

OP_HANDLER(bit_1_a) {
	bit(state, &state->regs.A, 1);
}

OP_HANDLER(bit_1_b) {
	bit(state, &state->regs.B, 1);
}

OP_HANDLER(bit_1_c) {
	bit(state, &state->regs.C, 1);
}

OP_HANDLER(bit_1_d) {
	bit(state, &state->regs.D, 1);
}

OP_HANDLER(bit_1_e) {
	bit(state, &state->regs.E, 1);
}

OP_HANDLER(bit_1_h) {
	bit(state, &state->regs.H, 1);
}

OP_HANDLER(bit_1_l) {
	bit(state, &state->regs.L, 1);
}

/* BIT 1 [HL] */

OP_HANDLER(bit_1_hl) {
	HLD_OP_BITS(bit, 1);
}

/* BIT 2 reg */

OP_HANDLER(bit_2_a) {
	bit(state, &state->regs.A, 2);
}

OP_HANDLER(bit_2_b) {
	bit(state, &state->regs.B, 2);
}

OP_HANDLER(bit_2_c) {
	bit(state, &state->regs.C, 2);
}

OP_HANDLER(bit_2_d) {
	bit(state, &state->regs.D, 2);
}

OP_HANDLER(bit_2_e) {
	bit(state, &state->regs.E, 2);
}

OP_HANDLER(bit_2_h) {
	bit(state, &state->regs.H, 2);
}

OP_HANDLER(bit_2_l) {
	bit(state, &state->regs.L, 2);
}

/* BIT 2 [HL] */

OP_HANDLER(bit_2_hl) {
	HLD_OP_BITS(bit, 2);
}

/* BIT 3 reg */

OP_HANDLER(bit_3_a) {
	bit(state, &state->regs.A, 3);
}

OP_HANDLER(bit_3_b) {
	bit(state, &state->regs.B, 3);
}

OP_HANDLER(bit_3_c) {
	bit(state, &state->regs.C, 3);
}

OP_HANDLER(bit_3_d) {
	bit(state, &state->regs.D, 3);
}

OP_HANDLER(bit_3_e) {
	bit(state, &state->regs.E, 3);
}

OP_HANDLER(bit_3_h) {
	bit(state, &state->regs.H, 3);
}

OP_HANDLER(bit_3_l) {
	bit(state, &state->regs.L, 3);
}

/* BIT 3 [HL] */

OP_HANDLER(bit_3_hl) {
	HLD_OP_BITS(bit, 3);
}

/* BIT 4 reg */

OP_HANDLER(bit_4_a) {
	bit(state, &state->regs.A, 4);
}

OP_HANDLER(bit_4_b) {
	bit(state, &state->regs.B, 4);
}

OP_HANDLER(bit_4_c) {
	bit(state, &state->regs.C, 4);
}

OP_HANDLER(bit_4_d) {
	bit(state, &state->regs.D, 4);
}

OP_HANDLER(bit_4_e) {
	bit(state, &state->regs.E, 4);
}

OP_HANDLER(bit_4_h) {
	bit(state, &state->regs.H, 4);
}

OP_HANDLER(bit_4_l) {
	bit(state, &state->regs.L, 4);
}

/* BIT 4 [HL] */

OP_HANDLER(bit_4_hl) {
	HLD_OP_BITS(bit, 4);
}

/* BIT 5 reg */

OP_HANDLER(bit_5_a) {
	bit(state, &state->regs.A, 5);
}

OP_HANDLER(bit_5_b) {
	bit(state, &state->regs.B, 5);
}

OP_HANDLER(bit_5_c) {
	bit(state, &state->regs.C, 5);
}

OP_HANDLER(bit_5_d) {
	bit(state, &state->regs.D, 5);
}

OP_HANDLER(bit_5_e) {
	bit(state, &state->regs.E, 5);
}

OP_HANDLER(bit_5_h) {
	bit(state, &state->regs.H, 5);
}

OP_HANDLER(bit_5_l) {
	bit(state, &state->regs.L, 5);
}

/* BIT 5 [HL] */

OP_HANDLER(bit_5_hl) {
	HLD_OP_BITS(bit, 5);
}

/* BIT 6 reg */

OP_HANDLER(bit_6_a) {
	bit(state, &state->regs.A, 6);
}

OP_HANDLER(bit_6_b) {
	bit(state, &state->regs.B, 6);
}

OP_HANDLER(bit_6_c) {
	bit(state, &state->regs.C, 6);
}

OP_HANDLER(bit_6_d) {
	bit(state, &state->regs.D, 6);
}

OP_HANDLER(bit_6_e) {
	bit(state, &state->regs.E, 6);
}

OP_HANDLER(bit_6_h) {
	bit(state, &state->regs.H, 6);
}

OP_HANDLER(bit_6_l) {
	bit(state, &state->regs.L, 6);
}

/* BIT 6 [HL] */

OP_HANDLER(bit_6_hl) {
	HLD_OP_BITS(bit, 6);
}

/* BIT 7 reg */

OP_HANDLER(bit_7_a) {
	bit(state, &state->regs.A, 7);
}

OP_HANDLER(bit_7_b) {
	bit(state, &state->regs.B, 7);
}

OP_HANDLER(bit_7_c) {
	bit(state, &state->regs.C, 7);
}

OP_HANDLER(bit_7_d) {
	bit(state, &state->regs.D, 7);
}

OP_HANDLER(bit_7_e) {
	bit(state, &state->regs.E, 7);
}

OP_HANDLER(bit_7_h) {
	bit(state, &state->regs.H, 7);
}

OP_HANDLER(bit_7_l) {
	bit(state, &state->regs.L, 7);
}

/* BIT 7 [HL] */

OP_HANDLER(bit_7_hl) {
	HLD_OP_BITS(bit, 7);
}

/* SET b, reg */

static void set(struct cpu_state * state, uint8_t * dst, uint8_t b) {
	*dst |= 1 << b;
}

/* SET 0 reg */
    
OP_HANDLER(set_0_a) {
        set(state, &state->regs.A, 0);
}
        
OP_HANDLER(set_0_b) {
        set(state, &state->regs.B, 0);
}
        
OP_HANDLER(set_0_c) {
        set(state, &state->regs.C, 0);
}
        
OP_HANDLER(set_0_d) {
        set(state, &state->regs.D, 0);
}
        
OP_HANDLER(set_0_e) {
        set(state, &state->regs.E, 0);
}
        
OP_HANDLER(set_0_h) {
        set(state, &state->regs.H, 0);
}
        
OP_HANDLER(set_0_l) {
        set(state, &state->regs.L, 0);
}
        
/* SET 0 [HL] */

OP_HANDLER(set_0_hl) {
        HLD_OP_BITS(set, 0);
}
        
/* SET 1 reg */
    
OP_HANDLER(set_1_a) {
        set(state, &state->regs.A, 1);
}
        
OP_HANDLER(set_1_b) {
        set(state, &state->regs.B, 1);
}
        
OP_HANDLER(set_1_c) {
        set(state, &state->regs.C, 1);
}
        
OP_HANDLER(set_1_d) {
        set(state, &state->regs.D, 1);
}
        
OP_HANDLER(set_1_e) {
        set(state, &state->regs.E, 1);
}
        
OP_HANDLER(set_1_h) {
        set(state, &state->regs.H, 1);
}
        
OP_HANDLER(set_1_l) {
        set(state, &state->regs.L, 1);
}
        
/* SET 1 [HL] */

OP_HANDLER(set_1_hl) {
        HLD_OP_BITS(set, 1);
}
        
/* SET 2 reg */
    
OP_HANDLER(set_2_a) {
        set(state, &state->regs.A, 2);
}
        
OP_HANDLER(set_2_b) {
        set(state, &state->regs.B, 2);
}
        
OP_HANDLER(set_2_c) {
        set(state, &state->regs.C, 2);
}
        
OP_HANDLER(set_2_d) {
        set(state, &state->regs.D, 2);
}
        
OP_HANDLER(set_2_e) {
        set(state, &state->regs.E, 2);
}
        
OP_HANDLER(set_2_h) {
        set(state, &state->regs.H, 2);
}
        
OP_HANDLER(set_2_l) {
        set(state, &state->regs.L, 2);
}
        
/* SET 2 [HL] */

OP_HANDLER(set_2_hl) {
        HLD_OP_BITS(set, 2);
}
        
/* SET 3 reg */
    
OP_HANDLER(set_3_a) {
        set(state, &state->regs.A, 3);
}
        
OP_HANDLER(set_3_b) {
        set(state, &state->regs.B, 3);
}
        
OP_HANDLER(set_3_c) {
        set(state, &state->regs.C, 3);
}
        
OP_HANDLER(set_3_d) {
        set(state, &state->regs.D, 3);
}
        
OP_HANDLER(set_3_e) {
        set(state, &state->regs.E, 3);
}
        
OP_HANDLER(set_3_h) {
        set(state, &state->regs.H, 3);
}
        
OP_HANDLER(set_3_l) {
        set(state, &state->regs.L, 3);
}
        
/* SET 3 [HL] */

OP_HANDLER(set_3_hl) {
        HLD_OP_BITS(set, 3);
}
        
/* SET 4 reg */
    
OP_HANDLER(set_4_a) {
        set(state, &state->regs.A, 4);
}
        
OP_HANDLER(set_4_b) {
        set(state, &state->regs.B, 4);
}
        
OP_HANDLER(set_4_c) {
        set(state, &state->regs.C, 4);
}
        
OP_HANDLER(set_4_d) {
        set(state, &state->regs.D, 4);
}
        
OP_HANDLER(set_4_e) {
        set(state, &state->regs.E, 4);
}
        
OP_HANDLER(set_4_h) {
        set(state, &state->regs.H, 4);
}
        
OP_HANDLER(set_4_l) {
        set(state, &state->regs.L, 4);
}
        
/* SET 4 [HL] */

OP_HANDLER(set_4_hl) {
        HLD_OP_BITS(set, 4);
}
        
/* SET 5 reg */
    
OP_HANDLER(set_5_a) {
        set(state, &state->regs.A, 5);
}
        
OP_HANDLER(set_5_b) {
        set(state, &state->regs.B, 5);
}
        
OP_HANDLER(set_5_c) {
        set(state, &state->regs.C, 5);
}
        
OP_HANDLER(set_5_d) {
        set(state, &state->regs.D, 5);
}
        
OP_HANDLER(set_5_e) {
        set(state, &state->regs.E, 5);
}
        
OP_HANDLER(set_5_h) {
        set(state, &state->regs.H, 5);
}
        
OP_HANDLER(set_5_l) {
        set(state, &state->regs.L, 5);
}
        
/* SET 5 [HL] */

OP_HANDLER(set_5_hl) {
        HLD_OP_BITS(set, 5);
}
        
/* SET 6 reg */
    
OP_HANDLER(set_6_a) {
        set(state, &state->regs.A, 6);
}
        
OP_HANDLER(set_6_b) {
        set(state, &state->regs.B, 6);
}
        
OP_HANDLER(set_6_c) {
        set(state, &state->regs.C, 6);
}
        
OP_HANDLER(set_6_d) {
        set(state, &state->regs.D, 6);
}
        
OP_HANDLER(set_6_e) {
        set(state, &state->regs.E, 6);
}
        
OP_HANDLER(set_6_h) {
        set(state, &state->regs.H, 6);
}
        
OP_HANDLER(set_6_l) {
        set(state, &state->regs.L, 6);
}
        
/* SET 6 [HL] */

OP_HANDLER(set_6_hl) {
        HLD_OP_BITS(set, 6);
}
        
/* SET 7 reg */
    
OP_HANDLER(set_7_a) {
        set(state, &state->regs.A, 7);
}
        
OP_HANDLER(set_7_b) {
        set(state, &state->regs.B, 7);
}
        
OP_HANDLER(set_7_c) {
        set(state, &state->regs.C, 7);
}
        
OP_HANDLER(set_7_d) {
        set(state, &state->regs.D, 7);
}
        
OP_HANDLER(set_7_e) {
        set(state, &state->regs.E, 7);
}
        
OP_HANDLER(set_7_h) {
        set(state, &state->regs.H, 7);
}
        
OP_HANDLER(set_7_l) {
        set(state, &state->regs.L, 7);
}
        
/* SET 7 [HL] */

OP_HANDLER(set_7_hl) {
        HLD_OP_BITS(set, 7);
}

/* RES b, reg */

static void res(struct cpu_state * state, uint8_t * dst, uint8_t b) {
	*dst &= 0xFF ^ (1 << b);
}

/* RES 0, reg */
    
OP_HANDLER(res_0_a) {
        res(state, &state->regs.A, 0);
}
        
OP_HANDLER(res_0_b) {
        res(state, &state->regs.B, 0);
}
        
OP_HANDLER(res_0_c) {
        res(state, &state->regs.C, 0);
}
        
OP_HANDLER(res_0_d) {
        res(state, &state->regs.D, 0);
}
        
OP_HANDLER(res_0_e) {
        res(state, &state->regs.E, 0);
}
        
OP_HANDLER(res_0_h) {
        res(state, &state->regs.H, 0);
}
        
OP_HANDLER(res_0_l) {
        res(state, &state->regs.L, 0);
}
        
/* RES 0, [HL] */

OP_HANDLER(res_0_hl) {
        HLD_OP_BITS(res, 0);
}
        
/* RES 1, reg */
    
OP_HANDLER(res_1_a) {
        res(state, &state->regs.A, 1);
}
        
OP_HANDLER(res_1_b) {
        res(state, &state->regs.B, 1);
}
        
OP_HANDLER(res_1_c) {
        res(state, &state->regs.C, 1);
}
        
OP_HANDLER(res_1_d) {
        res(state, &state->regs.D, 1);
}
        
OP_HANDLER(res_1_e) {
        res(state, &state->regs.E, 1);
}
        
OP_HANDLER(res_1_h) {
        res(state, &state->regs.H, 1);
}
        
OP_HANDLER(res_1_l) {
        res(state, &state->regs.L, 1);
}
        
/* RES 1, [HL] */

OP_HANDLER(res_1_hl) {
        HLD_OP_BITS(res, 1);
}
        
/* RES 2, reg */
    
OP_HANDLER(res_2_a) {
        res(state, &state->regs.A, 2);
}
        
OP_HANDLER(res_2_b) {
        res(state, &state->regs.B, 2);
}
        
OP_HANDLER(res_2_c) {
        res(state, &state->regs.C, 2);
}
        
OP_HANDLER(res_2_d) {
        res(state, &state->regs.D, 2);
}
        
OP_HANDLER(res_2_e) {
        res(state, &state->regs.E, 2);
}
        
OP_HANDLER(res_2_h) {
        res(state, &state->regs.H, 2);
}
        
OP_HANDLER(res_2_l) {
        res(state, &state->regs.L, 2);
}
        
/* RES 2, [HL] */

OP_HANDLER(res_2_hl) {
        HLD_OP_BITS(res, 2);
}
        
/* RES 3, reg */
    
OP_HANDLER(res_3_a) {
        res(state, &state->regs.A, 3);
}
        
OP_HANDLER(res_3_b) {
        res(state, &state->regs.B, 3);
}
        
OP_HANDLER(res_3_c) {
        res(state, &state->regs.C, 3);
}
        
OP_HANDLER(res_3_d) {
        res(state, &state->regs.D, 3);
}
        
OP_HANDLER(res_3_e) {
        res(state, &state->regs.E, 3);
}
        
OP_HANDLER(res_3_h) {
        res(state, &state->regs.H, 3);
}
        
OP_HANDLER(res_3_l) {
        res(state, &state->regs.L, 3);
}
        
/* RES 3, [HL] */

OP_HANDLER(res_3_hl) {
        HLD_OP_BITS(res, 3);
}
        
/* RES 4, reg */
    
OP_HANDLER(res_4_a) {
        res(state, &state->regs.A, 4);
}
        
OP_HANDLER(res_4_b) {
        res(state, &state->regs.B, 4);
}
        
OP_HANDLER(res_4_c) {
        res(state, &state->regs.C, 4);
}
        
OP_HANDLER(res_4_d) {
        res(state, &state->regs.D, 4);
}
        
OP_HANDLER(res_4_e) {
        res(state, &state->regs.E, 4);
}
        
OP_HANDLER(res_4_h) {
        res(state, &state->regs.H, 4);
}
        
OP_HANDLER(res_4_l) {
        res(state, &state->regs.L, 4);
}
        
/* RES 4, [HL] */

OP_HANDLER(res_4_hl) {
        HLD_OP_BITS(res, 4);
}
        
/* RES 5, reg */
    
OP_HANDLER(res_5_a) {
        res(state, &state->regs.A, 5);
}
        
OP_HANDLER(res_5_b) {
        res(state, &state->regs.B, 5);
}
        
OP_HANDLER(res_5_c) {
        res(state, &state->regs.C, 5);
}
        
OP_HANDLER(res_5_d) {
        res(state, &state->regs.D, 5);
}
        
OP_HANDLER(res_5_e) {
        res(state, &state->regs.E, 5);
}
        
OP_HANDLER(res_5_h) {
        res(state, &state->regs.H, 5);
}
        
OP_HANDLER(res_5_l) {
        res(state, &state->regs.L, 5);
}
        
/* RES 5, [HL] */

OP_HANDLER(res_5_hl) {
        HLD_OP_BITS(res, 5);
}
        
/* RES 6, reg */
    
OP_HANDLER(res_6_a) {
        res(state, &state->regs.A, 6);
}
        
OP_HANDLER(res_6_b) {
        res(state, &state->regs.B, 6);
}
        
OP_HANDLER(res_6_c) {
        res(state, &state->regs.C, 6);
}
        
OP_HANDLER(res_6_d) {
        res(state, &state->regs.D, 6);
}
        
OP_HANDLER(res_6_e) {
        res(state, &state->regs.E, 6);
}
        
OP_HANDLER(res_6_h) {
        res(state, &state->regs.H, 6);
}
        
OP_HANDLER(res_6_l) {
        res(state, &state->regs.L, 6);
}
        
/* RES 6, [HL] */

OP_HANDLER(res_6_hl) {
        HLD_OP_BITS(res, 6);
}
        
/* RES 7, reg */
    
OP_HANDLER(res_7_a) {
        res(state, &state->regs.A, 7);
}
        
OP_HANDLER(res_7_b) {
        res(state, &state->regs.B, 7);
}
        
OP_HANDLER(res_7_c) {
        res(state, &state->regs.C, 7);
}
        
OP_HANDLER(res_7_d) {
        res(state, &state->regs.D, 7);
}
        
OP_HANDLER(res_7_e) {
        res(state, &state->regs.E, 7);
}
        
OP_HANDLER(res_7_h) {
        res(state, &state->regs.H, 7);
}
        
OP_HANDLER(res_7_l) {
        res(state, &state->regs.L, 7);
}
        
/* RES 7, [HL] */

OP_HANDLER(res_7_hl) {
        HLD_OP_BITS(res, 7);
}

/* JP imm */

OP_HANDLER(jp_imm) {
	state->regs.PC = *(ea_t *)args;
}

/* JP cond, imm */

#define COND_JP_IMM(cond) \
	do { \
		if (cond) { \
			state->regs.PC = *(ea_t *)args; \
		} \
	} while (0)

OP_HANDLER(jp_nz_imm) {
	COND_JP_IMM(!state->regs.flags.Z);
}

OP_HANDLER(jp_z_imm) {
	COND_JP_IMM(state->regs.flags.Z);
}

OP_HANDLER(jp_nc_imm) {
	COND_JP_IMM(!state->regs.flags.C);
}

OP_HANDLER(jp_c_imm) {
	COND_JP_IMM(state->regs.flags.C);
}

/* JP [HL] */

OP_HANDLER(jp_hl) {
	state->regs.PC = read16(state->regs.HL);
}

/* JR imm */

OP_HANDLER(jr_imm) {
	state->regs.PC += (int8_t)args[0] - 2;
}

/* JR cond, imm */

OP_HANDLER(jr_nz_imm) {
	*(uint16_t *)args = state->regs.PC + (int8_t)args[0] - 2;
	COND_JP_IMM(!state->regs.flags.Z);
}

OP_HANDLER(jr_z_imm) {
	*(uint16_t *)args = state->regs.PC + (int8_t)args[0] - 2;
	COND_JP_IMM(state->regs.flags.Z);
}

OP_HANDLER(jr_nc_imm) {
	*(uint16_t *)args = state->regs.PC + (int8_t)args[0] - 2;
	COND_JP_IMM(!state->regs.flags.C);
}

OP_HANDLER(jr_c_imm) {
	*(uint16_t *)args = state->regs.PC + (int8_t)args[0] - 2;
	COND_JP_IMM(!state->regs.flags.C);
}

/* CALL imm */

static void call(struct cpu_state * state, ea_t dst) {
	push(state, state->regs.PC);
	state->regs.PC = dst;
}

OP_HANDLER(call_imm) {
	call(state, *(ea_t *)args);
}

/* CALL cond, imm */

#define COND_CALL_IMM(cond) \
	do { \
		if (cond) { \
			call(state, *(ea_t *)args); \
		} \
	} while (0)

OP_HANDLER(call_nz_imm) {
	COND_CALL_IMM(!state->regs.flags.Z);
}

OP_HANDLER(call_z_imm) {
	COND_CALL_IMM(state->regs.flags.Z);
}

OP_HANDLER(call_nc_imm) {
	COND_CALL_IMM(!state->regs.flags.C);
}

OP_HANDLER(call_c_imm) {
	COND_CALL_IMM(state->regs.flags.C);
}

/* RST imm */

static void rst(struct cpu_state * state, uint8_t dst) {
	call(state, dst);
}

OP_HANDLER(rst_00) {
    rst(state, 0x00);
}
    
OP_HANDLER(rst_08) {
    rst(state, 0x08);
}
    
OP_HANDLER(rst_10) {
    rst(state, 0x10);
}
    
OP_HANDLER(rst_18) {
    rst(state, 0x18);
}
    
OP_HANDLER(rst_20) {
    rst(state, 0x20);
}
    
OP_HANDLER(rst_28) {
    rst(state, 0x28);
}
    
OP_HANDLER(rst_30) {
    rst(state, 0x30);
}
    
OP_HANDLER(rst_38) {
    rst(state, 0x38);
}

/* RET */

static void do_ret(struct cpu_state * state) {
	ea_t dst = 0;
	pop(state, &dst);
	state->regs.PC = dst;
}

OP_HANDLER(ret) {
	do_ret(state);
}

/* RET cond */

#define COND_RET(cond) \
	do { \
		if (cond) { \
			do_ret(state); \
		} \
	} while (0)

OP_HANDLER(ret_nz) {
	COND_RET(!state->regs.flags.Z);
}

OP_HANDLER(ret_z) {
	COND_RET(state->regs.flags.Z);
}

OP_HANDLER(ret_nc) {
	COND_RET(!state->regs.flags.C);
}

OP_HANDLER(ret_c) {
	COND_RET(state->regs.flags.C);
}

/* RETI */

OP_HANDLER(reti) {
	do_ret(state);
	state->rflags.intr = INTR_ENABLED;
}

/* List of all opcodes */

struct op OPS[] = {
	{ld_a_imm,    1, 1,    8,    {0x3E, 0x00}, },
	{ld_b_imm,    1, 1,    8,    {0x06, 0x00}, },
	{ld_c_imm,    1, 1,    8,    {0x0E, 0x00}, },
	{ld_d_imm,    1, 1,    8,    {0x16, 0x00}, },
	{ld_e_imm,    1, 1,    8,    {0x1E, 0x00}, },
	{ld_h_imm,    1, 1,    8,    {0x26, 0x00}, },
	{ld_l_imm,    1, 1,    8,    {0x2E, 0x00}, },
	{ld_a_a,      0, 1,    4,    {0x7F, 0x00}, },
	{ld_a_b,      0, 1,    4,    {0x78, 0x00}, },
	{ld_a_c,      0, 1,    4,    {0x79, 0x00}, },
	{ld_a_d,      0, 1,    4,    {0x7A, 0x00}, },
	{ld_a_e,      0, 1,    4,    {0x7B, 0x00}, },
	{ld_a_h,      0, 1,    4,    {0x7C, 0x00}, },
	{ld_a_l,      0, 1,    4,    {0x7D, 0x00}, },
	{ld_b_b,      0, 1,    4,    {0x40, 0x00}, },
	{ld_b_c,      0, 1,    4,    {0x41, 0x00}, },
	{ld_b_d,      0, 1,    4,    {0x42, 0x00}, },
	{ld_b_e,      0, 1,    4,    {0x43, 0x00}, },
	{ld_b_h,      0, 1,    4,    {0x44, 0x00}, },
	{ld_b_l,      0, 1,    4,    {0x45, 0x00}, },
	{ld_c_b,      0, 1,    4,    {0x48, 0x00}, },
	{ld_c_c,      0, 1,    4,    {0x49, 0x00}, },
	{ld_c_d,      0, 1,    4,    {0x4A, 0x00}, },
	{ld_c_e,      0, 1,    4,    {0x4B, 0x00}, },
	{ld_c_h,      0, 1,    4,    {0x4C, 0x00}, },
	{ld_c_l,      0, 1,    4,    {0x4D, 0x00}, },
	{ld_d_b,      0, 1,    4,    {0x50, 0x00}, },
	{ld_d_c,      0, 1,    4,    {0x51, 0x00}, },
	{ld_d_d,      0, 1,    4,    {0x52, 0x00}, },
	{ld_d_e,      0, 1,    4,    {0x53, 0x00}, },
	{ld_d_h,      0, 1,    4,    {0x54, 0x00}, },
	{ld_d_l,      0, 1,    4,    {0x55, 0x00}, },
	{ld_e_b,      0, 1,    4,    {0x58, 0x00}, },
	{ld_e_c,      0, 1,    4,    {0x59, 0x00}, },
	{ld_e_d,      0, 1,    4,    {0x5A, 0x00}, },
	{ld_e_e,      0, 1,    4,    {0x5B, 0x00}, },
	{ld_e_h,      0, 1,    4,    {0x5C, 0x00}, },
	{ld_e_l,      0, 1,    4,    {0x5D, 0x00}, },
	{ld_h_b,      0, 1,    4,    {0x60, 0x00}, },
	{ld_h_c,      0, 1,    4,    {0x61, 0x00}, },
	{ld_h_d,      0, 1,    4,    {0x62, 0x00}, },
	{ld_h_e,      0, 1,    4,    {0x63, 0x00}, },
	{ld_h_h,      0, 1,    4,    {0x64, 0x00}, },
	{ld_h_l,      0, 1,    4,    {0x65, 0x00}, },
	{ld_l_b,      0, 1,    4,    {0x68, 0x00}, },
	{ld_l_c,      0, 1,    4,    {0x69, 0x00}, },
	{ld_l_d,      0, 1,    4,    {0x6A, 0x00}, },
	{ld_l_e,      0, 1,    4,    {0x6B, 0x00}, },
	{ld_l_h,      0, 1,    4,    {0x6C, 0x00}, },
	{ld_l_l,      0, 1,    4,    {0x6D, 0x00}, },
	{ld_b_a,      0, 1,    4,    {0x47, 0x00}, },
	{ld_c_a,      0, 1,    4,    {0x4F, 0x00}, },
	{ld_d_a,      0, 1,    4,    {0x57, 0x00}, },
	{ld_e_a,      0, 1,    4,    {0x5F, 0x00}, },
	{ld_h_a,      0, 1,    4,    {0x67, 0x00}, },
	{ld_l_a,      0, 1,    4,    {0x6F, 0x00}, },
	{ld_a_hl,     0, 1,    8,    {0x7E, 0x00}, },
	{ld_b_hl,     0, 1,    8,    {0x46, 0x00}, },
	{ld_c_hl,     0, 1,    8,    {0x4E, 0x00}, },
	{ld_d_hl,     0, 1,    8,    {0x56, 0x00}, },
	{ld_e_hl,     0, 1,    8,    {0x5E, 0x00}, },
	{ld_h_hl,     0, 1,    8,    {0x66, 0x00}, },
	{ld_l_hl,     0, 1,    8,    {0x6E, 0x00}, },
	{ld_hl_b,     0, 1,    8,    {0x70, 0x00}, },
	{ld_hl_c,     0, 1,    8,    {0x71, 0x00}, },
	{ld_hl_d,     0, 1,    8,    {0x72, 0x00}, },
	{ld_hl_e,     0, 1,    8,    {0x73, 0x00}, },
	{ld_hl_h,     0, 1,    8,    {0x74, 0x00}, },
	{ld_hl_l,     0, 1,    8,    {0x75, 0x00}, },
	{ld_hld_imm,  1, 1,   12,    {0x36, 0x00}, },
	{ld_a_bc,     0, 1,    8,    {0x0A, 0x00}, },
	{ld_a_de,     0, 1,    8,    {0x1A, 0x00}, },
	{ld_a_immd,   2, 1,   16,    {0xFA, 0x00}, },
	{ld_bc_a,     0, 1,    8,    {0x02, 0x00}, },
	{ld_de_a,     0, 1,    8,    {0x12, 0x00}, },
	{ld_hl_a,     0, 1,    8,    {0x77, 0x00}, },
	{ld_imm_a,    0, 1,   16,    {0xEA, 0x00}, },
	{ld_a_ioc,    0, 1,    8,    {0xF2, 0x00}, },
	{ld_ioc_a,    0, 1,    8,    {0xE2, 0x00}, },
	{ldd_a_hl,    0, 1,    8,    {0x3A, 0x00}, },
	{ldd_hl_a,    0, 1,    8,    {0x32, 0x00}, },
	{ldi_a_hl,    0, 1,    8,    {0x2A, 0x00}, },
	{ldi_hl_a,    0, 1,    8,    {0x22, 0x00}, },
	{ldh_imm_a,   1, 1,   12,    {0xE0, 0x00}, },
	{ldh_a_imm,   1, 1,   12,    {0xF0, 0x00}, },
	{ld_bc_imm,   2, 1,   12,    {0x01, 0x00}, },
	{ld_de_imm,   2, 1,   12,    {0x11, 0x00}, },
	{ld_hl_imm,   2, 1,   12,    {0x21, 0x00}, },
	{ld_sp_imm,   2, 1,   12,    {0x31, 0x00}, },
	{ld_sp_hl,    0, 1,    8,    {0xF9, 0x00}, },
	{ldhl_sp_imm, 1, 1,   12,    {0xF8, 0x00}, },
	{ld_imm_sp,   2, 1,   20,    {0x08, 0x00}, },
	{push_af,     0, 1,   16,    {0xF5, 0x00}, },
	{push_bc,     0, 1,   16,    {0xC5, 0x00}, },
	{push_de,     0, 1,   16,    {0xD5, 0x00}, },
	{push_hl,     0, 1,   16,    {0xE5, 0x00}, },
	{pop_af,      0, 1,   12,    {0xF1, 0x00}, },
	{pop_bc,      0, 1,   12,    {0xC1, 0x00}, },
	{pop_de,      0, 1,   12,    {0xD1, 0x00}, },
	{pop_hl,      0, 1,   12,    {0xE1, 0x00}, },
	{add_a_a,     0, 1,    4,    {0x87, 0x00}, },
	{add_a_b,     0, 1,    4,    {0x80, 0x00}, },
	{add_a_c,     0, 1,    4,    {0x81, 0x00}, },
	{add_a_d,     0, 1,    4,    {0x82, 0x00}, },
	{add_a_e,     0, 1,    4,    {0x83, 0x00}, },
	{add_a_h,     0, 1,    4,    {0x84, 0x00}, },
	{add_a_l,     0, 1,    4,    {0x85, 0x00}, },
	{add_a_hl,    0, 1,    8,    {0x86, 0x00}, },
	{add_a_imm,   1, 1,    8,    {0xC6, 0x00}, },
	{adc_a_a,     0, 1,    4,    {0x8F, 0x00}, },
	{adc_a_b,     0, 1,    4,    {0x88, 0x00}, },
	{adc_a_c,     0, 1,    4,    {0x89, 0x00}, },
	{adc_a_d,     0, 1,    4,    {0x8A, 0x00}, },
	{adc_a_e,     0, 1,    4,    {0x8B, 0x00}, },
	{adc_a_h,     0, 1,    4,    {0x8C, 0x00}, },
	{adc_a_l,     0, 1,    4,    {0x8D, 0x00}, },
	{adc_a_hl,    0, 1,    8,    {0x8E, 0x00}, },
	{adc_a_imm,   1, 1,    8,    {0xCE, 0x00}, },
	{sub_a,       0, 1,    4,    {0x97, 0x00}, },
	{sub_b,       0, 1,    4,    {0x90, 0x00}, },
	{sub_c,       0, 1,    4,    {0x91, 0x00}, },
	{sub_d,       0, 1,    4,    {0x92, 0x00}, },
	{sub_e,       0, 1,    4,    {0x93, 0x00}, },
	{sub_h,       0, 1,    4,    {0x94, 0x00}, },
	{sub_l,       0, 1,    4,    {0x95, 0x00}, },
	{sub_hl,      0, 1,    8,    {0x96, 0x00}, },
	{sub_imm,     1, 1,    8,    {0xD6, 0x00}, },
	{sbc_a,       0, 1,    4,    {0x9F, 0x00}, },
	{sbc_b,       0, 1,    4,    {0x98, 0x00}, },
	{sbc_c,       0, 1,    4,    {0x99, 0x00}, },
	{sbc_d,       0, 1,    4,    {0x9A, 0x00}, },
	{sbc_e,       0, 1,    4,    {0x9B, 0x00}, },
	{sbc_h,       0, 1,    4,    {0x9C, 0x00}, },
	{sbc_l,       0, 1,    4,    {0x9D, 0x00}, },
	{sbc_hl,      0, 1,    8,    {0x9E, 0x00}, },
	{sbc_imm,     1, 1,    8,    {0xDE, 0x00}, },
	{and_a,       0, 1,    4,    {0xA7, 0x00}, },
	{and_b,       0, 1,    4,    {0xA0, 0x00}, },
	{and_c,       0, 1,    4,    {0xA1, 0x00}, },
	{and_d,       0, 1,    4,    {0xA2, 0x00}, },
	{and_e,       0, 1,    4,    {0xA3, 0x00}, },
	{and_h,       0, 1,    4,    {0xA4, 0x00}, },
	{and_l,       0, 1,    4,    {0xA5, 0x00}, },
	{and_hl,      0, 1,    8,    {0xA6, 0x00}, },
	{and_imm,     1, 1,    8,    {0xE6, 0x00}, },
	{or_a,        0, 1,    4,    {0xB7, 0x00}, },
	{or_b,        0, 1,    4,    {0xB0, 0x00}, },
	{or_c,        0, 1,    4,    {0xB1, 0x00}, },
	{or_d,        0, 1,    4,    {0xB2, 0x00}, },
	{or_e,        0, 1,    4,    {0xB3, 0x00}, },
	{or_h,        0, 1,    4,    {0xB4, 0x00}, },
	{or_l,        0, 1,    4,    {0xB5, 0x00}, },
	{or_hl,       0, 1,    8,    {0xB6, 0x00}, },
	{or_imm,      1, 1,    8,    {0xF6, 0x00}, },
	{xor_a,       0, 1,    4,    {0xAF, 0x00}, },
	{xor_b,       0, 1,    4,    {0xA8, 0x00}, },
	{xor_c,       0, 1,    4,    {0xA9, 0x00}, },
	{xor_d,       0, 1,    4,    {0xAA, 0x00}, },
	{xor_e,       0, 1,    4,    {0xAB, 0x00}, },
	{xor_h,       0, 1,    4,    {0xAC, 0x00}, },
	{xor_l,       0, 1,    4,    {0xAD, 0x00}, },
	{xor_hl,      0, 1,    8,    {0xAE, 0x00}, },
	{xor_imm,     1, 1,    8,    {0xEE, 0x00}, },
	{cp_a,        0, 1,    4,    {0xBF, 0x00}, },
	{cp_b,        0, 1,    4,    {0xB8, 0x00}, },
	{cp_c,        0, 1,    4,    {0xB9, 0x00}, },
	{cp_d,        0, 1,    4,    {0xBA, 0x00}, },
	{cp_e,        0, 1,    4,    {0xBB, 0x00}, },
	{cp_h,        0, 1,    4,    {0xBC, 0x00}, },
	{cp_l,        0, 1,    4,    {0xBD, 0x00}, },
	{cp_hl,       0, 1,    8,    {0xBE, 0x00}, },
	{cp_imm,      1, 1,    8,    {0xFE, 0x00}, },
	{inc_a,       0, 1,    4,    {0x3C, 0x00}, },
	{inc_b,       0, 1,    4,    {0x04, 0x00}, },
	{inc_c,       0, 1,    4,    {0x0C, 0x00}, },
	{inc_d,       0, 1,    4,    {0x14, 0x00}, },
	{inc_e,       0, 1,    4,    {0x1C, 0x00}, },
	{inc_h,       0, 1,    4,    {0x24, 0x00}, },
	{inc_l,       0, 1,    4,    {0x2C, 0x00}, },
	{inc_hld,     0, 1,   12,    {0x34, 0x00}, },
	{dec_a,       0, 1,    4,    {0x3D, 0x00}, },
	{dec_b,       0, 1,    4,    {0x05, 0x00}, },
	{dec_c,       0, 1,    4,    {0x0D, 0x00}, },
	{dec_d,       0, 1,    4,    {0x15, 0x00}, },
	{dec_e,       0, 1,    4,    {0x1D, 0x00}, },
	{dec_h,       0, 1,    4,    {0x25, 0x00}, },
	{dec_l,       0, 1,    4,    {0x2D, 0x00}, },
	{dec_hld,     0, 1,   12,    {0x35, 0x00}, },
	{add_bc,      0, 1,    8,    {0x09, 0x00}, },
	{add_de,      0, 1,    8,    {0x19, 0x00}, },
	{add_hl,      0, 1,    8,    {0x29, 0x00}, },
	{add_sp,      0, 1,    8,    {0x39, 0x00}, },
	{add_sp_imm,  1, 1,   16,    {0xE8, 0x00}, },
	{inc_bc,      0, 1,    8,    {0x03, 0x00}, },
	{inc_de,      0, 1,    8,    {0x13, 0x00}, },
	{inc_hl,      0, 1,    8,    {0x23, 0x00}, },
	{inc_sp,      0, 1,    8,    {0x33, 0x00}, },
	{dec_bc,      0, 1,    8,    {0x0B, 0x00}, },
	{dec_de,      0, 1,    8,    {0x1B, 0x00}, },
	{dec_hl,      0, 1,    8,    {0x2B, 0x00}, },
	{dec_sp,      0, 1,    8,    {0x3B, 0x00}, },
	{swap_a,      0, 2,    8,    {0xCB, 0x37}, },
	{swap_b,      0, 2,    8,    {0xCB, 0x30}, },
	{swap_c,      0, 2,    8,    {0xCB, 0x31}, },
	{swap_d,      0, 2,    8,    {0xCB, 0x32}, },
	{swap_e,      0, 2,    8,    {0xCB, 0x33}, },
	{swap_h,      0, 2,    8,    {0xCB, 0x34}, },
	{swap_l,      0, 2,    8,    {0xCB, 0x35}, },
	{swap_hl,     0, 2,   16,    {0xCB, 0x36}, },
	{daa,         0, 1,    4,    {0x27, 0x00}, },
	{cpl,         0, 1,    4,    {0x2F, 0x00}, },
	{ccf,         0, 1,    4,    {0x3F, 0x00}, },
	{scf,         0, 1,    4,    {0x37, 0x00}, },
	{nop,         0, 1,    4,    {0x00, 0x00}, },
	{halt,        0, 1,    4,    {0x76, 0x00}, },
	{stop,        0, 1,    4,    {0x10, 0x00}, },
	{di,          0, 1,    4,    {0xF3, 0x00}, },
	{ei,          0, 1,    4,    {0xFB, 0x00}, },
	{rlc_a,       0, 1,    4,    {0x07, 0x00}, },
	{rl_a,        0, 1,    4,    {0x17, 0x00}, },
	{rrc_a,       0, 1,    4,    {0x0F, 0x00}, },
	{rr_a,        0, 1,    4,    {0x1F, 0x00}, },
	{rlc_a,       0, 2,    8,    {0xCB, 0x07}, },
	{rlc_b,       0, 2,    8,    {0xCB, 0x00}, },
	{rlc_c,       0, 2,    8,    {0xCB, 0x01}, },
	{rlc_d,       0, 2,    8,    {0xCB, 0x02}, },
	{rlc_e,       0, 2,    8,    {0xCB, 0x03}, },
	{rlc_h,       0, 2,    8,    {0xCB, 0x04}, },
	{rlc_l,       0, 2,    8,    {0xCB, 0x05}, },
	{rlc_hl,      0, 2,   16,    {0xCB, 0x06}, },
	{rl_a,        0, 2,    8,    {0xCB, 0x17}, },
	{rl_b,        0, 2,    8,    {0xCB, 0x10}, },
	{rl_c,        0, 2,    8,    {0xCB, 0x11}, },
	{rl_d,        0, 2,    8,    {0xCB, 0x12}, },
	{rl_e,        0, 2,    8,    {0xCB, 0x13}, },
	{rl_h,        0, 2,    8,    {0xCB, 0x14}, },
	{rl_l,        0, 2,    8,    {0xCB, 0x15}, },
	{rl_hl,       0, 2,   16,    {0xCB, 0x16}, },
	{rrc_a,       0, 2,    8,    {0xCB, 0x0F}, },
	{rrc_b,       0, 2,    8,    {0xCB, 0x08}, },
	{rrc_c,       0, 2,    8,    {0xCB, 0x09}, },
	{rrc_d,       0, 2,    8,    {0xCB, 0x0A}, },
	{rrc_e,       0, 2,    8,    {0xCB, 0x0B}, },
	{rrc_h,       0, 2,    8,    {0xCB, 0x0C}, },
	{rrc_l,       0, 2,    8,    {0xCB, 0x0D}, },
	{rrc_hl,      0, 2,   16,    {0xCB, 0x0E}, },
	{rr_a,        0, 2,    8,    {0xCB, 0x1F}, },
	{rr_b,        0, 2,    8,    {0xCB, 0x18}, },
	{rr_c,        0, 2,    8,    {0xCB, 0x19}, },
	{rr_d,        0, 2,    8,    {0xCB, 0x1A}, },
	{rr_e,        0, 2,    8,    {0xCB, 0x1B}, },
	{rr_h,        0, 2,    8,    {0xCB, 0x1C}, },
	{rr_l,        0, 2,    8,    {0xCB, 0x1D}, },
	{rr_hl,       0, 2,   16,    {0xCB, 0x1E}, },
	{sla_a,       0, 2,    8,    {0xCB, 0x27}, },
	{sla_b,       0, 2,    8,    {0xCB, 0x20}, },
	{sla_c,       0, 2,    8,    {0xCB, 0x21}, },
	{sla_d,       0, 2,    8,    {0xCB, 0x22}, },
	{sla_e,       0, 2,    8,    {0xCB, 0x23}, },
	{sla_h,       0, 2,    8,    {0xCB, 0x24}, },
	{sla_l,       0, 2,    8,    {0xCB, 0x25}, },
	{sla_hl,      0, 2,   16,    {0xCB, 0x26}, },
	{sra_a,       0, 2,    8,    {0xCB, 0x2F}, },
	{sra_b,       0, 2,    8,    {0xCB, 0x28}, },
	{sra_c,       0, 2,    8,    {0xCB, 0x29}, },
	{sra_d,       0, 2,    8,    {0xCB, 0x2A}, },
	{sra_e,       0, 2,    8,    {0xCB, 0x2B}, },
	{sra_h,       0, 2,    8,    {0xCB, 0x2C}, },
	{sra_l,       0, 2,    8,    {0xCB, 0x2D}, },
	{sra_hl,      0, 2,   16,    {0xCB, 0x2E}, },
	{srl_a,       0, 2,    8,    {0xCB, 0x3F}, },
	{srl_b,       0, 2,    8,    {0xCB, 0x38}, },
	{srl_c,       0, 2,    8,    {0xCB, 0x39}, },
	{srl_d,       0, 2,    8,    {0xCB, 0x3A}, },
	{srl_e,       0, 2,    8,    {0xCB, 0x3B}, },
	{srl_h,       0, 2,    8,    {0xCB, 0x3C}, },
	{srl_l,       0, 2,    8,    {0xCB, 0x3D}, },
	{srl_hl,      0, 2,   16,    {0xCB, 0x3E}, },
	{bit_0_b,     0, 2,    8,    {0xCB, 0x40}, },
	{bit_0_c,     0, 2,    8,    {0xCB, 0x41}, },
	{bit_0_d,     0, 2,    8,    {0xCB, 0x42}, },
	{bit_0_e,     0, 2,    8,    {0xCB, 0x43}, },
	{bit_0_h,     0, 2,    8,    {0xCB, 0x44}, },
	{bit_0_l,     0, 2,    8,    {0xCB, 0x45}, },
	{bit_0_hl,    0, 2,   16,    {0xCB, 0x46}, },
	{bit_0_a,     0, 2,    8,    {0xCB, 0x47}, },
	{bit_1_b,     0, 2,    8,    {0xCB, 0x48}, },
	{bit_1_c,     0, 2,    8,    {0xCB, 0x49}, },
	{bit_1_d,     0, 2,    8,    {0xCB, 0x4A}, },
	{bit_1_e,     0, 2,    8,    {0xCB, 0x4B}, },
	{bit_1_h,     0, 2,    8,    {0xCB, 0x4C}, },
	{bit_1_l,     0, 2,    8,    {0xCB, 0x4D}, },
	{bit_1_hl,    0, 2,   16,    {0xCB, 0x4E}, },
	{bit_1_a,     0, 2,    8,    {0xCB, 0x4F}, },
	{bit_2_b,     0, 2,    8,    {0xCB, 0x50}, },
	{bit_2_c,     0, 2,    8,    {0xCB, 0x51}, },
	{bit_2_d,     0, 2,    8,    {0xCB, 0x52}, },
	{bit_2_e,     0, 2,    8,    {0xCB, 0x53}, },
	{bit_2_h,     0, 2,    8,    {0xCB, 0x54}, },
	{bit_2_l,     0, 2,    8,    {0xCB, 0x55}, },
	{bit_2_hl,    0, 2,   16,    {0xCB, 0x56}, },
	{bit_2_a,     0, 2,    8,    {0xCB, 0x57}, },
	{bit_3_b,     0, 2,    8,    {0xCB, 0x58}, },
	{bit_3_c,     0, 2,    8,    {0xCB, 0x59}, },
	{bit_3_d,     0, 2,    8,    {0xCB, 0x5A}, },
	{bit_3_e,     0, 2,    8,    {0xCB, 0x5B}, },
	{bit_3_h,     0, 2,    8,    {0xCB, 0x5C}, },
	{bit_3_l,     0, 2,    8,    {0xCB, 0x5D}, },
	{bit_3_hl,    0, 2,   16,    {0xCB, 0x5E}, },
	{bit_3_a,     0, 2,    8,    {0xCB, 0x5F}, },
	{bit_4_b,     0, 2,    8,    {0xCB, 0x60}, },
	{bit_4_c,     0, 2,    8,    {0xCB, 0x61}, },
	{bit_4_d,     0, 2,    8,    {0xCB, 0x62}, },
	{bit_4_e,     0, 2,    8,    {0xCB, 0x63}, },
	{bit_4_h,     0, 2,    8,    {0xCB, 0x64}, },
	{bit_4_l,     0, 2,    8,    {0xCB, 0x65}, },
	{bit_4_hl,    0, 2,   16,    {0xCB, 0x66}, },
	{bit_4_a,     0, 2,    8,    {0xCB, 0x67}, },
	{bit_5_b,     0, 2,    8,    {0xCB, 0x68}, },
	{bit_5_c,     0, 2,    8,    {0xCB, 0x69}, },
	{bit_5_d,     0, 2,    8,    {0xCB, 0x6A}, },
	{bit_5_e,     0, 2,    8,    {0xCB, 0x6B}, },
	{bit_5_h,     0, 2,    8,    {0xCB, 0x6C}, },
	{bit_5_l,     0, 2,    8,    {0xCB, 0x6D}, },
	{bit_5_hl,    0, 2,   16,    {0xCB, 0x6E}, },
	{bit_5_a,     0, 2,    8,    {0xCB, 0x6F}, },
	{bit_6_b,     0, 2,    8,    {0xCB, 0x70}, },
	{bit_6_c,     0, 2,    8,    {0xCB, 0x71}, },
	{bit_6_d,     0, 2,    8,    {0xCB, 0x72}, },
	{bit_6_e,     0, 2,    8,    {0xCB, 0x73}, },
	{bit_6_h,     0, 2,    8,    {0xCB, 0x74}, },
	{bit_6_l,     0, 2,    8,    {0xCB, 0x75}, },
	{bit_6_hl,    0, 2,   16,    {0xCB, 0x76}, },
	{bit_6_a,     0, 2,    8,    {0xCB, 0x77}, },
	{bit_7_b,     0, 2,    8,    {0xCB, 0x78}, },
	{bit_7_c,     0, 2,    8,    {0xCB, 0x79}, },
	{bit_7_d,     0, 2,    8,    {0xCB, 0x7A}, },
	{bit_7_e,     0, 2,    8,    {0xCB, 0x7B}, },
	{bit_7_h,     0, 2,    8,    {0xCB, 0x7C}, },
	{bit_7_l,     0, 2,    8,    {0xCB, 0x7D}, },
	{bit_7_hl,    0, 2,   16,    {0xCB, 0x7E}, },
	{bit_7_a,     0, 2,    8,    {0xCB, 0x7F}, },
	{set_0_b,     0, 2,    8,    {0xCB, 0xC0}, },
	{set_0_c,     0, 2,    8,    {0xCB, 0xC1}, },
	{set_0_d,     0, 2,    8,    {0xCB, 0xC2}, },
	{set_0_e,     0, 2,    8,    {0xCB, 0xC3}, },
	{set_0_h,     0, 2,    8,    {0xCB, 0xC4}, },
	{set_0_l,     0, 2,    8,    {0xCB, 0xC5}, },
	{set_0_hl,    0, 2,   16,    {0xCB, 0xC6}, },
	{set_0_a,     0, 2,    8,    {0xCB, 0xC7}, },
	{set_1_b,     0, 2,    8,    {0xCB, 0xC8}, },
	{set_1_c,     0, 2,    8,    {0xCB, 0xC9}, },
	{set_1_d,     0, 2,    8,    {0xCB, 0xCA}, },
	{set_1_e,     0, 2,    8,    {0xCB, 0xCB}, },
	{set_1_h,     0, 2,    8,    {0xCB, 0xCC}, },
	{set_1_l,     0, 2,    8,    {0xCB, 0xCD}, },
	{set_1_hl,    0, 2,   16,    {0xCB, 0xCE}, },
	{set_1_a,     0, 2,    8,    {0xCB, 0xCF}, },
	{set_2_b,     0, 2,    8,    {0xCB, 0xD0}, },
	{set_2_c,     0, 2,    8,    {0xCB, 0xD1}, },
	{set_2_d,     0, 2,    8,    {0xCB, 0xD2}, },
	{set_2_e,     0, 2,    8,    {0xCB, 0xD3}, },
	{set_2_h,     0, 2,    8,    {0xCB, 0xD4}, },
	{set_2_l,     0, 2,    8,    {0xCB, 0xD5}, },
	{set_2_hl,    0, 2,   16,    {0xCB, 0xD6}, },
	{set_2_a,     0, 2,    8,    {0xCB, 0xD7}, },
	{set_3_b,     0, 2,    8,    {0xCB, 0xD8}, },
	{set_3_c,     0, 2,    8,    {0xCB, 0xD9}, },
	{set_3_d,     0, 2,    8,    {0xCB, 0xDA}, },
	{set_3_e,     0, 2,    8,    {0xCB, 0xDB}, },
	{set_3_h,     0, 2,    8,    {0xCB, 0xDC}, },
	{set_3_l,     0, 2,    8,    {0xCB, 0xDD}, },
	{set_3_hl,    0, 2,   16,    {0xCB, 0xDE}, },
	{set_3_a,     0, 2,    8,    {0xCB, 0xDF}, },
	{set_4_b,     0, 2,    8,    {0xCB, 0xE0}, },
	{set_4_c,     0, 2,    8,    {0xCB, 0xE1}, },
	{set_4_d,     0, 2,    8,    {0xCB, 0xE2}, },
	{set_4_e,     0, 2,    8,    {0xCB, 0xE3}, },
	{set_4_h,     0, 2,    8,    {0xCB, 0xE4}, },
	{set_4_l,     0, 2,    8,    {0xCB, 0xE5}, },
	{set_4_hl,    0, 2,   16,    {0xCB, 0xE6}, },
	{set_4_a,     0, 2,    8,    {0xCB, 0xE7}, },
	{set_5_b,     0, 2,    8,    {0xCB, 0xE8}, },
	{set_5_c,     0, 2,    8,    {0xCB, 0xE9}, },
	{set_5_d,     0, 2,    8,    {0xCB, 0xEA}, },
	{set_5_e,     0, 2,    8,    {0xCB, 0xEB}, },
	{set_5_h,     0, 2,    8,    {0xCB, 0xEC}, },
	{set_5_l,     0, 2,    8,    {0xCB, 0xED}, },
	{set_5_hl,    0, 2,   16,    {0xCB, 0xEE}, },
	{set_5_a,     0, 2,    8,    {0xCB, 0xEF}, },
	{set_6_b,     0, 2,    8,    {0xCB, 0xF0}, },
	{set_6_c,     0, 2,    8,    {0xCB, 0xF1}, },
	{set_6_d,     0, 2,    8,    {0xCB, 0xF2}, },
	{set_6_e,     0, 2,    8,    {0xCB, 0xF3}, },
	{set_6_h,     0, 2,    8,    {0xCB, 0xF4}, },
	{set_6_l,     0, 2,    8,    {0xCB, 0xF5}, },
	{set_6_hl,    0, 2,   16,    {0xCB, 0xF6}, },
	{set_6_a,     0, 2,    8,    {0xCB, 0xF7}, },
	{set_7_b,     0, 2,    8,    {0xCB, 0xF8}, },
	{set_7_c,     0, 2,    8,    {0xCB, 0xF9}, },
	{set_7_d,     0, 2,    8,    {0xCB, 0xFA}, },
	{set_7_e,     0, 2,    8,    {0xCB, 0xFB}, },
	{set_7_h,     0, 2,    8,    {0xCB, 0xFC}, },
	{set_7_l,     0, 2,    8,    {0xCB, 0xFD}, },
	{set_7_hl,    0, 2,   16,    {0xCB, 0xFE}, },
	{set_7_a,     0, 2,    8,    {0xCB, 0xFF}, },
	{res_0_b,     0, 2,    8,    {0xCB, 0x80}, },
	{res_0_c,     0, 2,    8,    {0xCB, 0x81}, },
	{res_0_d,     0, 2,    8,    {0xCB, 0x82}, },
	{res_0_e,     0, 2,    8,    {0xCB, 0x83}, },
	{res_0_h,     0, 2,    8,    {0xCB, 0x84}, },
	{res_0_l,     0, 2,    8,    {0xCB, 0x85}, },
	{res_0_hl,    0, 2,   16,    {0xCB, 0x86}, },
	{res_0_a,     0, 2,    8,    {0xCB, 0x87}, },
	{res_1_b,     0, 2,    8,    {0xCB, 0x88}, },
	{res_1_c,     0, 2,    8,    {0xCB, 0x89}, },
	{res_1_d,     0, 2,    8,    {0xCB, 0x8A}, },
	{res_1_e,     0, 2,    8,    {0xCB, 0x8B}, },
	{res_1_h,     0, 2,    8,    {0xCB, 0x8C}, },
	{res_1_l,     0, 2,    8,    {0xCB, 0x8D}, },
	{res_1_hl,    0, 2,   16,    {0xCB, 0x8E}, },
	{res_1_a,     0, 2,    8,    {0xCB, 0x8F}, },
	{res_2_b,     0, 2,    8,    {0xCB, 0x90}, },
	{res_2_c,     0, 2,    8,    {0xCB, 0x91}, },
	{res_2_d,     0, 2,    8,    {0xCB, 0x92}, },
	{res_2_e,     0, 2,    8,    {0xCB, 0x93}, },
	{res_2_h,     0, 2,    8,    {0xCB, 0x94}, },
	{res_2_l,     0, 2,    8,    {0xCB, 0x95}, },
	{res_2_hl,    0, 2,   16,    {0xCB, 0x96}, },
	{res_2_a,     0, 2,    8,    {0xCB, 0x97}, },
	{res_3_b,     0, 2,    8,    {0xCB, 0x98}, },
	{res_3_c,     0, 2,    8,    {0xCB, 0x99}, },
	{res_3_d,     0, 2,    8,    {0xCB, 0x9A}, },
	{res_3_e,     0, 2,    8,    {0xCB, 0x9B}, },
	{res_3_h,     0, 2,    8,    {0xCB, 0x9C}, },
	{res_3_l,     0, 2,    8,    {0xCB, 0x9D}, },
	{res_3_hl,    0, 2,   16,    {0xCB, 0x9E}, },
	{res_3_a,     0, 2,    8,    {0xCB, 0x9F}, },
	{res_4_b,     0, 2,    8,    {0xCB, 0xA0}, },
	{res_4_c,     0, 2,    8,    {0xCB, 0xA1}, },
	{res_4_d,     0, 2,    8,    {0xCB, 0xA2}, },
	{res_4_e,     0, 2,    8,    {0xCB, 0xA3}, },
	{res_4_h,     0, 2,    8,    {0xCB, 0xA4}, },
	{res_4_l,     0, 2,    8,    {0xCB, 0xA5}, },
	{res_4_hl,    0, 2,   16,    {0xCB, 0xA6}, },
	{res_4_a,     0, 2,    8,    {0xCB, 0xA7}, },
	{res_5_b,     0, 2,    8,    {0xCB, 0xA8}, },
	{res_5_c,     0, 2,    8,    {0xCB, 0xA9}, },
	{res_5_d,     0, 2,    8,    {0xCB, 0xAA}, },
	{res_5_e,     0, 2,    8,    {0xCB, 0xAB}, },
	{res_5_h,     0, 2,    8,    {0xCB, 0xAC}, },
	{res_5_l,     0, 2,    8,    {0xCB, 0xAD}, },
	{res_5_hl,    0, 2,   16,    {0xCB, 0xAE}, },
	{res_5_a,     0, 2,    8,    {0xCB, 0xAF}, },
	{res_6_b,     0, 2,    8,    {0xCB, 0xB0}, },
	{res_6_c,     0, 2,    8,    {0xCB, 0xB1}, },
	{res_6_d,     0, 2,    8,    {0xCB, 0xB2}, },
	{res_6_e,     0, 2,    8,    {0xCB, 0xB3}, },
	{res_6_h,     0, 2,    8,    {0xCB, 0xB4}, },
	{res_6_l,     0, 2,    8,    {0xCB, 0xB5}, },
	{res_6_hl,    0, 2,   16,    {0xCB, 0xB6}, },
	{res_6_a,     0, 2,    8,    {0xCB, 0xB7}, },
	{res_7_b,     0, 2,    8,    {0xCB, 0xB8}, },
	{res_7_c,     0, 2,    8,    {0xCB, 0xB9}, },
	{res_7_d,     0, 2,    8,    {0xCB, 0xBA}, },
	{res_7_e,     0, 2,    8,    {0xCB, 0xBB}, },
	{res_7_h,     0, 2,    8,    {0xCB, 0xBC}, },
	{res_7_l,     0, 2,    8,    {0xCB, 0xBD}, },
	{res_7_hl,    0, 2,   16,    {0xCB, 0xBE}, },
	{res_7_a,     0, 2,    8,    {0xCB, 0xBF}, },
	{jp_imm,      2, 1,   12,    {0xC3, 0x00}, },
	{jp_nz_imm,   2, 1,   12,    {0xC2, 0x00}, },
	{jp_z_imm,    2, 1,   12,    {0xCA, 0x00}, },
	{jp_nc_imm,   2, 1,   12,    {0xD2, 0x00}, },
	{jp_c_imm,    2, 1,   12,    {0xDA, 0x00}, },
	{jp_hl,       0, 1,    4,    {0xE9, 0x00}, },
	{jr_imm,      1, 1,    8,    {0x18, 0x00}, },
	{jr_nz_imm,   1, 1,    8,    {0x20, 0x00}, },
	{jr_z_imm,    1, 1,    8,    {0x28, 0x00}, },
	{jr_nc_imm,   1, 1,    8,    {0x30, 0x00}, },
	{jr_c_imm,    1, 1,    8,    {0x38, 0x00}, },
	{call_imm,    2, 1,   12,    {0xCD, 0x00}, },
	{call_nz_imm, 2, 1,   12,    {0xC4, 0x00}, },
	{call_z_imm,  2, 1,   12,    {0xCC, 0x00}, },
	{call_nc_imm, 2, 1,   12,    {0xD4, 0x00}, },
	{call_c_imm,  2, 1,   12,    {0xDC, 0x00}, },
	{rst_00,      0, 1,   32,    {0xC7, 0x00}, },
	{rst_08,      0, 1,   32,    {0xCF, 0x00}, },
	{rst_10,      0, 1,   32,    {0xD7, 0x00}, },
	{rst_18,      0, 1,   32,    {0xDF, 0x00}, },
	{rst_20,      0, 1,   32,    {0xE7, 0x00}, },
	{rst_28,      0, 1,   32,    {0xEF, 0x00}, },
	{rst_30,      0, 1,   32,    {0xF7, 0x00}, },
	{rst_38,      0, 1,   32,    {0xFF, 0x00}, },
	{ret,         0, 1,    8,    {0xC9, 0x00}, },
	{ret_nz,      0, 1,    8,    {0xC0, 0x00}, },
	{ret_z,       0, 1,    8,    {0xC8, 0x00}, },
	{ret_nc,      0, 1,    8,    {0xD0, 0x00}, },
	{ret_c,       0, 1,    8,    {0xD8, 0x00}, },
	{reti,        0, 1,    8,    {0xD9, 0x00}, },
};

static struct op * find_by_op(uint8_t op_idx, inst_t * ops) {
	int i;
	for (i = 0; i < sizeof(OPS) / sizeof(struct op); i++) {
		if (memcmp(ops, OPS[i].opcode, op_idx) == 0) {
			return &OPS[i];
		}
	}
	return NULL;
}

cpu_ret_t handle_op(struct cpu_state * state) {
	struct op * op_desc = NULL;
	uint8_t num_ops = 0;
	inst_t ops[MAX_OP_BYTES] = {0};
	uint8_t args[MAX_OP_ARGS] = {0};
	do {
		ops[num_ops] = cpu_fetch(state);
		num_ops++;
		op_desc = find_by_op(num_ops, ops);
		if (op_desc == NULL) {
			fprintf(stderr, "Unrecognized opcode at %04X:", state->regs.PC);
			for (int i = 0; i < num_ops; i++) {
				fprintf(stderr, " %02X", ops[i]);
			}
			fprintf(stderr, "\n");
			return CPU_FAILURE;
		}
	} while (num_ops != op_desc->num_ops);
	for (int i = 0; i < op_desc->num_args; i++) {
		args[i] = cpu_fetch(state);
	}
	op_desc->handler(args, state);
	state->mclk += op_desc->cycles / 4;
	state->tclk += op_desc->cycles;
	return CPU_SUCCESS;
}

