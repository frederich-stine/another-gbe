#pragma once

#include "cpu.h"
#include <stdint.h>

void nop(struct cpu_struct* cpu);
void jp(struct cpu_struct* cpu);
void add_reg(struct cpu_struct* cpu, uint8_t reg);
void ldrn(struct cpu_struct* cpu, uint8_t reg);

