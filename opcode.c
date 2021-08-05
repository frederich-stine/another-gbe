#include "opcode.h"

void nop(struct cpu_struct* cpu)
{
	return;
}

void jp(struct cpu_struct* cpu)
{
	cpu->pc = read_word(cpu->pc, cpu->mmu);
}

void addr(struct cpu_struct* cpu, uint8_t reg)
{
	switch(reg)
	{
		case 0x00:
			cpu->a = cpu->a + cpu->b;
		case 0x01:
			cpu->a = cpu->a + cpu->c;
		case 0x02:
			cpu->a = cpu->a + cpu->d;
		case 0x03:
			cpu->a = cpu->a + cpu->e;
		case 0x04:
			cpu->a = cpu->a + cpu->h;
		case 0x05:
			cpu->a = cpu->a + cpu->l;
		case 0x07:
			cpu->a = cpu->a + cpu->a;
	}

	// need to do flag register
	
}

void ldrn(struct cpu_struct* cpu, uint8_t reg)
{
	switch(reg>>3)
	{
		case 0x00:
			cpu->a = read_byte(cpu->pc+1, cpu->mmu);
		case 0x01:
			cpu->c = read_byte(cpu->pc+1, cpu->mmu);
		case 0x02:
			cpu->d = read_byte(cpu->pc+1, cpu->mmu);
		case 0x03:
			cpu->e = read_byte(cpu->pc+1, cpu->mmu);
		case 0x04:
			cpu->h = read_byte(cpu->pc+1, cpu->mmu);
		case 0x05:
			cpu->l = read_byte(cpu->pc+1, cpu->mmu);
		case 0x07:
			cpu->a = read_byte(cpu->pc+1, cpu->mmu);
	}
}
