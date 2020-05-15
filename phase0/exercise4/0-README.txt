0-README.txt

To copy the demo.dli, issue shell command:
   cp ~changw/html/159/0/ex4stuff/demo.dli .

then shell command: flash demo.dli
   FLASH% d
   FLASH% fl
   FLAMES> g
(when run, press a key at times; to end the run, press the 'x' key)
   FLAMES> ctrl-C
   FLASH% q
(back to shell)

Press the Left-Command key when using Virtual Box and the cursor disappears.

While using the SPEDE tool 'flash' to connect to a target PC, do not
suspend "flash" (e.g., pressing ctrl-Z, logout, etc.) on the Linux host:
DO NOT do any of these:
   1. press ctrl-Z
   2. start another "flash"
   3. close a terminal shell window that's still running "flash"
   4. let a login session idled out and screen-locked without logging
      out (next person logging in cannot start "flash" properly)

You should manually quit the flash. To terminate a run-away flash process,
issue shell command "kill -9 <flash process ID>," or cold-start the linux
PC to release the communication/download connection session.

Exercise 4 needs your work (timer.c) properly programmed in order for it
to run like the demo.dli after compiled. Submit your work (timer.c).

