test: mmu.h mmu.c main.c cartridge.h cartridge.c cpu.h cpu.c opcode.c opcode.h
	gcc main.c cpu.c mmu.c cartridge.c opcode.c -o test

