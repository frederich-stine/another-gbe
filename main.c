#include "cartridge.h"
#include "cpu.h"
#include "opcode.h"
#include "mmu.h"
#include <stdio.h>

int main(int argc, char** argv)
{
	if(argc != 2)
	{
		printf("Error: Path to ROM is required\n");
		return 0;
	}

	printf("*** Allcoating MMU ***\n");
	cpu.mmu = allocate_mmu();
	
	printf("*** Loading cartridge from file ***\n");
	load_cartridge_from_file(argv[1], cpu.mmu);

	reset_cpu(&cpu);
	
	uint8_t opcode;

	while(1)
	{
		// Debug info
		printf("CPU:0x%04x \n", cpu.pc);
		
		opcode = read_byte(cpu.pc++, cpu.mmu);
		printf("opcode:0x%02x \n", opcode);
		
		run_opcode(&cpu, opcode);

		// Debug info
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
