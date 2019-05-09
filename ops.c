#include <stdlib.h>
#include <string.h>

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

/* INC [HL] */

OP_HANDLER(inc_hld) {
	uint8_t val = read8(state->regs.HL);
	inc(state, &val);
	write8(state->regs.HL, val);
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
	uint8_t val = read8(state->regs.HL);
	dec(state, &val);
	write8(state->regs.HL, val);
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
	uint8_t val = read8(state->regs.HL);
	swap(state, &val);
	write8(state->regs.HL, val);
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
			return CPU_FAILURE;
		}
	} while (num_ops != op_desc->num_ops);
	for (int i = 0; i < op_desc->num_args; i++) {
		args[i] = cpu_fetch(state);
	}
	op_desc->handler(args, state);
	return CPU_SUCCESS;
}

#include <stdio.h>

int main() {
	uint16_t i = 0;
	printf("number of ops: %lu\n", sizeof(OPS) / sizeof(struct op));
	for (i = 0; i <= 0xFF; i++) {
		int ctr = 0;
		for (int j = 0; j < sizeof(OPS) / sizeof(struct op); j++) {
			if (OPS[j].opcode[0] == i) {
				ctr++;
			}
		}
		if (ctr > 1) {
			printf("%02X dup!\n", i);
			break;
		}
	}
}


