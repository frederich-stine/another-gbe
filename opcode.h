#include "cpu.h"
#include <stdint.h>

#pragma once

void nop(struct cpu_struct* cpu);
void jp(struct cpu_struct* cpu);
void addr(struct cpu_struct* cpu, uint8_t reg);
void ldrn(struct cpu_struct* cpu, uint8_t reg);


