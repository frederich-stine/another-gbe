#include <stdio.h>
#include "cpu.h"
#include "opcode.h"

void reset_cpu(struct cpu_struct* cpu)
{
	for(int i=0; i<8; i++)
	{
		cpu->stand_regs[i] = 0;
	}

	cpu->sp = 0xFFFE;
	cpu->pc = 0x0100;
	cpu->int_en = 1;

	printf("CPU:0x%04x \n", cpu->pc);
}

uint16_t get_double_reg(struct cpu_struct* cpu, uint8_t reg)
{
	uint16_t double_reg = cpu->stand_regs[reg];
	double_reg = (double_reg << 8) | cpu->stand_regs[reg+1];
	return double_reg;
}

void save_double_reg(struct cpu_struct* cpu, uint8_t reg, uint16_t data)
{
	cpu->stand_regs[reg+1] = data;
	data = data>>8;
	cpu->stand_regs[reg] = data;
}

void load_m_reg(struct cpu_struct* cpu, uint16_t addr)
{
	cpu->stand_regs[reg_m] = read_byte(addr, cpu->mmu);
}

void load_m_reg_imm(struct cpu_struct* cpu)
{
	cpu->stand_regs[reg_m] = read_byte(cpu->pc++, cpu->mmu);
}

void write_m_reg(struct cpu_struct* cpu, uint16_t addr)
{
	write_byte(addr, cpu->stand_regs[reg_m], cpu->mmu);
}

void run_opcode(struct cpu_struct* cpu, uint8_t opcode)
{
	switch(opcode)
	{
		case 0x01:
			ld_dreg_imm(cpu, opcode&0x30); break;
		case 0x02:
			write_byte(get_double_reg(cpu, reg_b), cpu->stand_regs[reg_a], cpu->mmu); break;
		case 0x03:
			inc_dreg(cpu, opcode&0x30); break;
		case 0x04:
			inc_reg(cpu, opcode&0x38); break;
		case 0x05:
			dec_reg(cpu, opcode&0x38); break;
		case 0x06:
			ld_reg_imm(cpu, opcode&0x38); break;
		case 0x07:
			rlc(cpu, reg_a); break;
		case 0x08:
			ld_imm_indir_dst_sp(cpu); break;
		case 0x09:
			add_dreg(cpu, opcode&0x30); break;
		case 0x0A:
			load_m_reg(cpu, get_double_reg(cpu, reg_b));
			ld_reg(cpu, 0x38, 0x06); break;
		case 0x0B:
			dec_dreg(cpu, opcode&0x30); break;
		case 0x0C:
			inc_reg(cpu, opcode&0x38); break;
		case 0x0D:
			dec_reg(cpu, opcode&0x38); break;
		case 0x0E:
			ld_reg_imm(cpu, opcode&0x38); break;
		case 0x0F:
			rrc(cpu, reg_a); break;
		case 0x11:
			ld_dreg_imm(cpu, opcode&0x30); break;
		case 0x12:
			write_byte(get_double_reg(cpu, reg_d), cpu->stand_regs[reg_a], cpu->mmu); break;
		case 0x13:
			inc_dreg(cpu, opcode&0x30); break;
		case 0x14:
			inc_reg(cpu, opcode&0x38); break;
		case 0x15:
			dec_reg(cpu, opcode&0x38); break;
		case 0x16:
			ld_reg_imm(cpu, opcode&0x38); break;
		case 0x17:
			rl(cpu, reg_a); break;
		case 0x18:
			jr(cpu); break;
		case 0x19:
			add_dreg(cpu, opcode&0x30); break;
		case 0x1A:
			load_m_reg(cpu, get_double_reg(cpu, reg_d));
			ld_reg(cpu, 0x38, 0x06); break;
		case 0x1B:
			dec_dreg(cpu, opcode&0x30); break;
		case 0x1C:
			inc_reg(cpu, opcode&0x38); break;
		case 0x1D:
			dec_reg(cpu, opcode&0x38); break;
		case 0x1E:
			ld_reg_imm(cpu, opcode&0x38); break;
		case 0x1F:
			rr(cpu, reg_a); break;
		case 0x20:
			jrnz(cpu); break;
		case 0x21:
			ld_dreg_imm(cpu, opcode&0x30); break;
		case 0x22:
			write_byte(get_double_reg(cpu, reg_h), cpu->stand_regs[reg_a], cpu->mmu);
			inc_dreg(cpu, 0x20); break;
		case 0x23:
			inc_dreg(cpu, opcode&0x30); break;
		case 0x24:
			inc_reg(cpu, opcode&0x38); break;
		case 0x25:
			dec_reg(cpu, opcode&0x38); break;
		case 0x26:
			ld_reg_imm(cpu, opcode&0x38); break;
		case 0x28:
			jrz(cpu); break;
		case 0x29:
			add_dreg(cpu, opcode&0x30); break;
		case 0x2A:
			load_m_reg(cpu, get_double_reg(cpu, reg_h));
			ld_reg(cpu, 0x38, 0x06); 
			inc_dreg(cpu, 0x20); break;
		case 0x2B:
			dec_dreg(cpu, opcode&0x30); break;
		case 0x2C:
			inc_reg(cpu, opcode&0x38); break;
		case 0x2D:
			dec_reg(cpu, opcode&0x38); break;
		case 0x2E:
			ld_reg_imm(cpu, opcode&0x38); break;
		case 0x2F:
			cpl(cpu); break;
		case 0x30:
			jrnc(cpu); break;
		case 0x31:
			ld_dreg_imm_sp(cpu); break;
		case 0x32:
			write_byte(get_double_reg(cpu, reg_h), cpu->stand_regs[reg_a], cpu->mmu);
			dec_dreg(cpu, 0x20); break;
		case 0x33:
			inc_sp(cpu); break;
		case 0x34:
			load_m_reg(cpu, get_double_reg(cpu, reg_h));
			inc_reg(cpu, opcode&0x38);
			write_m_reg(cpu, get_double_reg(cpu, reg_h)); break;
		case 0x35:
			load_m_reg(cpu, get_double_reg(cpu, reg_h));
			dec_reg(cpu, opcode&0x38);
			write_m_reg(cpu, get_double_reg(cpu, reg_h)); break;
		case 0x36:
			ld_reg_imm(cpu, reg_m);
			write_m_reg(cpu, get_double_reg(cpu, reg_h)); break;
		case 0x37:
			scf(cpu); break;	
		case 0x38:
			jrc(cpu); break;
		case 0x39:
			add_dreg_sp(cpu); break;
		case 0x3A:
			load_m_reg(cpu, get_double_reg(cpu, reg_h));
			ld_reg(cpu, 0x38, 0x06); 
			dec_dreg(cpu, 0x20); break;
		case 0x3B:
			dec_sp(cpu); break;
		case 0x3C:
			inc_reg(cpu, opcode&0x38); break;
		case 0x3D:
			dec_reg(cpu, opcode&0x38); break;
		case 0x3E:
			ld_reg_imm(cpu, opcode&0x38); break;
		case 0x3F:
			ccf(cpu); break;
		case 0x40:
			ld_reg(cpu, opcode&0x38, opcode&0x07); break;
		case 0x41:
			ld_reg(cpu, opcode&0x38, opcode&0x07); break;
		case 0x42:
			ld_reg(cpu, opcode&0x38, opcode&0x07); break;
		case 0x43:
			ld_reg(cpu, opcode&0x38, opcode&0x07); break;
		case 0x44:
			ld_reg(cpu, opcode&0x38, opcode&0x07); break;
		case 0x45:
			ld_reg(cpu, opcode&0x38, opcode&0x07); break;
		case 0x46:
			load_m_reg(cpu, get_double_reg(cpu, reg_h));
			ld_reg(cpu, opcode&0x38, opcode&0x07); break;
		case 0x47:
			ld_reg(cpu, opcode&0x38, opcode&0x07); break;
		case 0x48:
			ld_reg(cpu, opcode&0x38, opcode&0x07); break;
		case 0x49:
			ld_reg(cpu, opcode&0x38, opcode&0x07); break;
		case 0x4A:
			ld_reg(cpu, opcode&0x38, opcode&0x07); break;
		case 0x4B:
			ld_reg(cpu, opcode&0x38, opcode&0x07); break;
		case 0x4C:
			ld_reg(cpu, opcode&0x38, opcode&0x07); break;
		case 0x4D:
			ld_reg(cpu, opcode&0x38, opcode&0x07); break;
		case 0x4E:
			load_m_reg(cpu, get_double_reg(cpu, reg_h));
			ld_reg(cpu, opcode&0x38, opcode&0x07); break;
		case 0x4F:
			ld_reg(cpu, opcode&0x38, opcode&0x07); break;
		case 0x50:
			ld_reg(cpu, opcode&0x38, opcode&0x07); break;
		case 0x51:
			ld_reg(cpu, opcode&0x38, opcode&0x07); break;
		case 0x52:
			ld_reg(cpu, opcode&0x38, opcode&0x07); break;
		case 0x53:
			ld_reg(cpu, opcode&0x38, opcode&0x07); break;
		case 0x54:
			ld_reg(cpu, opcode&0x38, opcode&0x07); break;
		case 0x55:
			ld_reg(cpu, opcode&0x38, opcode&0x07); break;
		case 0x56:
			load_m_reg(cpu, get_double_reg(cpu, reg_h));
			ld_reg(cpu, opcode&0x38, opcode&0x07); break;
		case 0x57:
			ld_reg(cpu, opcode&0x38, opcode&0x07); break;
		case 0x58:
			ld_reg(cpu, opcode&0x38, opcode&0x07); break;
		case 0x59:
			ld_reg(cpu, opcode&0x38, opcode&0x07); break;
		case 0x5A:
			ld_reg(cpu, opcode&0x38, opcode&0x07); break;
		case 0x5B:
			ld_reg(cpu, opcode&0x38, opcode&0x07); break;
		case 0x5C:
			ld_reg(cpu, opcode&0x38, opcode&0x07); break;
		case 0x5D:
			ld_reg(cpu, opcode&0x38, opcode&0x07); break;
		case 0x5E:
			load_m_reg(cpu, get_double_reg(cpu, reg_h));
			ld_reg(cpu, opcode&0x38, opcode&0x07); break;
		case 0x5F:
			ld_reg(cpu, opcode&0x38, opcode&0x07); break;
		case 0x60:
			ld_reg(cpu, opcode&0x38, opcode&0x07); break;
		case 0x61:
			ld_reg(cpu, opcode&0x38, opcode&0x07); break;
		case 0x62:
			ld_reg(cpu, opcode&0x38, opcode&0x07); break;
		case 0x63:
			ld_reg(cpu, opcode&0x38, opcode&0x07); break;
		case 0x64:
			ld_reg(cpu, opcode&0x38, opcode&0x07); break;
		case 0x65:
			ld_reg(cpu, opcode&0x38, opcode&0x07); break;
		case 0x66:
			load_m_reg(cpu, get_double_reg(cpu, reg_h));
			ld_reg(cpu, opcode&0x38, opcode&0x07); break;
		case 0x67:
			ld_reg(cpu, opcode&0x38, opcode&0x07); break;
		case 0x68:
			ld_reg(cpu, opcode&0x38, opcode&0x07); break;
		case 0x69:
			ld_reg(cpu, opcode&0x38, opcode&0x07); break;
		case 0x6A:
			ld_reg(cpu, opcode&0x38, opcode&0x07); break;
		case 0x6B:
			ld_reg(cpu, opcode&0x38, opcode&0x07); break;
		case 0x6C:
			ld_reg(cpu, opcode&0x38, opcode&0x07); break;
		case 0x6D:
			ld_reg(cpu, opcode&0x38, opcode&0x07); break;
		case 0x6E:
			load_m_reg(cpu, get_double_reg(cpu, reg_h));
			ld_reg(cpu, opcode&0x38, opcode&0x07); break;
		case 0x6F:
			ld_reg(cpu, opcode&0x38, opcode&0x07); break;
		case 0x70:
			ld_reg(cpu, opcode&0x38, opcode&0x07); 
			write_m_reg(cpu, get_double_reg(cpu, reg_h)); break;
		case 0x71:
			ld_reg(cpu, opcode&0x38, opcode&0x07); 
			write_m_reg(cpu, get_double_reg(cpu, reg_h)); break;
		case 0x72:
			ld_reg(cpu, opcode&0x38, opcode&0x07); 
			write_m_reg(cpu, get_double_reg(cpu, reg_h)); break;
		case 0x73:
			ld_reg(cpu, opcode&0x38, opcode&0x07); 
			write_m_reg(cpu, get_double_reg(cpu, reg_h)); break;
		case 0x74:
			ld_reg(cpu, opcode&0x38, opcode&0x07); 
			write_m_reg(cpu, get_double_reg(cpu, reg_h)); break;
		case 0x75:
			ld_reg(cpu, opcode&0x38, opcode&0x07); 
			write_m_reg(cpu, get_double_reg(cpu, reg_h)); break;
		case 0x77:
			ld_reg(cpu, opcode&0x38, opcode&0x07); 
			write_m_reg(cpu, get_double_reg(cpu, reg_h)); break;
		case 0x78:
			ld_reg(cpu, opcode&0x38, opcode&0x07); break;
		case 0x79:
			ld_reg(cpu, opcode&0x38, opcode&0x07); break;
		case 0x7A:
			ld_reg(cpu, opcode&0x38, opcode&0x07); break;
		case 0x7B:
			ld_reg(cpu, opcode&0x38, opcode&0x07); break;
		case 0x7C:
			ld_reg(cpu, opcode&0x38, opcode&0x07); break;
		case 0x7D:
			ld_reg(cpu, opcode&0x38, opcode&0x07); break;
		case 0x7E:
			load_m_reg(cpu, get_double_reg(cpu, reg_h));
			ld_reg(cpu, opcode&0x38, opcode&0x07); break;
		case 0x7F:
			ld_reg(cpu, opcode&0x38, opcode&0x07); break;
		case 0x80:
			add_reg(cpu, opcode&0x07); break;
		case 0x81:
			add_reg(cpu, opcode&0x07); break;
		case 0x82:
			add_reg(cpu, opcode&0x07); break;
		case 0x83:
			add_reg(cpu, opcode&0x07); break;
		case 0x84:
			add_reg(cpu, opcode&0x07); break;
		case 0x85:
			add_reg(cpu, opcode&0x07); break;
		case 0x86:
			load_m_reg(cpu, get_double_reg(cpu, reg_h));
			add_reg(cpu, opcode&0x07); break;
		case 0x87:
			add_reg(cpu, opcode&0x07); break;
		case 0x88:
			adc_reg(cpu, opcode&0x07); break;
		case 0x89:
			adc_reg(cpu, opcode&0x07); break;
		case 0x8A:
			adc_reg(cpu, opcode&0x07); break;
		case 0x8B:
			adc_reg(cpu, opcode&0x07); break;
		case 0x8C:
			adc_reg(cpu, opcode&0x07); break;
		case 0x8D:
			adc_reg(cpu, opcode&0x07); break;
		case 0x8E:
			load_m_reg(cpu, get_double_reg(cpu, reg_h));
			adc_reg(cpu, opcode&0x07); break;
		case 0x8F:
			adc_reg(cpu, opcode&0x07); break;
		case 0x90:
			sub_reg(cpu, opcode&0x07); break;
		case 0x91:
			sub_reg(cpu, opcode&0x07); break;
		case 0x92:
			sub_reg(cpu, opcode&0x07); break;
		case 0x93:
			sub_reg(cpu, opcode&0x07); break;
		case 0x94:
			sub_reg(cpu, opcode&0x07); break;
		case 0x95:
			sub_reg(cpu, opcode&0x07); break;
		case 0x96:
			load_m_reg(cpu, get_double_reg(cpu, reg_h));
			sub_reg(cpu, opcode&0x07); break;
		case 0x97:
			sub_reg(cpu, opcode&0x07); break;
		case 0x98:
			sbc_reg(cpu, opcode&0x07); break;
		case 0x99:
			sbc_reg(cpu, opcode&0x07); break;
		case 0x9A:
			sbc_reg(cpu, opcode&0x07); break;
		case 0x9B:
			sbc_reg(cpu, opcode&0x07); break;
		case 0x9C:
			sbc_reg(cpu, opcode&0x07); break;
		case 0x9D:
			sbc_reg(cpu, opcode&0x07); break;
		case 0x9E:
			load_m_reg(cpu, get_double_reg(cpu, reg_h));
			sbc_reg(cpu, opcode&0x07); break;
		case 0x9F:
			sbc_reg(cpu, opcode&0x07); break;
		case 0xA0:
			and_reg(cpu, opcode&0x07); break;
		case 0xA1:
			and_reg(cpu, opcode&0x07); break;
		case 0xA2:
			and_reg(cpu, opcode&0x07); break;
		case 0xA3:
			and_reg(cpu, opcode&0x07); break;
		case 0xA4:
			and_reg(cpu, opcode&0x07); break;
		case 0xA5:
			and_reg(cpu, opcode&0x07); break;
		case 0xA6:
			load_m_reg(cpu, get_double_reg(cpu, reg_h));
			and_reg(cpu, opcode&0x07); break;
		case 0xA7:
			and_reg(cpu, opcode&0x07); break;
		case 0xA8:
			or_reg(cpu, opcode&0x07); break;
		case 0xA9:
			or_reg(cpu, opcode&0x07); break;
		case 0xAA:
			or_reg(cpu, opcode&0x07); break;
		case 0xAB:
			or_reg(cpu, opcode&0x07); break;
		case 0xAC:
			or_reg(cpu, opcode&0x07); break;
		case 0xAE:
			load_m_reg(cpu, get_double_reg(cpu, reg_h));
			or_reg(cpu, opcode&0x07); break;
		case 0xAD:
			or_reg(cpu, opcode&0x07); break;
		case 0xAF:
			or_reg(cpu, opcode&0x07); break;
		case 0xB0:
			xor_reg(cpu, opcode&0x07); break;
		case 0xB1:
			xor_reg(cpu, opcode&0x07); break;
		case 0xB2:
			xor_reg(cpu, opcode&0x07); break;
		case 0xB3:
			xor_reg(cpu, opcode&0x07); break;
		case 0xB4:
			xor_reg(cpu, opcode&0x07); break;
		case 0xB5:
			xor_reg(cpu, opcode&0x07); break;
		case 0xB6:
			load_m_reg(cpu, get_double_reg(cpu, reg_h));
			xor_reg(cpu, opcode&0x07); break;
		case 0xB7:
			xor_reg(cpu, opcode&0x07); break;
		case 0xB8:
			cp_reg(cpu, opcode&0x07); break;
		case 0xB9:
			cp_reg(cpu, opcode&0x07); break;
		case 0xBA:
			cp_reg(cpu, opcode&0x07); break;
		case 0xBB:
			cp_reg(cpu, opcode&0x07); break;
		case 0xBC:
			cp_reg(cpu, opcode&0x07); break;
		case 0xBD:
			cp_reg(cpu, opcode&0x07); break;
		case 0xBE:
			load_m_reg(cpu, get_double_reg(cpu, reg_h));
			cp_reg(cpu, opcode&0x07); break;
		case 0xBF:
			cp_reg(cpu, opcode&0x07); break;
		case 0xC0:
			retnz(cpu); break;
		case 0xC1:
			pop(cpu, opcode&0x30); break;
		case 0xC2:
			jpnz(cpu); break;
		case 0xC3:
			jp(cpu); break;
		case 0xC4:
			callnz(cpu); break;
		case 0xC5:
			push(cpu, opcode&0x30); break;
		case 0xC6:
			load_m_reg_imm(cpu);
			add_reg(cpu, reg_m); break;
		case 0xC7:
			rst(cpu, 0x00); break;
		case 0xC8:
			retz(cpu); break;
		case 0xC9:
			ret(cpu); break;
		case 0xCA:
			jpz(cpu); break;
		case 0xCC:
			callz(cpu); break;
		case 0xCD:
			call(cpu); break;
		case 0xCE:
			load_m_reg_imm(cpu);
			adc_reg(cpu, reg_m); break;
		case 0xCF:
			rst(cpu, 0x08); break;
		case 0xD0:
			retnc(cpu); break;
		case 0xD1:
			pop(cpu, opcode&0x30); break;
		case 0xD2:
			jpnc(cpu); break;
		case 0xD4:
			callnc(cpu); break;
		case 0xD5:
			push(cpu, opcode&0x30); break;
		case 0xD6:
			load_m_reg_imm(cpu);
			sub_reg(cpu, reg_m); break;
		case 0xD7:
			rst(cpu, 0x10); break;
		case 0xD8:
			retc(cpu); break;
		case 0xD9:
			reti(cpu); break;
		case 0xDA:
			jpc(cpu); break;
		case 0xDC:
			callc(cpu); break;
		case 0xDE:
			load_m_reg_imm(cpu);
			sbc_reg(cpu, reg_m); break;
		case 0xDF:
			rst(cpu, 0x18); break;
		case 0xE0:
			ld_index_dst(cpu); break;
		case 0xE1:
			pop(cpu, opcode&0x30); break;
		case 0xE2:
			ld_rindex_dst(cpu); break;
		case 0xE5:
			push(cpu, opcode&0x30); break;
		case 0xE6:
			load_m_reg_imm(cpu);
			and_reg(cpu, reg_m); break;
		case 0xE7:
			rst(cpu, 0x20); break;
		case 0xE8:
			add_imm_sp(cpu); break;
		case 0xE9:
			jphl(cpu); break;
		case 0xEA:
			ld_imm_indir_dst(cpu); break;
		case 0xEE:
			load_m_reg_imm(cpu);
			xor_reg(cpu, reg_m); break;
		case 0xEF:
			rst(cpu, 0x30); break;
		case 0xF0:
			ld_index_src(cpu); break;
		case 0xF1:
			pop_af(cpu); break;
		case 0xF2:
			ld_rindex_src(cpu); break;
		case 0xF3:
			cpu->int_en = 0; break;
		case 0xF5:
			push_af(cpu); break;
		case 0xF6:
			load_m_reg_imm(cpu);
			or_reg(cpu, reg_m); break;
		case 0xF7:
			rst(cpu, 0x28); break;
		case 0xF8:
			ld_dreg_imm_index_sp(cpu); break;
		case 0xF9:
			ld_dreg_sp(cpu); break;
		case 0xFA:
			ld_imm_indir_src(cpu); break;
		case 0xFB:
			cpu->int_en = 1; break;
		case 0xFE:
			load_m_reg_imm(cpu);
			cp_reg(cpu, reg_m); break;
		case 0xFF:
			rst(cpu, 0x38); break;
	}
}

void run_opcode_prefix(struct cpu_struct* cpu)
{
	uint8_t opcode = read_byte(cpu->pc++, cpu->mmu); 
	printf("opcode:0x%02x \n", opcode);

	


}
