#include "iotimer.h"
#include "main.h"
#include "sysdep.h"

// an ioTimer designed similiar to the tiemr. Which responsibility is 
//to set the schedule of next Iointerrupt

//initialize a ioTimer and set the interrupt if the eventQueue is not empty
 ioTimer:: ioTimer(CallBackObj *toCall){
    ioCallBack =toCall;

    ioRequest *req = ((ioAlarm*)toCall)->ihandler->getNextInterrupt();
    if(req !=NULL){
        SetInterrupt(req);
    }
}

void ioTimer :: CallBack(){
    pringf("IOTIMER callback! \n");
    ioCallBack->CallBack();
   
}

void ioTimer::SetInterrupt(ioRequest* req){
  
        int delay =req->pendingTick;
        IntType t= IoInt;
        kernel->interrupt->Schedule(this,delay,t);
}