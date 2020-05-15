/*
// misc.c, 159
*/ 

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
		myQ->head = (myQ->head + 1) % Q_SIZE;
		--myQ->size;
		return temp;
	}
	else
	{
		return NA;
	}
}


void EnQ(int pid, q_t *myQ)
{
	if (!QisFull(myQ))
	{
		++myQ->size;
		myQ->q[myQ->tail] = pid;
		myQ->tail = (myQ->tail + 1) % Q_SIZE;
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


void MemCpy(char *source, char *dest, unsigned nBytes)
{
        int i;
	for (i = 0; i < nBytes; i++)
	{
		dest[i] = source[i];
	}
}

int str_len(char* s) {
    int i;
    for(i = 0; s[i] != '\0'; ++i);
    return i;
}

void itos(int i, char* s) {
    int h;
    h = str_len(s) - 1;
    if(i == 0) s[h] = '0';
    else for(; i > 0; i /= 10)
        s[h--] = '0' + (i % 10);
}

void StrAdd(char* str, char c) {
    int len = str_len(str);
    str[len+1] = '\0';
    str[len] = c;
}

void StrCpy(char* inStr, char* destStr) {
    int len = str_len(inStr);
    int i;
    for(i = 0; i < len; ++i)
        destStr[i] = inStr[i];
    destStr[len] = '\0';
}
