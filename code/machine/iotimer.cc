#include "iotimer.h"
#include "main.h"
#include "sysdep.h"

// an ioTimer designed similiar to the tiemr. Which responsibility is 
//to set the schedule of next Iointerrupt

//initialize a ioTimer and set the interrupt if the eventQueue is not empty
 ioTimer:: ioTimer(CallBackObj *toCall){
    ioCallBack =toCall;
    ihandler =new tocall->ihandler;
    ioRequest *req = ihandler->getNextInterrupt();
    if(req !=NULL){
        SetInterrupt(req);
    }
}

void ioTimer :: CallBack(){
    ioCallBack->CallBack();
   
}

void ioTimer::SetInterrupt(ioRequest* req){
    if(!disable){
        int delay =req->pendingTick;
        kernel->interrupt->Schedule(this,delay,IoInt);
    }
}