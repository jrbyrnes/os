// boot.c, 159, phase 1
//
// TACOS  (Members: Jeff Byrnes, Joel Sanchez)

#include "spede.h"
#include "kernel.h"
#include "entry.h"
#include "misc.h"
#include "proc.h"

// kernel data are all declared here (prototyped in kernel.h):

int cur_pid;
pcb_t pcb[PROC_SIZE];
char stack[PROC_SIZE][STACK_SIZE];
q_t unused_q, ready_q;

unsigned int sys_tick;
struct i386_gate *intr_table;

void CreateProc(func_p_t funEntry)
{
 	int next = DeQ(&unused_q);  
	EnQ(next, &ready_q);

	Bzero(stack[next], STACK_SIZE);	
	pcb[next].run_tick = 0;
	pcb[next].total_tick = 0;
	pcb[next].state = READY;
	
	Bzero((char*) &pcb[next], sizeof(pcb_t));

	pcb[next].tf_p = (tf_t *) &stack[next][STACK_SIZE - sizeof(tf_t)];
	pcb[next].tf_p->efl = FLAGS;
	pcb[next].tf_p->cs = CS;
	pcb[next].tf_p->eip = (unsigned) funEntry;
}

void main(void) {                   // kernel boots
       int i;
	sys_tick = 0;
	intr_table = (struct i386_gate *) INTR_TABLE;

	
	unused_q.head = unused_q.tail = unused_q.size = 0;
	ready_q.head = ready_q.tail = ready_q.size = 0;

	for (i = 0; i < PROC_SIZE; i++)
	{
		EnQ(i, &unused_q);
	}
	
	fill_gate(&intr_table[TIMER], (int)TimerEntry, get_cs(), ACC_INTR_GATE, 0);
	
	outportb(PIC_MASK_REG, PIC_MASK);

	
	CreateProc(Clock);

	cur_pid = 0;

	Loader(pcb[cur_pid].tf_p); 
}
