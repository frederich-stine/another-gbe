#pragma once

#include <stdint.h>
#include "mmu.h"

// Could instead implement separate registers for flags for
// slightly better performance
#define z_flag 0b10000000
#define n_flag 0b01000000
#define h_flag 0b00100000
#define c_flag 0b00010000

#define not_z_flag 0b01111111
#define not_n_flag 0b10111111
#define not_h_flag 0b11011111
#define not_c_flag 0b11101111

#define set_z_flag cpu->stand_regs[8] | z_flag
#define set_n_flag cpu->stand_regs[8] | n_flag 
#define set_h_flag cpu->stand_regs[8] | h_flag
#define set_c_flag cpu->stand_regs[8] | c_flag

#define reset_z_flag cpu->stand_regs[8] & not_z_flag
#define reset_n_flag cpu->stand_regs[8] & not_n_flag 
#define reset_h_flag cpu->stand_regs[8] & not_h_flag
#define reset_c_flag cpu->stand_regs[8] & not_c_flag

#define reg_a 7
#define reg_b 0
#define reg_c 1 
#define reg_d 2
#define reg_e 3
#define reg_m 6
#define reg_h 4
#define reg_l 5
#define reg_f 8

struct cpu_struct {
	// main Z80 registers
	// uint8_t a, b, c, d, e, f, h, l;
	// uint8_t b, c, d, e, h, l, m, a, f;
	uint8_t stand_regs[9];
	uint16_t sp, pc;

	struct mmu_struct* mmu;

}cpu;

void reset_cpu(struct cpu_struct* cpu);
void run_opcode(struct cpu_struct* cpu, uint8_t opcode);
