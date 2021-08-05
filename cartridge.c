#include <stdio.h>
#include "cartridge.h"

// only support 32kB ROMS
void load_cartridge_from_file(char* fname, struct mmu_struct* mmu)
{
	FILE* rom_file;
	rom_file = fopen(fname, "rb");

	// need exception thrown here
	if(rom_file == NULL)
	{
		printf("Error: File name invalid\n");
		return;

	}

	fread(mmu->rom1, 0x4000, 1, rom_file);

	// check to make sure 32kB ROM for now
	if(mmu->rom1[cart_rom_size] != 0)
	{
		printf("Error: ROMs over 32kB not supported\n");
		return;
	}
	
	fread(mmu->rom2, 0x4000, 1, rom_file);

	fclose(rom_file);
}
