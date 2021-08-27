#include "opcode.h"
#include <stdio.h>

void nop(struct cpu_struct* cpu)
{
	return;
}

void jp(struct cpu_struct* cpu)
{
	cpu->pc = read_word(cpu->pc, cpu->mmu);
}

void jpnz(struct cpu_struct* cpu)
{
	if(cpu->stand_regs[reg_f] & z_flag)
	{
		cpu->pc = cpu->pc + 2;
		return;
	}
	cpu->pc = read_word(cpu->pc, cpu->mmu);
}

void jpz(struct cpu_struct* cpu)
{
	if(cpu->stand_regs[reg_f] & z_flag)
	{
		cpu->pc = read_word(cpu->pc, cpu->mmu);
		return;
	}
	cpu->pc = cpu->pc+2;
}

void jpnc(struct cpu_struct* cpu)
{
	if(cpu->stand_regs[reg_f] & c_flag)
	{
		cpu->pc = cpu->pc + 2;
		return;
	}
	cpu->pc = read_word(cpu->pc, cpu->mmu);
}

void jpc(struct cpu_struct* cpu)
{
	if(cpu->stand_regs[reg_f] & c_flag)
	{
		cpu->pc = read_word(cpu->pc, cpu->mmu);
		return;
	}
	cpu->pc = cpu->pc + 2;
}

void jr(struct cpu_struct* cpu)
{
	int8_t offset = read_byte(cpu->pc, cpu->mmu);
	cpu->pc += offset;
}

void jrnz(struct cpu_struct* cpu)
{
	int8_t offset;
	if(cpu->stand_regs[reg_f] & z_flag)
	{
		cpu->pc = cpu->pc + 1;
		return;
	}
	offset = read_byte(cpu->pc, cpu->mmu);
	cpu->pc += offset;
}

void jrz(struct cpu_struct* cpu)
{
	int8_t offset;
	if(cpu->stand_regs[reg_f] & z_flag)
	{
		offset = read_byte(cpu->pc, cpu->mmu);
		cpu->pc += offset;
		return;
	}
	cpu->pc = cpu->pc+1;
}

void jrnc(struct cpu_struct* cpu)
{
	int8_t offset;
	if(cpu->stand_regs[reg_f] & c_flag)
	{
		cpu->pc = cpu->pc + 1;
		return;
	}
	offset = read_byte(cpu->pc, cpu->mmu);
	cpu->pc += offset;
}

void jrc(struct cpu_struct* cpu)
{
	int8_t offset;
	if(cpu->stand_regs[reg_f] & c_flag)
	{
		offset = read_byte(cpu->pc, cpu->mmu);
		cpu->pc += offset;
		return;
	}
	cpu->pc = cpu->pc + 1;
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

void ld_reg_imm(struct cpu_struct* cpu, uint8_t reg)
{
	reg = reg>>3;
	
	cpu->stand_regs[reg] = read_byte(cpu->pc++, cpu->mmu);
}

void ld_dreg_imm(struct cpu_struct* cpu, uint8_t reg)
{
	uint16_t data;
	reg = reg>>3;
	data = read_word(cpu->pc, cpu->mmu);
	cpu->pc += 2;
	save_double_reg(cpu, reg, data);
}

void ld_dreg_imm_sp(struct cpu_struct* cpu)
{
	uint16_t data;
	cpu->sp = read_word(cpu->pc, cpu->mmu);
	cpu->pc += 2;
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

void inc_dreg(struct cpu_struct* cpu, uint8_t reg)
{
	uint16_t data;
	reg = reg>>3;
	data = get_double_reg(cpu, reg);
	data++;
	save_double_reg(cpu, reg, data);
}

void inc_sp(struct cpu_struct* cpu)
{
	cpu->sp++;
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

void dec_dreg(struct cpu_struct* cpu, uint8_t reg)
{
	uint16_t data;
	reg = reg>>3;
	data = get_double_reg(cpu, reg);
	data--;
	save_double_reg(cpu, reg, data);
}

void dec_sp(struct cpu_struct* cpu)
{
	cpu->sp--;
}

void push(struct cpu_struct* cpu, uint8_t reg)
{
	reg = reg>>3;
	write_word(cpu->sp, get_double_reg(cpu, reg),cpu->mmu); 
	cpu->sp = cpu->sp - 2;
}

void pop(struct cpu_struct* cpu, uint8_t reg)
{
	reg = reg>>3;
	cpu->sp = cpu->sp + 2;
	save_double_reg(cpu, reg, read_word(cpu->sp, cpu->mmu));
}

void push_af(struct cpu_struct* cpu)
{
	write_word(cpu->sp, get_double_reg(cpu, reg_a),cpu->mmu); 
	cpu->sp = cpu->sp - 2;
}

void pop_af(struct cpu_struct* cpu)
{
	cpu->sp = cpu->sp + 2;
	save_double_reg(cpu, reg_a, read_word(cpu->sp, cpu->mmu));
}

void call(struct cpu_struct* cpu)
{
	write_word(cpu->sp, cpu->pc+2, cpu->mmu); 
	cpu->sp = cpu->sp - 2;
	jp(cpu);
}

void callnz(struct cpu_struct* cpu)
{
	if(cpu->stand_regs[reg_f] & z_flag)
	{
		cpu->pc = cpu->pc + 2;
		return;
	}
	write_word(cpu->sp, cpu->pc+2, cpu->mmu); 
	cpu->sp = cpu->sp - 2;
	jp(cpu);
}

void callz(struct cpu_struct* cpu)
{
	if(cpu->stand_regs[reg_f] & z_flag)
	{
		write_word(cpu->sp, cpu->pc+2, cpu->mmu); 
		cpu->sp = cpu->sp - 2;
		jp(cpu);
		return;
	}
	cpu->pc = cpu->pc + 2;
}

void callnc(struct cpu_struct* cpu)
{
	if(cpu->stand_regs[reg_f] & c_flag)
	{
		cpu->pc = cpu->pc + 2;
		return;
	}
	write_word(cpu->sp, cpu->pc+2, cpu->mmu); 
	cpu->sp = cpu->sp - 2;
	jp(cpu);
}

void callc(struct cpu_struct* cpu)
{
	if(cpu->stand_regs[reg_f] & c_flag)
	{
		write_word(cpu->sp, cpu->pc+2, cpu->mmu); 
		cpu->sp = cpu->sp - 2;
		jp(cpu);
		return;
	}
	cpu->pc = cpu->pc + 2;
}

void ret(struct cpu_struct* cpu)
{
	cpu->sp = cpu->sp + 2;
	cpu->pc = read_word(cpu->sp, cpu->mmu); 
}

void retnz(struct cpu_struct* cpu)
{
	if(cpu->stand_regs[reg_f] & z_flag)
		return;
	cpu->sp = cpu->sp + 2;
	cpu->pc = read_word(cpu->sp, cpu->mmu); 
}

void retz(struct cpu_struct* cpu)
{
	if(cpu->stand_regs[reg_f] & z_flag)
	{
		cpu->sp = cpu->sp + 2;
		cpu->pc = read_word(cpu->sp, cpu->mmu); 
		return;
	}
}

void retnc(struct cpu_struct* cpu)
{
	if(cpu->stand_regs[reg_f] & c_flag)
		return;
	cpu->sp = cpu->sp + 2;
	cpu->pc = read_word(cpu->sp, cpu->mmu); 
}

void retc(struct cpu_struct* cpu)
{
	if(cpu->stand_regs[reg_f] & c_flag)
	{
		cpu->sp = cpu->sp + 2;
		cpu->pc = read_word(cpu->sp, cpu->mmu); 
		return;
	}
}

void rst(struct cpu_struct* cpu, uint8_t offset)
{
	write_word(cpu->sp, cpu->pc, cpu->mmu); 
	cpu->sp = cpu->sp - 2;

	cpu->pc = offset;
}


