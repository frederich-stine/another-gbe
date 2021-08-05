#include "cartridge.h"
#include "cpu.h"
#include "opcode.h"
#include "mmu.h"
#include <stdio.h>

void wait();

int main()
{
	printf("*** Allcoating MMU ***\n");
	cpu.mmu = allocate_mmu();
	
	printf("*** Loading cartridge from file ***\n");
	load_cartridge_from_file("gb-custom-tests/test.gb", cpu.mmu);

	reset_cpu(&cpu);
	
	uint8_t opcode, data;

	while(1)
	{
		printf("CPU:0x%04x \n", cpu.pc);
		opcode = read_byte(cpu.pc++, cpu.mmu);

		printf("opcode:0x%02x \n", opcode);

		switch(opcode)
		{
			case 0xC3:
				jp(&cpu);
				break;
		}
		switch(opcode & 0xF1)
		{
			case 0x80:
				addr(&cpu, opcode & 0x07);
		}
		switch(opcode & 0xC7)
		{
			case 0x06:
				ldrn(&cpu, opcode & 0x38);
		}

		printf("Register a: 0x%02x\n", cpu.a);
		printf("Register b: 0x%02x\n", cpu.b);
		printf("Register c: 0x%02x\n", cpu.c);
		printf("Register d: 0x%02x\n", cpu.d);
		printf("Register e: 0x%02x\n", cpu.e);
		printf("Register f: 0x%02x\n", cpu.f);
		printf("Register h: 0x%02x\n", cpu.h);
		printf("Register l: 0x%02x\n", cpu.l);
		printf("Register sp: 0x%04x\n", cpu.sp);
		printf("Register pc: 0x%04x\n", cpu.pc);
	
		// Supposed to stop after every instruction
		scanf("Hit enter to run next command: \n");	
	}

	/*	
	write_byte(0x1000, 244, mmu);
	data = read_byte(0x1000, mmu);
	printf("Read data: %d\n", data);

	write_byte(0x4500, 230, mmu);
	data = read_byte(0x4500, mmu);
	printf("Read data: %d\n", data);

	write_byte(0x8000, 12, mmu);
	data = read_byte(0x8000, mmu);
	printf("Read data: %d\n", data);

	data = read_byte(0x1000, mmu);
	printf("Read data: %d\n", data);

	*/

	data = read_byte(0x0100, cpu.mmu);
	printf("Read data: %d\n", data);

	printf("*** Deleting MMU ***\n");
	delete_mmu(cpu.mmu);

	return 0;
}

void wait()
{
	
}
