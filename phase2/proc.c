// proc.c, 159

/*
need to include "syscall.h" to call the new OS services

program a void-returning Init that has no input
   loop forever:
      call get_time_call() to get current time in seconds
      convert time to a smaller time str
      call write_call to show time_str
      ...
      ... see demo run to issue calls to perform the same...
      ...
   }
}

*/

// all user processes are coded here
// processes do not R/W kernel data or call kernel code, only via syscalls

// include spede.h and kernel.h

#include "spede.h"
#include "kernel.h"
#include "misc.h"
#include "syscall.h"
#include "proc.h"

#define STRWIDTH 4

char str[] = "    ";

void Clock() {
   int second, last_second;
   second = last_second = 0; 
   display(second);
   while(1){ 
      second = get_time_call();
      if(last_second != second) {
          last_second = second;
          display(second);
      }
   }
}

void display(int num) {
   static unsigned short *p = (unsigned short*)VIDEO_START + CORNER - STRWIDTH;
   unsigned i;
   itos(num, str);
   for(i = 0; i < STRWIDTH; ++i)
      *(p + i) = str[i] + VIDEO_MASK;
}

void Init() {
    char hold[STR_SIZE];
    while(1) {
        write_call("The time is ");
        write_call(str);
        write_call(".\n");
        write_call("What do you say to a cup of coffee? ");
        read_call(hold);
        write_call("The answer is ");
        write_call(hold);
        write_call(".\n");
    }
}
