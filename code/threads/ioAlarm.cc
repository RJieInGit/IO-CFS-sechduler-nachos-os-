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
    printf("try wake up \n");
    ihandler->wakeUp(currentRequest);
    printf("waken up \n");
      ioRequest *req = ihandler->getNextInterrupt();
    if(req !=NULL){
        iotimer->SetInterrupt(req);
        currentRequest = req;
    }
    else{
        currentRequest=NULL;
    }
}