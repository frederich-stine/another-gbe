#include "cartridge.h"
#include "cpu.h"
#include "opcode.h"
#include "mmu.h"
#include <stdio.h>

int main()
{
	printf("*** Allcoating MMU ***\n");
	cpu.mmu = allocate_mmu();
	
	printf("*** Loading cartridge from file ***\n");
	load_cartridge_from_file("gb-custom-tests/test.gb", cpu.mmu);

	reset_cpu(&cpu);
	
	uint8_t opcode;

	while(1)
	{
		printf("CPU:0x%04x \n", cpu.pc);
		opcode = read_byte(cpu.pc++, cpu.mmu);

		printf("opcode:0x%02x \n", opcode);

		switch(opcode)
		{
			case 0x06:
				ldrn(&cpu, opcode&0x38); break;
			case 0x0E:
				ldrn(&cpu, opcode&0x38); break;
			case 0x16:
				ldrn(&cpu, opcode&0x38); break;
			case 0x1E:
				ldrn(&cpu, opcode&0x38); break;
			case 0x026:
				ldrn(&cpu, opcode&0x38); break;
			case 0x2E:
				ldrn(&cpu, opcode&0x38); break;
			case 0x3E:
				ldrn(&cpu, opcode&0x38); break;
			case 0xC3:
				jp(&cpu); break;
			case 0x80:
				add_reg(&cpu, opcode&0x07); break;
			case 0x81:
				add_reg(&cpu, opcode&0x07); break;
			case 0x82:
				add_reg(&cpu, opcode&0x07); break;
			case 0x83:
				add_reg(&cpu, opcode&0x07); break;
			case 0x84:
				add_reg(&cpu, opcode&0x07); break;
			case 0x85:
				add_reg(&cpu, opcode&0x07); break;
			case 0x87:
				add_reg(&cpu, opcode&0x07); break;
		}
		

		printf("Register a: 0x%02x\n", cpu.stand_regs[reg_a]);
		printf("Register b: 0x%02x\n", cpu.stand_regs[reg_b]);
		printf("Register c: 0x%02x\n", cpu.stand_regs[reg_c]);
		printf("Register d: 0x%02x\n", cpu.stand_regs[reg_d]);
		printf("Register e: 0x%02x\n", cpu.stand_regs[reg_e]);
		printf("Register f: 0x%02x\n", cpu.stand_regs[reg_f]);
		printf("Register h: 0x%02x\n", cpu.stand_regs[reg_h]);
		printf("Register l: 0x%02x\n", cpu.stand_regs[reg_l]);
		printf("Register sp: 0x%04x\n", cpu.sp);
		printf("Register pc: 0x%04x\n", cpu.pc);
	
		// Supposed to stop after every instruction
		scanf("Hit enter to run next command: \n");
		getchar();
	}

	printf("*** Deleting MMU ***\n");
	delete_mmu(cpu.mmu);

	return 0;
}

void wait()
{
	
}
