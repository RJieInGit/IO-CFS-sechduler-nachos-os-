#include "kernel.h"
#include "main.h"
#include "thread.h"
#include "../lib/rbtree.h"
#include <string.h>

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
    for(int i=0;i<500;i++){
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
    int numCPU =7;
    int numIO =7;
    int numMix =7;
    Thread *t;
    
    for (int i=0;i<numCPU;i++){
        char s[50];
         sprintf(s,"CPUbound");
        t= new Thread(s);
        t->Fork((VoidFunctionPtr) CPUbound, (void *) 1);
    }
     for (int i=0;i<numIO;i++){
         char s [50];
        sprintf(s,"IObound");
        t= new Thread(s);
        t->Fork((VoidFunctionPtr) IObound, (void *) 1);
    } for (int i=0;i<numMix;i++){
        char s [50];
        sprintf(s,"MIXbound");
        t= new Thread(s);
        t->Fork((VoidFunctionPtr) MIXbound, (void *) 1);
    }
}

