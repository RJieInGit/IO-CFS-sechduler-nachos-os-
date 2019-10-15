#include "kernel.h"
#include "main.h"
#include "thread.h"
#include "../machine/io.h"

void
SimpleThread(int which)
{
    int num;
    
    for (num = 0; num < 5; num++) {
        printf("*** thread %d looped %d times\n", which, num);
        kernel->currentThread->Yield();
    }
}


void IObound(){
    printf("here1\n");
   io::iowrite(0);
   io::iowrite(1);
   io::ioread(0);
   io::iowrite(2);
   io::ioread(1);
    
}
void
ThreadTest()
{
    printf("here0\n");
    Thread *IO =new Thread("IObound");
    IO->Fork((VoidFunctionPtr)IObound,(void*)1);
    while(1){
        kernel->Yield();
        kernel->interrupt->OneTick();
    }
}


