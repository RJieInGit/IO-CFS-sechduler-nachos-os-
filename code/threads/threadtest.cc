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

void
ThreadTest()
{
    TestIO();
    
}


void TestIO(){
Thread *t = new Thread("thread0");
    t->Fork((VoidFunctionPtr) io::iowrite, (void *)0);
    Thread *t1 = new Thread("thread1");
    t->Fork((VoidFunctionPtr) io::iowrite, (void *)0);
    Thread *t2 = new Thread("thread2");
    t->Fork((VoidFunctionPtr) io::iowrite, (void *)0);
    Thread *t = new Thread("thread3");
    t->Fork((VoidFunctionPtr) io::ioread, (void *) 0);
    Thread *t = new Thread("thread4");
    t->Fork((VoidFunctionPtr) io::ioread, (void *) 0);
    Thread *t = new Thread("thread5");
    t->Fork((VoidFunctionPtr) io::iowrite, (void *) 0);
    Thread *t = new Thread("thread1");
    t->Fork((VoidFunctionPtr) io::ioread, (void *) 0);
}