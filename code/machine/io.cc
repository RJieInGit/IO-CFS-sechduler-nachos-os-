#include "io.h"
#include "../threads/main.h"

ioRequest:: ioRequest(requestType t, Thread *parent){
    parentThread= parent;
    type=t;
    int random= (rand()%10)*100;
    if(type==requestType::ioread)
        random=random*100;
    pendingTick=random;
    createStamp= kernel->stats->totalTicks;
}



 void io:: ioread(int arg){
    requestType read =requestType:: ioread;
    ioRequest* req=new ioRequest(read,kernel->currentThread);
    // if there is no current running iorequest then set up the interrupt
    printf("read iorequest created at %d tick, \n",kernel->stats->totalTicks);
    if(kernel->IoAlarm->currentRequest!=NULL){
         kernel->ioEventQueue->Insert(req);
    }
    //if there is an running iorequest then put the request in eventqueue.
    else{
        kernel->IoAlarm->currentRequest=req;
        kernel->IoAlarm->iotimer->SetInterrupt(req);
    }
    kernel->interrupt->SetLevel(IntOff);
    kernel->currentThread->Sleep(false);
    kernel->interrupt->SetLevel(IntOn);
    //print after callback from alarmer, which simulate the execution time
    printf("read some content as an iorequest, ioread finished currentTick: %d\n",kernel->stats->totalTicks);
    
    //just simulate output, input depends on user so that is unable to simulate
} 
void io:: iowrite(int arg){
    
    requestType write =requestType:: iowrite;
    ioRequest* req=new ioRequest(write,kernel->currentThread);
printf("write iorequest created at %d tick, the io thread is %s the exetime is : %d \n",kernel->stats->totalTicks,kernel->currentThread->getName(),req->pendingTick
);
    if(kernel->IoAlarm->currentRequest!=NULL){
         kernel->ioEventQueue->Insert(req);
    }
    else{
        kernel->IoAlarm->currentRequest=req;
        kernel->IoAlarm->iotimer->SetInterrupt(req);
    }
    printf("write thread sleep\n");
    kernel->interrupt->SetLevel(IntOff);
    kernel->currentThread->Sleep(false);
    kernel->interrupt->SetLevel(IntOn);
    printf("write thread wake up");
    //print after callback from alarmer, which simulate the execution time
    printf("%s :write some content as an iorequest at :%d ticks \n",kernel->stats->totalTicks);
    
    //just simulate output, input depends on user so that is unable to simulate
}

void ioHandler::wakeUp(ioRequest *req){
    //simply wake up the parent thread
    kernel->scheduler->ReadyToRun(req->parentThread);
    printf("wake up parent %s",req->parentThread->getName());
}

ioRequest* ioHandler:: getNextInterrupt(){
    if(kernel->ioEventQueue->IsEmpty())
        return NULL;
    else{
        return kernel->ioEventQueue->RemoveFront();
    }
}

