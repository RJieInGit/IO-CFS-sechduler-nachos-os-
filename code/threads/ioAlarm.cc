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
    ihandler->wakeUp(currentRequest);
      ioRequest *req = ihandler->getNextInterrupt();
    if(req !=NULL){
        iotimer->SetInterrupt(req);
        currentRequest = req;
    }
    else{
        currentRequest=NULL;
    }

    if (status != IdleMode) {
	interrupt->YieldOnReturn();
    }
}