// syscall.c
// OS service calls

#include "kernel.h"

int get_time_call(void) {    // phase2
   int time;

   asm("int $48;            // jmp to inter table entry 48
        movl %%eax, %0"     // after intr, copy eax to time
       : "=g" (time)        // output line of asm(), one item
       :                    // input line of asm(), none
       : "eax"              // list of clobbered register(s)
   );

   return time;
}

void write_call(char *str) {
   asm("movl %0, %%eax;
        int $49"
       :
       : "g" ((int)str)
       : "eax"
   );
}

//program read_call()...


void read_call(char *str) {
   
    asm("movl %0, %%eax;
	int $50"
	: 
	: "g" ((int)str)
	: "eax"
    );

   
}

int get_pid_call(void){
    int pid;

    asm("int $51;
	 movl %%eax, %0"
	:"=g" (pid)
	:
	: "eax"
    );

	return pid;
}

void exit_call(void){
    asm("int $52");
}

int fork_call(void){
    int fork_return;

    asm("int $53;
	movl %%eax, %0"
	: "=g" (fork_return)
	:
	: "eax"
    );

    return fork_return;
}
