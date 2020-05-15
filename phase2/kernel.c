// kernel.c, 159, phase 2
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
		else if (kb.wait_q.size != 0)
		{
			KbService(ch);
		}
                //if(ch == 'x') exit(0);
		//what happens q.size == 0?

			
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

	if (cur_pid == NA)
	{
		Swapper();
	}

	Loader(pcb[cur_pid].tf_p);

}


void GetTimeService(tf_t *tf_p)
{
	tf_p->eax = sys_tick / 100;	
	Loader(tf_p);
}


void WriteService(tf_t *tf_p)
{
	char *ch = (char *) tf_p->eax;
	
	while (*ch)
	{
		WriteChar(*ch);
		ch++;
	}
	//Bzero((char *)tf_p->eax, len);	
	Loader(tf_p);
}


void WriteChar(char ch)
{

	static unsigned short *cursor = (unsigned short *) VIDEO_START;
	int i;	

	if ((((unsigned) cursor - VIDEO_START ) % (CORNER * 2)) == 0)
	{
		for (i = 0; i < CORNER; i++)
		{
			*(cursor + i) = ' ' + VIDEO_MASK;
		}
	}

	if (ch != CR && ch != LF)
	{
		*cursor = ch + VIDEO_MASK;
		++cursor;
	}

	else
	{
		
		while ((((unsigned) cursor - VIDEO_START) % (CORNER * 2)) != 0)
		{
			*cursor = ' ' + VIDEO_MASK;
			++cursor;
		}

		//cursor += CORNER - ((unsigned) cursor - VIDEO_START) % (CORNER);
	}

	if (((unsigned) cursor - VIDEO_START) % ((CORNER * ROWS) * 2) == 0)
	{
		cursor = (unsigned short *) VIDEO_START;
	}
        

	
}


void ReadService(tf_t *tf_p)
{
	pcb[cur_pid].tf_p = tf_p;
	

	EnQ(cur_pid, &kb.wait_q);
	pcb[cur_pid].state = WAIT;
	cur_pid = -1;

	Swapper();
	Loader(pcb[cur_pid].tf_p);
	
}


	
void KbService(char ch)
{
	int release_pid;

	WriteChar(ch);
	if ((ch != CR) && (ch != LF))
	{
		StrAdd(kb.buffer, ch);
	}
	else
	{
		StrAdd(kb.buffer, '\0');
		release_pid = DeQ(&kb.wait_q);
		StrCpy(kb.buffer, (char *) pcb[release_pid].tf_p->eax);
		pcb[release_pid].state = READY;
		EnQ(release_pid, &ready_q);
		Bzero(kb.buffer, STR_SIZE);
	}
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

