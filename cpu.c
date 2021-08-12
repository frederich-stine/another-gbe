#include <stdio.h>
#include "cpu.h"
#include "opcode.h"

void reset_cpu(struct cpu_struct* cpu)
{
	for(int i=0; i<8; i++)
	{
		cpu->stand_regs[i] = 0;
	}

	cpu->sp = 0xFFFE;
	cpu->pc = 0x0100;

	printf("CPU:0x%04x \n", cpu->pc);
}

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
		case 0x88:
			adc_reg(cpu, opcode&0x07); break;
		case 0x89:
			adc_reg(cpu, opcode&0x07); break;
		case 0x8A:
			adc_reg(cpu, opcode&0x07); break;
		case 0x8B:
			adc_reg(cpu, opcode&0x07); break;
		case 0x8C:
			adc_reg(cpu, opcode&0x07); break;
		case 0x8D:
			adc_reg(cpu, opcode&0x07); break;
		case 0x8F:
			adc_reg(cpu, opcode&0x07); break;
		case 0x90:
			sub_reg(cpu, opcode&0x07); break;
		case 0x91:
			sub_reg(cpu, opcode&0x07); break;
		case 0x92:
			sub_reg(cpu, opcode&0x07); break;
		case 0x93:
			sub_reg(cpu, opcode&0x07); break;
		case 0x94:
			sub_reg(cpu, opcode&0x07); break;
		case 0x95:
			sub_reg(cpu, opcode&0x07); break;
		case 0x97:
			sub_reg(cpu, opcode&0x07); break;
		case 0x98:
			sbc_reg(cpu, opcode&0x07); break;
		case 0x99:
			sbc_reg(cpu, opcode&0x07); break;
		case 0x9A:
			sbc_reg(cpu, opcode&0x07); break;
		case 0x9B:
			sbc_reg(cpu, opcode&0x07); break;
		case 0x9C:
			sbc_reg(cpu, opcode&0x07); break;
		case 0x9D:
			sbc_reg(cpu, opcode&0x07); break;
		case 0x9F:
			sbc_reg(cpu, opcode&0x07); break;
	}
}

