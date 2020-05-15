//*******************************************************************
// Jeffrey Byrnes
// timer.c
// Phase 0, Exercise 4, Timer Programming
//*******************************************************************

#include <spede/flames.h>      // SPEDE stuff we need...
#include <spede/machine/asmacros.h>
#include <spede/machine/io.h>
#include <spede/machine/pic.h>
#include <spede/machine/proc_reg.h>
#include <spede/machine/seg.h>
#include <spede/stdio.h>
#include <spede/time.h>

#define TIMER 32               // timer intrrupt #
#define PIC_MASK_REG 0x21      // I/O # of PIC mask register
#define PIC_CONTROL_REG 0x20   // I/O # of PIC control register
#define PIC_MASK ~0x01         // mask for PIC
#define TIMER_ACK 0x60         // to sent to PIC control register

unsigned time_tick = 0;        // system time count
struct i386_gate *intr_table = (struct i386_gate *)0x3914c;  // interrupt table


__BEGIN_DECLS
void TimerEntry(void);         // a prototype, actual code in entry.S
__END_DECLS

void TimerService(void)
{
	outportb(PIC_CONTROL_REG, TIMER_ACK);
	++time_tick;
	if (!(time_tick % CLK_TCK))	//	
		cons_printf("%d ", time_tick / CLK_TCK);
}

int main(void)
{
	char myname[] = "Jeff";
	int i = 0, len = 4;
	char ch;
	fill_gate(&intr_table[TIMER], (int)TimerEntry, get_cs(), ACC_INTR_GATE, 0);
	outportb(PIC_MASK_REG, PIC_MASK);
	asm("sti");
	while(1)
	{
		if (cons_kbhit())
		{
			ch = cons_getchar();
			if(ch == 'g')breakpoint();
			else if(ch == 'x')break;
			else
			{
				cons_printf("%c ", myname[i++]);
				i %= len;
			}
		}
	}

	return 0;
}			


