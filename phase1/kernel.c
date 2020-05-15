// kernel.c, 159, phase 1
//
// Team Name: TACOS (Members: Jeff Byrnes, Joel Sanchez)

#include "spede.h"
#include "kernel.h"
#include "proc.h"
#include "misc.h"
#include "entry.h"

void TimerService(tf_t *trapframe)
{
	char ch;
	pcb[cur_pid].tf_p = trapframe;
	
	if (cons_kbhit())
	{
		ch = cons_getchar();
		if (ch == 'g') breakpoint();
               // if (ch == 'x') exit(0); //Remove this before submitting. It's just used for exiting faster.
	}	
	
	outportb(PIC_CONTROL_REG, TIMER_ACK);
	
	++sys_tick;
	++pcb[cur_pid].run_tick;
	++pcb[cur_pid].total_tick;

	if (pcb[cur_pid].run_tick == TIME_SIZE)
	{
		pcb[cur_pid].state = READY;
		EnQ(cur_pid, &ready_q);
		cur_pid = -1;
	}		

	if (cur_pid == -1)
	{
		Swapper();
	}

	Loader(pcb[cur_pid].tf_p);

}

void Swapper()
{
	if (QisEmpty(&ready_q))
	{
		cons_printf("Kernel: panic, no more processes ready to run!\n");		breakpoint();
	}

	else
	{
		cur_pid = DeQ(&ready_q);
		pcb[cur_pid].run_tick = 0;
		pcb[cur_pid].state = RUN;
	}				
}

