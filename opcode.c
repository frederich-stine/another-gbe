#include "opcode.h"

void nop(struct cpu_struct* cpu)
{
	return;
}

void jp(struct cpu_struct* cpu)
{
	cpu->pc = read_word(cpu->pc, cpu->mmu);
}

void add_reg(struct cpu_struct* cpu, uint8_t reg)
{
	uint16_t temp = cpu->stand_regs[reg_a] + cpu->stand_regs[reg] ;

	// Flag Calculation
	cpu->stand_regs[reg_f] = temp == 0 ? set_z_flag : reset_z_flag;
	cpu->stand_regs[reg_f] = reset_n_flag;
	cpu->stand_regs[reg_f] = (cpu->stand_regs[reg] ^ cpu->stand_regs[reg_a] ^ temp) & 0x10 ? set_h_flag : reset_h_flag;
	cpu->stand_regs[reg_f] = (temp>0xFF) ? set_c_flag : reset_c_flag;

	// Result pass
	cpu->stand_regs[reg_a] = temp;
}

void adc_reg(struct cpu_struct* cpu, uint8_t reg)
{
	uint16_t temp = cpu->stand_regs[reg_a] + cpu->stand_regs[reg];
	temp = (cpu->stand_regs[reg_f] & c_flag) ? ++temp : temp;

	// Flag Calculation
	cpu->stand_regs[reg_f] = temp == 0 ? set_z_flag : reset_z_flag;
	cpu->stand_regs[reg_f] = reset_n_flag;
	cpu->stand_regs[reg_f] = (cpu->stand_regs[reg] ^ cpu->stand_regs[reg_a] ^ temp) & 0x10 ? set_h_flag : reset_h_flag;
	cpu->stand_regs[reg_f] = (temp>0xFF) ? set_c_flag : reset_c_flag;

	// Result pass
	cpu->stand_regs[reg_a] = temp;
}

void sub_reg(struct cpu_struct* cpu, uint8_t reg)
{
	uint16_t temp = cpu->stand_regs[reg_a] - cpu->stand_regs[reg];

	// Flag Calculation
	cpu->stand_regs[reg_f] = temp == 0 ? set_z_flag : reset_z_flag;
	cpu->stand_regs[reg_f] = set_n_flag;
	cpu->stand_regs[reg_f] = (cpu->stand_regs[reg] ^ cpu->stand_regs[reg_a] ^ temp) & 0x10 ? set_h_flag : reset_h_flag;
	cpu->stand_regs[reg_f] = (temp>0xFF) ? set_c_flag : reset_c_flag;

	// Result pass
	cpu->stand_regs[reg_a] = temp;
}

void sbc_reg(struct cpu_struct* cpu, uint8_t reg)
{
	uint16_t temp = cpu->stand_regs[reg_a] - cpu->stand_regs[reg];
	temp = (cpu->stand_regs[reg_f] & c_flag) ? --temp : temp;

	// Flag Calculation
	cpu->stand_regs[reg_f] = temp == 0 ? set_z_flag : reset_z_flag;
	cpu->stand_regs[reg_f] = set_n_flag;
	cpu->stand_regs[reg_f] = (cpu->stand_regs[reg] ^ cpu->stand_regs[reg_a] ^ temp) & 0x10 ? set_h_flag : reset_h_flag;
	cpu->stand_regs[reg_f] = (temp>0xFF) ? set_c_flag : reset_c_flag;

	// Result pass
	cpu->stand_regs[reg_a] = temp;
}

void and_reg(struct cpu_struct* cpu, uint8_t reg)
{
	cpu->stand_regs[reg_a] = cpu->stand_regs[reg_a] & cpu->stand_regs[reg];

	// Flag Calculation
	cpu->stand_regs[reg_f] = cpu->stand_regs[reg_a] == 0 ? set_z_flag : reset_z_flag;
	cpu->stand_regs[reg_f] = reset_n_flag;
	cpu->stand_regs[reg_f] = set_h_flag;
	cpu->stand_regs[reg_f] = reset_c_flag; 
}

void or_reg(struct cpu_struct* cpu, uint8_t reg)
{
	cpu->stand_regs[reg_a] = cpu->stand_regs[reg_a] | cpu->stand_regs[reg];

	// Flag Calculation
	cpu->stand_regs[reg_f] = cpu->stand_regs[reg_a] == 0 ? set_z_flag : reset_z_flag;
	cpu->stand_regs[reg_f] = reset_n_flag;
	cpu->stand_regs[reg_f] = reset_h_flag;
	cpu->stand_regs[reg_f] = reset_c_flag; 
}

void xor_reg(struct cpu_struct* cpu, uint8_t reg)
{
	cpu->stand_regs[reg_a] = cpu->stand_regs[reg_a] ^ cpu->stand_regs[reg];

	// Flag Calculation
	cpu->stand_regs[reg_f] = cpu->stand_regs[reg_a] == 0 ? set_z_flag : reset_z_flag;
	cpu->stand_regs[reg_f] = reset_n_flag;
	cpu->stand_regs[reg_f] = reset_h_flag;
	cpu->stand_regs[reg_f] = reset_c_flag; 
}

void cp_reg(struct cpu_struct* cpu, uint8_t reg)
{
	uint16_t temp = cpu->stand_regs[reg_a] - cpu->stand_regs[reg];

	// Flag Calculation
	cpu->stand_regs[reg_f] = temp == 0 ? set_z_flag : reset_z_flag;
	cpu->stand_regs[reg_f] = set_n_flag;
	cpu->stand_regs[reg_f] = (cpu->stand_regs[reg] ^ cpu->stand_regs[reg_a] ^ temp) & 0x10 ? set_h_flag : reset_h_flag;
	cpu->stand_regs[reg_f] = (temp>0xFF) ? set_c_flag : reset_c_flag;
}

void ldrn(struct cpu_struct* cpu, uint8_t reg)
{
	reg = reg>>3;

	cpu->stand_regs[reg] = read_byte(cpu->pc++, cpu->mmu);
}

void ld_reg(struct cpu_struct* cpu, uint8_t reg1, uint8_t reg2)
{
	cpu->stand_regs[reg1>>3] = cpu->stand_regs[reg2];
}

void inc_reg(struct cpu_struct* cpu, uint8_t reg)
{
	reg = reg>>3;
	uint16_t temp = cpu->stand_regs[reg] + 1;

	// Flag Calculation
	cpu->stand_regs[reg_f] = temp == 0 ? set_z_flag : reset_z_flag;
	cpu->stand_regs[reg_f] = reset_n_flag;
	cpu->stand_regs[reg_f] = (cpu->stand_regs[reg] ^ cpu->stand_regs[reg_a] ^ temp) & 0x10 ? set_h_flag : reset_h_flag;

	// Result pass
	cpu->stand_regs[reg] = temp;
}

void dec_reg(struct cpu_struct* cpu, uint8_t reg)
{
	reg = reg>>3;
	uint16_t temp = cpu->stand_regs[reg] - 1;

	// Flag Calculation
	cpu->stand_regs[reg_f] = temp == 0 ? set_z_flag : reset_z_flag;
	cpu->stand_regs[reg_f] = set_n_flag;
	cpu->stand_regs[reg_f] = (cpu->stand_regs[reg] ^ cpu->stand_regs[reg_a] ^ temp) & 0x10 ? set_h_flag : reset_h_flag;

	// Result pass
	cpu->stand_regs[reg] = temp;
}
