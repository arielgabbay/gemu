#ifndef __GEMU_CPU_H
#define __GEMU_CPU_H

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

#endif /* __GEMU_CPU_H */

