In the folder where the makefile is located, open terminal.
    Command is 'make run microkernel=obj/KERNEL.o'

You must change the KERNEL for desired microkernel.
List of micro kernels you can use:
    - make run microkernel=obj/kernel1.o
    - make run microkernel=obj/kernel2.o
    - make run microkernel=obj/kernel3.o

If you are going to run different kernels,
    - You must type 'make clean' after each use of make run.

IMPORTANT NOTE:
    - I increase timer interrupt period to 200x but it still fast sometimes it does not enough to enter all the inputs. So please be fast when entering user inputs. Also press 's' to notify user inputs end.
    - Pressing 'p' to context switching if the current process is not init.
    - Processes running collatz in microkernels produce a lot of output.
        This makes it very difficult to follow the screen.
        For this reason, collatz operates the [20, 25) interval, not the [1,25) interval. (Just to be able to follow the screen)
