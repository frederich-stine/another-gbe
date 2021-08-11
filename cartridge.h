#pragma once

#include "mmu.h"

#define cart_rom_size 0x148
#define cart_ram_size 0x149


void load_cartridge_from_file(char* fname, struct mmu_struct* mmu);


