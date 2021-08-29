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

void jphl(struct cpu_struct* cpu)
{
	cpu->pc = get_double_reg(cpu, reg_h);
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

void cpl(struct cpu_struct* cpu)
{
	cpu->stand_regs[reg_a] = cpu->stand_regs[reg_a] ^ 0xFF;

	cpu->stand_regs[reg_f] = set_n_flag;
	cpu->stand_regs[reg_f] = set_h_flag;
}

void ccf(struct cpu_struct* cpu)
{
	if(cpu->stand_regs[reg_f] & c_flag)
		cpu->stand_regs[reg_f] = reset_c_flag;
	else
		cpu->stand_regs[reg_f] = set_c_flag;
}

void daa(struct cpu_struct* cpu)
{

}

void scf(struct cpu_struct* cpu)
{
	cpu->stand_regs[reg_f] = set_c_flag;

	cpu->stand_regs[reg_f] = reset_n_flag;
	cpu->stand_regs[reg_f] = reset_h_flag;
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

void add_dreg(struct cpu_struct* cpu, uint8_t reg)
{
	reg = reg >> 4;

	uint16_t val1 = get_double_reg(cpu, reg_h);
	uint16_t val2 = get_double_reg(cpu, reg);

	uint32_t temp = val1+val2;

	// Flag Calculation
	cpu->stand_regs[reg_f] = temp == 0 ? set_z_flag : reset_z_flag;
	cpu->stand_regs[reg_f] = reset_n_flag;
	cpu->stand_regs[reg_f] = (val2 ^ cpu->stand_regs[reg_a] ^ temp) & 0x1000 ? set_h_flag : reset_h_flag;
	cpu->stand_regs[reg_f] = (temp>0xFFFF) ? set_c_flag : reset_c_flag;

	// Result pass
	cpu->stand_regs[reg_a] = temp;
}

void add_dreg_sp(struct cpu_struct* cpu)
{
	uint16_t val1 = get_double_reg(cpu, reg_h);

	uint32_t temp = val1+cpu->sp;

	// Flag Calculation
	cpu->stand_regs[reg_f] = temp == 0 ? set_z_flag : reset_z_flag;
	cpu->stand_regs[reg_f] = reset_n_flag;
	cpu->stand_regs[reg_f] = (cpu->sp ^ cpu->stand_regs[reg_a] ^ temp) & 0x1000 ? set_h_flag : reset_h_flag;
	cpu->stand_regs[reg_f] = (temp>0xFFFF) ? set_c_flag : reset_c_flag;

	// Result pass
	cpu->stand_regs[reg_a] = temp;
}

void add_imm_sp(struct cpu_struct* cpu)
{
	int8_t val1 = read_byte(cpu->pc++, cpu->mmu);

	uint32_t temp = val1+cpu->sp;

	// Flag Calculation
	cpu->stand_regs[reg_f] = reset_z_flag;
	cpu->stand_regs[reg_f] = reset_n_flag;
	cpu->stand_regs[reg_f] = (cpu->sp ^ cpu->stand_regs[reg_a] ^ temp) & 0x1000 ? set_h_flag : reset_h_flag;
	cpu->stand_regs[reg_f] = (temp>0xFFFF) ? set_c_flag : reset_c_flag;

	// Result pass
	cpu->sp = temp;
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

void ld_index_src(struct cpu_struct* cpu)
{
	uint16_t addr = 0xFF00;
	int8_t offset = read_byte(cpu->pc++, cpu->mmu);
	addr += offset;

	write_byte(addr, cpu->stand_regs[reg_a], cpu->mmu); 
}

void ld_index_dst(struct cpu_struct* cpu)
{
	uint16_t addr = 0xFF00;
	int8_t offset = read_byte(cpu->pc++, cpu->mmu);
	addr += offset;

	cpu->stand_regs[reg_a] = read_byte(addr, cpu->mmu); 
}

void ld_rindex_dst(struct cpu_struct* cpu)
{
	uint16_t addr = 0xFF00 + cpu->stand_regs[reg_c];

	write_byte(addr, cpu->stand_regs[reg_a], cpu->mmu); 
}

void ld_rindex_src(struct cpu_struct* cpu)
{
	uint16_t addr = 0xFF00 + cpu->stand_regs[reg_c];

	cpu->stand_regs[reg_a] = read_byte(addr, cpu->mmu); 
}

void ld_imm_indir_dst(struct cpu_struct* cpu)
{
	uint16_t addr = read_word(cpu->pc, cpu->mmu);
	cpu->pc += 2;

	write_byte(addr, cpu->stand_regs[reg_a], cpu->mmu); 
}

void ld_dreg_imm_index_sp(struct cpu_struct* cpu)
{
	int8_t offset = read_byte(cpu->pc++, cpu->mmu);
	uint32_t temp = offset + cpu->sp;

	cpu->stand_regs[reg_f] = reset_z_flag;
	cpu->stand_regs[reg_f] = reset_n_flag;

	cpu->stand_regs[reg_f] = (cpu->sp ^ offset ^ temp) & 0x1000 ? set_h_flag : reset_h_flag;
	cpu->stand_regs[reg_f] = (temp>0xFFFF) ? set_c_flag : reset_c_flag;

	save_double_reg(cpu, reg_h, temp);
}

void ld_dreg_sp(struct cpu_struct* cpu)
{
	cpu->sp = get_double_reg(cpu, reg_h);
}

void ld_imm_indir_src(struct cpu_struct* cpu)
{
	uint16_t addr = read_word(cpu->pc, cpu->mmu);
	cpu->pc += 2;

	cpu->stand_regs[reg_a] = read_byte(addr, cpu->mmu); 
}

void ld_imm_indir_dst_sp(struct cpu_struct* cpu)
{
	uint16_t addr = read_word(cpu->pc, cpu->mmu);
	cpu->pc += 2;

	write_word(addr, cpu->sp, cpu->mmu); 
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

void reti(struct cpu_struct* cpu)
{
	cpu->sp = cpu->sp + 2;
	cpu->pc = read_word(cpu->sp, cpu->mmu); 
	cpu->int_en = 1;
}

void rst(struct cpu_struct* cpu, uint8_t offset)
{
	write_word(cpu->sp, cpu->pc, cpu->mmu); 
	cpu->sp = cpu->sp - 2;

	cpu->pc = offset;
}

void rlc(struct cpu_struct* cpu, uint8_t reg)
{
	if (cpu->stand_regs[reg] & 0x80)
		cpu->stand_regs[reg_f] = set_c_flag;
	cpu->stand_regs[reg] << 1;

	if (cpu->stand_regs[reg] == 0)
		cpu->stand_regs[reg_f] = set_z_flag;

	cpu->stand_regs[reg_f] = reset_n_flag;
	cpu->stand_regs[reg_f] = reset_h_flag;
}

void rl(struct cpu_struct* cpu, uint8_t reg)
{
	uint8_t oldcarry = cpu->stand_regs[reg_f] & c_flag;
	if (cpu->stand_regs[reg] & 0x80)
		cpu->stand_regs[reg_f] = set_c_flag;
	
	cpu->stand_regs[reg] << 1;

	if (oldcarry)
		cpu->stand_regs[reg] = cpu->stand_regs[reg] | 0x01;

	if (cpu->stand_regs[reg] == 0)
		cpu->stand_regs[reg_f] = set_z_flag;

	cpu->stand_regs[reg_f] = reset_n_flag;
	cpu->stand_regs[reg_f] = reset_h_flag;
}

void rrc(struct cpu_struct* cpu, uint8_t reg)
{
	if (cpu->stand_regs[reg] & 0x01)
		cpu->stand_regs[reg_f] = set_c_flag;
	cpu->stand_regs[reg] >> 1;

	if (cpu->stand_regs[reg] == 0)
		cpu->stand_regs[reg_f] = set_z_flag;

	cpu->stand_regs[reg_f] = reset_n_flag;
	cpu->stand_regs[reg_f] = reset_h_flag;
}

void rr(struct cpu_struct* cpu, uint8_t reg)
{
	uint8_t oldcarry = cpu->stand_regs[reg_f] & c_flag;
	if (cpu->stand_regs[reg] & 0x01)
		cpu->stand_regs[reg_f] = set_c_flag;
	
	cpu->stand_regs[reg] >> 1;

	if (oldcarry)
		cpu->stand_regs[reg] = cpu->stand_regs[reg] | 0x80;

	if (cpu->stand_regs[reg] == 0)
		cpu->stand_regs[reg_f] = set_z_flag;

	cpu->stand_regs[reg_f] = reset_n_flag;
	cpu->stand_regs[reg_f] = reset_h_flag;
}
