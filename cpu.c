#include <stdio.h>
#include "cpu.h"

void reset_cpu(struct cpu_struct* cpu)
{
	cpu->a = 0;
	cpu->b = 0;
	cpu->c = 0;
	cpu->d = 0;
	cpu->e = 0;
	cpu->f = 0;
	cpu->h = 0;
	cpu->l = 0;

	cpu->sp = 0;
	cpu->pc = 0x100;

	printf("CPU:0x%04x \n", cpu->pc);
}


