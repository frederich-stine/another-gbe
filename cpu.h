#include <stdint.h>
#include "mmu.h"

#pragma once

struct cpu_struct {
	// main Z80 registers
	uint8_t a, b, c, d, e, f, h, l;
	uint16_t sp, pc;

	struct mmu_struct* mmu;

} cpu;

void reset_cpu(struct cpu_struct* cpu);

