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

void write_m_reg(struct cpu_struct* cpu, uint16_t addr)
{
	write_byte(addr, cpu->stand_regs[reg_m], cpu->mmu);
}

void run_opcode(struct cpu_struct* cpu, uint8_t opcode)
{
	switch(opcode)
	{
		case 0x04:
			inc_reg(cpu, opcode&0x38); break;
		case 0x05:
			dec_reg(cpu, opcode&0x38); break;
		case 0x06:
			ldrn(cpu, opcode&0x38); break;
		case 0x0C:
			inc_reg(cpu, opcode&0x38); break;
		case 0x0D:
			dec_reg(cpu, opcode&0x38); break;
		case 0x0E:
			ldrn(cpu, opcode&0x38); break;
		case 0x14:
			inc_reg(cpu, opcode&0x38); break;
		case 0x15:
			dec_reg(cpu, opcode&0x38); break;
		case 0x16:
			ldrn(cpu, opcode&0x38); break;
		case 0x18:
			jr(cpu); break;
		case 0x1C:
			inc_reg(cpu, opcode&0x38); break;
		case 0x1D:
			dec_reg(cpu, opcode&0x38); break;
		case 0x1E:
			ldrn(cpu, opcode&0x38); break;
		case 0x20:
			jrnz(cpu); break;
		case 0x24:
			inc_reg(cpu, opcode&0x38); break;
		case 0x25:
			dec_reg(cpu, opcode&0x38); break;
		case 0x26:
			ldrn(cpu, opcode&0x38); break;
		case 0x28:
			jrz(cpu); break;
		case 0x2C:
			inc_reg(cpu, opcode&0x38); break;
		case 0x2D:
			dec_reg(cpu, opcode&0x38); break;
		case 0x2E:
			ldrn(cpu, opcode&0x38); break;
		case 0x30:
			jrnc(cpu); break;
		case 0x38:
			jrc(cpu); break;
		case 0x3C:
			inc_reg(cpu, opcode&0x38); break;
		case 0x3D:
			dec_reg(cpu, opcode&0x38); break;
		case 0x3E:
			ldrn(cpu, opcode&0x38); break;
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
		case 0x9E:
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
		case 0xC1:
			pop(cpu, opcode&0x30); break;
		case 0xC2:
			jpnz(cpu); break;
		case 0xC3:
			jp(cpu); break;
		case 0xC5:
			push(cpu, opcode&0x30); break;
		case 0xCA:
			jpz(cpu); break;
		case 0xD1:
			pop(cpu, opcode&0x30); break;
		case 0xD2:
			jpnc(cpu); break;
		case 0xD5:
			push(cpu, opcode&0x30); break;
		case 0xDA:
			jpc(cpu); break;
		case 0xE1:
			pop(cpu, opcode&0x30); break;
		case 0xE5:
			push(cpu, opcode&0x30); break;
		case 0xF1:
			pop_af(cpu); break;
		case 0xF5:
			push_af(cpu); break;
	}
}

