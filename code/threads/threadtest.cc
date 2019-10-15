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


void TestIO(){
    printf("here1\n");
Thread *t = new Thread("thread0");
    t->Fork((VoidFunctionPtr) io::iowrite, (void *)0);
    printf("here2\n");
    Thread *t1 = new Thread("thread1");
    t1->Fork((VoidFunctionPtr) io::iowrite, (void *)0);
    Thread *t2 = new Thread("thread2");
    t2->Fork((VoidFunctionPtr) io::iowrite, (void *)0);
    Thread *t3 = new Thread("thread3");
    t3->Fork((VoidFunctionPtr) io::ioread, (void *) 0);
    Thread *t4 = new Thread("thread4");
    printf("here3\n");
    t4->Fork((VoidFunctionPtr) io::ioread, (void *) 0);
    Thread *t5 = new Thread("thread5");
    t5->Fork((VoidFunctionPtr) io::iowrite, (void *) 0);
    Thread *t6 = new Thread("thread6");
    t6->Fork((VoidFunctionPtr) io::ioread, (void *) 0);
    printf("here4\n");
}
void
ThreadTest()
{
    printf("here0\n");
    TestIO();
    
}


