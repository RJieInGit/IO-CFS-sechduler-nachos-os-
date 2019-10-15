// ioalarm.cc
//routines to put iorequest in queue and set interrupt schedule

#include "./ioAlarm.h"
#include "main.h"

ioAlarm:: ioAlarm(){
    ihandler =new ioHandler();
    iotimer =new ioTimer(this);
}

void ioAlarm :: CallBack(){
    printf("IOALARMER CALLBACK! \n");
    Interrupt *interrupt = kernel->interrupt;
    MachineStatus status = interrupt->getStatus();

    //wake up the blocked parent thread
    printf("try wake up all\n");
    List<ioRequest*> temp;
    
    while(!kernel->ioEventQueue->IsEmpty()){
        ioRequest *req=kernel->ioEventQueue->RemoveFront();
        if(req->pendingTick<=kernel->stats->totalTicks){
            printf("here\n");
            ihandler->wakeUp(req);
            printf("here2\n");
        }
        else
        {
            printf("io in queue %d \n",kernel->ioEventQueue->NumInList());
            temp.Append(req);
        }
    }
    while(!temp.IsEmpty()){
        kernel->ioEventQueue->Insert(temp.RemoveFront());
    }
    printf("waken up all \n");

}