#pragma once

#include "cpu.h"
#include <stdint.h>

void nop(struct cpu_struct* cpu);
void jp(struct cpu_struct* cpu);
void jphl(struct cpu_struct* cpu);
void jpnz(struct cpu_struct* cpu);
void jpz(struct cpu_struct* cpu);
void jpnc(struct cpu_struct* cpu);
void jpc(struct cpu_struct* cpu);
void jr(struct cpu_struct* cpu);
void jrnz(struct cpu_struct* cpu);
void jrz(struct cpu_struct* cpu);
void jrnc(struct cpu_struct* cpu);
void jrc(struct cpu_struct* cpu);
void cpl(struct cpu_struct* cpu);
void ccf(struct cpu_struct* cpu);
void daa(struct cpu_struct* cpu);
void scf(struct cpu_struct* cpu);
void add_reg(struct cpu_struct* cpu, uint8_t reg);
void adc_reg(struct cpu_struct* cpu, uint8_t reg);
void ld_reg_imm(struct cpu_struct* cpu, uint8_t reg);
void ld_reg(struct cpu_struct* cpu, uint8_t reg1, uint8_t reg2);
void ld_dreg_imm(struct cpu_struct* cpu, uint8_t reg);
void ld_dreg_imm_sp(struct cpu_struct* cpu);
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
void call(struct cpu_struct* cpu);
void callnz(struct cpu_struct* cpu);
void callz(struct cpu_struct* cpu);
void callnc(struct cpu_struct* cpu);
void callc(struct cpu_struct* cpu);
void ret(struct cpu_struct* cpu);
void retnz(struct cpu_struct* cpu);
void retz(struct cpu_struct* cpu);
void retnc(struct cpu_struct* cpu);
void retc(struct cpu_struct* cpu);
void rst(struct cpu_struct* cpu, uint8_t offset);
void reti(struct cpu_struct* cpu);

void rlc(struct cpu_struct* cpu, uint8_t reg);
void rl(struct cpu_struct* cpu, uint8_t reg);
void rrc(struct cpu_struct* cpu, uint8_t reg);
void rr(struct cpu_struct* cpu, uint8_t reg);
