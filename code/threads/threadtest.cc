#include "kernel.h"
#include "main.h"
#include "thread.h"

void
SimpleThread(int which)
{
    int num;
    
    for (num = 0; num < 5; num++) {
        printf("*** thread %d looped %d times\n", which, num);
        kernel->currentThread->Yield();
    }
}

void IObound(int arg){
    io::iowrite(0);
    io::ioread(0);
    io::iowrite(1);
    io::iowrite(2);
    io::ioread(1);
    return;
}
void CPUbound(int arg){
    for(int i=0;i<1000;i++){
    printf("cpu bound tick at : %d\n",kernel->stats->totalTicks);
    kernel->interrupt->OneTick();
    }
}

void
ThreadTest()
{
    Thread *t = new Thread("IObound thread");
    t->Fork((VoidFunctionPtr) IObound, (void *) 1);
    Thread *t1 =new Thread("CPU bound 0");
    t1->Fork((VoidFunctionPtr)CPUbound,(void*)1);
    return;
}

