// misc.h, 159

#ifndef __MISC__
#define __MISC__

#include "kernel.h" // need definition of 'q_t' below

int QisEmpty(q_t*);
int QisFull(q_t*);
int DeQ(q_t*);
void EnQ(int, q_t*);
void Bzero(char*, unsigned);
void MemCpy(char*, char*, unsigned);
int str_len(char*);
void itos(int, char*);
void StrAdd(char*, char);
void StrCpy(char*, char*);

#endif

