// Team TACOS
// misc.c, 159

#include "spede.h"
#include "kernel.h"

int QisEmpty(q_t *myQ)
{
	return (myQ->size == 0) ? TRUE : FALSE;
}

int QisFull(q_t *myQ)
{
	return (myQ->size == 20) ? TRUE : FALSE;
}

int DeQ(q_t *myQ)
{
	if (!QisEmpty(myQ))
	{
		int temp = myQ->q[myQ->head];
		++myQ->head;
		--myQ->size;
		return temp;
	}
	else
	{
		return 0;
	}
}


void EnQ(int pid, q_t *myQ)
{
	if (!QisFull(myQ))
	{
		++myQ->size;
		myQ->q[(myQ->tail++) % Q_SIZE] = pid;
	}

	else
	{
		cons_printf("Panic: queue is full, cannot EnQ!\n");
		breakpoint();
	}
}

void Bzero(char *myChar, unsigned nBytes)
{
        int i;
	for (i = 0; i < nBytes; i++)
	{
		myChar[i] =0;
	}
}

