#include "io.h"
#include "../threads/main.h"

ioRequest:: ioRequest(requestType t, Thread *parent){
    parentThread= parent;
    type=t;
    int random= rand()%10;
    if(type=ioread)
        random=random*100;
    createStamp= kernel->stat->totalTicks;
}



 void io:: ioread(int arg){
    enum requestType read =ioread;
    ioRequest* req=new ioRequest(read,kernel->currentThread);
    // if there is no current running iorequest then set up the interrupt
    if(kernel->IoAlarm->currentRequest!=NULL){
         kernel->ioEventQueue->Append(req);
    }
    //if there is an running iorequest then put the request in eventqueue.
    else{
        kernel->IoAlarm->currentRequest=req;
        kernel->IoAlarm->iotimer->SetInterrupt(req);
    }

    kernel->currentThread->Sleep(false);
    //print after callback from alarmer, which simulate the execution time
    printf("read some content as an iorequest\n");
    
    //just simulate output, input depends on user so that is unable to simulate
} 
void io:: iowrite(int arg){
    enum requestType write =iowrite;
    ioRequest* req=new ioRequest(write,kernel->currentThread);
    if(kernel->IoAlarm->currentRequest!=NULL){
         kernel->ioEventQueue->Insert(req);
    }
    else{
        kernel->IoAlarm->currentRequest=req;
        kernel->IoAlarm->iotimer->SetInterrupt(req);
    }
    kernel->currentThread->Sleep(false);
    //print after callback from alarmer, which simulate the execution time
    printf("%s :write some content as an iorequest at :%d ticks \n",kernel->currentThread->getName());
    
    //just simulate output, input depends on user so that is unable to simulate
}

void ioHandler::wakeUp(ioRequest *req){
    //simply wake up the parent thread
    kernel->scheduler->ReadyToRun(req->parentThread);
}

ioRequest* ioHandler:: getNextInterrupt(){
    if(kernel->ioEventQueue->IsEmpty())
        return NULL;
    else{
        return kernel->ioEventQueue->RemoveFront();
    }
}

