#pragma once

#include "cpu.h"
#include <stdint.h>

void nop(struct cpu_struct* cpu);
void jp(struct cpu_struct* cpu);
void jpnz(struct cpu_struct* cpu);
void jpz(struct cpu_struct* cpu);
void jpnc(struct cpu_struct* cpu);
void jpc(struct cpu_struct* cpu);
void jr(struct cpu_struct* cpu);
void jrnz(struct cpu_struct* cpu);
void jrz(struct cpu_struct* cpu);
void jrnc(struct cpu_struct* cpu);
void jrc(struct cpu_struct* cpu);
void add_reg(struct cpu_struct* cpu, uint8_t reg);
void adc_reg(struct cpu_struct* cpu, uint8_t reg);
void ldrn(struct cpu_struct* cpu, uint8_t reg);
void ld_reg(struct cpu_struct* cpu, uint8_t reg1, uint8_t reg2);
void sub_reg(struct cpu_struct* cpu, uint8_t reg);
void sbc_reg(struct cpu_struct* cpu, uint8_t reg);
void and_reg(struct cpu_struct* cpu, uint8_t reg);
void or_reg(struct cpu_struct* cpu, uint8_t reg);
void xor_reg(struct cpu_struct* cpu, uint8_t reg);
void cp_reg(struct cpu_struct* cpu, uint8_t reg);
void inc_reg(struct cpu_struct* cpu, uint8_t reg);
void inc_dreg(struct cpu_struct* cpu, uint8_t reg);
void inc_sp(struct cpu_struct* cpu);
void dec_reg(struct cpu_struct* cpu, uint8_t reg);
void dec_dreg(struct cpu_struct* cpu, uint8_t reg);
void dec_sp(struct cpu_struct* cpu);
void push(struct cpu_struct* cpu, uint8_t reg);
void pop(struct cpu_struct* cpu, uint8_t reg);
void push_af(struct cpu_struct* cpu);
void pop_af(struct cpu_struct* cpu);

