#include <spede/machine/asmacros.h>
#include "entry.h"

// set DS and ES to Kernel's data segment
#define SET_KSEGS movw $(KDATA), %ax; mov %ax, %ds; mov %ax, %es

.comm kstack, KSTACK_SIZE, 1 // define kernel stack space
.text

// Loader loads trapframe of a process to CPU registers, to run it
ENTRY(Loader) 
   movl 4(%esp), %eax   // load stack pointer from eax
   movl %eax, %esp
   popl %gs
   popl %fs
   popl %es
   popl %ds
   popa                 // restore general registers
   add $4, %esp         // skip 4 bytes that stored intr_num
   iret


// push intr type number then jump to common handler
ENTRY(TimerEntry)
   pushl $TIMER_INTR
   jmp CommonRoutine

ENTRY(GetPidEntry)
   pushl $GETPID_INTR
   jmp CommonRoutine

ENTRY(GetTimeEntry)
   pushl $GETTIME_INTR
   jmp CommonRoutine

ENTRY(SleepEntry)
   pushl $SLEEP_INTR
   jmp CommonRoutine

ENTRY(SemGetEntry)
   pushl $SEMGET_INTR
   jmp CommonRoutine

ENTRY(SemWaitEntry)
   pushl $SEMWAIT_INTR
   jmp CommonRoutine

ENTRY(SemPostEntry)
   pushl $SEMPOST_INTR
   jmp CommonRoutine

ENTRY(MsgSendEntry)
   pushl $MSGSEND_INTR
   jmp CommonRoutine

ENTRY(MsgRecvEntry)
   pushl $MSGRECV_INTR
   jmp CommonRoutine

// Common IRQ entry, save context and call Kernel()
CommonRoutine:
   pusha
   pushl %ds
   pushl %es
   pushl %fs
   pushl %gs
   movl %esp, %edx
   cld
   SET_KSEGS      // set DS and ES to kernel's data segments
   leal kstack + KSTACK_SIZE, %esp
   pushl %edx
   call CNAME(Kernel)
