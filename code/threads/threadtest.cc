#include "kernel.h"
#include "main.h"
#include "thread.h"
#include "../lib/rbtree.h"

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
    //printf("cpu bound tick at : %d\n",kernel->stats->totalTicks);
    kernel->interrupt->OneTick();
    }
}
void MIXbound(int arg){
    io::iowrite(0);
    printf("%s thread compute start at %d\n",kernel->currentThread->getName(),kernel->stats->totalTicks);
    for(int i=0;i<150;i++){
        kernel->interrupt->OneTick();
    }
    printf("%s thread compute finish at %d\n",kernel->currentThread->getName(),kernel->stats->totalTicks);
    io::ioread(0);
    printf("%s thread compute start at %d\n",kernel->currentThread->getName(),kernel->stats->totalTicks);
     for(int i=0;i<250;i++){
        kernel->interrupt->OneTick();
    }
    printf("%s thread compute finish at %d\n",kernel->currentThread->getName(),kernel->stats->totalTicks);
    io::iowrite(1);
     for(int i=0;i<200;i++){
        kernel->interrupt->OneTick();
    }

}
void
ThreadTest()
{
    Thread *t = new Thread("IObound thread0");
    t->Fork((VoidFunctionPtr) IObound, (void *) 1);
    Thread *t1 =new Thread("CPU bound 0");
    t1->Fork((VoidFunctionPtr)CPUbound,(void*)1);
    Thread *t2 =new Thread("MIX bound 0");
    t2->Fork((VoidFunctionPtr)MIXbound,(void*)1);
    Thread *t3 =new Thread("IO bound 1");
    t3->Fork((VoidFunctionPtr)IObound,(void*)1);
    Thread *t4 =new Thread("CPU bound 1");
    t4->Fork((VoidFunctionPtr)CPUbound,(void*)1);
    Thread *t5 =new Thread("MIX bound 0");
    t5->Fork((VoidFunctionPtr)MIXbound,(void*)1);
     
    return;
}

