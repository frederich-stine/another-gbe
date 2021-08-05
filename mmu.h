#include <stdint.h>

#pragma once

struct mmu_struct {
	// first segment of ROM
	// 0x0000-0x3fff
	uint8_t* rom1;
	// second switchable bank of ROM
	// 0x4000-0x7fff
	uint8_t* rom2;
	// ram/bg maps
	// 0x8000-0xcfff
	uint8_t* ram1;
	// second switchable bank of ram
	// x0d000-0xdfff
	uint8_t* ram2;
	// ram/reseved hardware
	// 0xe000-0xffff
	uint8_t* reserved;
};

// mmu related functions
struct mmu_struct* allocate_mmu();
void delete_mmu(struct mmu_struct* mmu);
uint8_t read_byte(uint16_t addr, struct mmu_struct* mmu);
uint16_t read_word(uint16_t addr, struct mmu_struct* mmu);
void write_byte(uint16_t addr, uint8_t data, struct mmu_struct* mmu);




