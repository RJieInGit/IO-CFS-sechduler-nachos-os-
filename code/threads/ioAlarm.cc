// ioalarm.cc
//routines to put iorequest in queue and set interrupt schedule

#include "./ioAlarm.h"
#include "main.h"

Alarm:: Alarm(){
    iotime =new IoTimer(this);
    ioHandler *ihandler =new ioHandler();
}

void ioAlarm :: CallBack(){
    Interrupt *interrupt = kernel->interrupt;
    MachineStatus status = interrupt->getStatus();

    //wake up the blocked parent thread
    ihandler->wakeUp(currentRequest);
      ioRequest *req = ihandler->getNextInterrupt();
    if(req !=NULL){
        SetInterrupt(req);
        currentRequest = req;
    }
    else{
        currentRequest=NULL;
    }

    if (status != IdleMode) {
	interrupt->YieldOnReturn();
    }
}