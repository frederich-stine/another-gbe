#include "mmu.h"
#include <stdlib.h>
#include <stdio.h>

// dynamically allocate mmu
// does not account for switchable banks yet
struct mmu_struct* allocate_mmu()
{
	struct mmu_struct* mmu = malloc(sizeof(struct mmu_struct));

	mmu->rom1 = (uint8_t*) malloc(0x4000);
	mmu->rom2 = (uint8_t*) malloc(0x4000);
	mmu->ram1 = (uint8_t*) malloc(0x5000);
	mmu->ram2 = (uint8_t*) malloc(0x1000);
	mmu->reserved = (uint8_t*) malloc(0x2000);

	return mmu;
}

// delete allocated mmu
void delete_mmu(struct mmu_struct* mmu)
{
	free(mmu->rom1);
	free(mmu->rom2);
	free(mmu->ram1);
	free(mmu->ram2);
	free(mmu->reserved);

	free(mmu);
}

uint8_t read_byte(uint16_t addr, struct mmu_struct* mmu)
{
	uint16_t mask_addr = addr & 0xF000;
	switch(mask_addr)
	{
		case 0x0000:
		case 0x1000:
		case 0x2000:
		case 0x3000:
			return (mmu->rom1[addr]);
		case 0x4000:
		case 0x5000:
		case 0x6000:
		case 0x7000:
			return (mmu->rom2[addr-0x4000]);
		case 0x8000:
		case 0x9000:
		case 0xA000:
		case 0xB000:
		case 0xC000:
			return (mmu->ram1[addr-0x8000]);
		case 0xD000:
			return (mmu->ram2[addr-0xD000]);
		case 0xE000:
		case 0xF000:
			return (mmu->reserved[addr-0xE000]);
	}
}

void write_byte(uint16_t addr, uint8_t data, struct mmu_struct* mmu)
{
	// need to implement write protection
	uint16_t mask_addr = addr & 0xF000;
	switch(mask_addr)
	{
		case 0x0000:
		case 0x1000:
		case 0x2000:
		case 0x3000:
			mmu->rom1[addr] = data;
		case 0x4000:
		case 0x5000:
		case 0x6000:
		case 0x7000:
			mmu->rom2[addr-0x4000] = data;
		case 0x8000:
		case 0x9000:
		case 0xA000:
		case 0xB000:
		case 0xC000:
			mmu->ram1[addr-0x8000] = data;
		case 0xD000:
			mmu->ram2[addr-0xD000] = data;
		case 0xE000:
		case 0xF000:
			mmu->reserved[addr-0xE000] = data;
	}
}

uint16_t read_word(uint16_t addr, struct mmu_struct* mmu)
{
	return(read_byte(addr, mmu) + (read_byte(addr+1, mmu) << 8));
}

void write_word(uint16_t addr, uint16_t data, struct mmu_struct* mmu)
{
	write_byte(addr, (uint8_t) data, mmu);
	write_byte(addr+1, (uint8_t) (data>>8), mmu);
}
