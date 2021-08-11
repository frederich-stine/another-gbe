#include <stdio.h>
#include "cpu.h"

void reset_cpu(struct cpu_struct* cpu)
{
	for(int i=0; i<8; i++)
	{
		cpu->stand_regs[i] = 0;
	}

	cpu->sp = 0;
	cpu->pc = 0x100;

	printf("CPU:0x%04x \n", cpu->pc);
}
/*
void run_opcode(struct cpu_struct* cpu, uint8_t opcode)
{
	switch(opcode)
	{
		case 0x06:
			ldrn(cpu, opcode&0x38); break;
		case 0x0E:
			ldrn(cpu, opcode&0x38); break;
		case 0x16:
			ldrn(cpu, opcode&0x38); break;
		case 0x1E:
			ldrn(cpu, opcode&0x38); break;
		case 0x026:
			ldrn(cpu, opcode&0x38); break;
		case 0x2E:
			ldrn(cpu, opcode&0x38); break;
		case 0x3E:
			ldrn(cpu, opcode&0x38); break;
		case 0xC3:
			jp(cpu); break;
		case 0x80:
			add_reg(cpu, opcode&0x07); break;
		case 0x81:
			add_reg(cpu, opcode&0x07); break;
		case 0x82:
			add_reg(cpu, opcode&0x07); break;
		case 0x83:
			add_reg(cpu, opcode&0x07); break;
		case 0x84:
			add_reg(cpu, opcode&0x07); break;
		case 0x85:
			add_reg(cpu, opcode&0x07); break;
		case 0x87:
			add_reg(cpu, opcode&0x07); break;
	}
}
*/
