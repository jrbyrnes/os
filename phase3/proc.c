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

int StrCmp(char* a, char* b) {
    int i;
    for(i = 0; a[i] != '\0' && b[i] != '\0' && a[i] == b[i]; ++i); 
    return (a[i] == b[i]) ? TRUE : FALSE;
}

void Shell() {
    int time, my_pid, ret;
    char cmd_str[STR_SIZE];

    while(1) {
        char pid_str[] = "  ";
        char time_str[] = "    ";
        time = get_time_call();
        itos(time, time_str);
        my_pid = get_pid_call();
        itos(my_pid, pid_str);
        write_call("T");
        write_call(time_str);
        write_call("(");
        write_call(pid_str);
        write_call(") TACOS-> ");
        read_call(cmd_str);
        my_pid = get_pid_call();
        itos(my_pid, pid_str);
        write_call("(");
        write_call(pid_str);
        write_call(") got input:");
        write_call(cmd_str);
        write_call("\n");
        if(StrCmp(cmd_str, "exit")) {
            write_call("(");
            write_call(pid_str);
            write_call(") exiting.\n");
            exit_call();
        }
        if(StrCmp(cmd_str, "fork")) {
            ret = fork_call();
            if(ret == NA) write_call("fork failed!\n");
            else if (ret == 0)write_call("I'm a new child process.\n");
            else if (ret > 0) write_call("I'm a parent process\n");
        }
    }
}
