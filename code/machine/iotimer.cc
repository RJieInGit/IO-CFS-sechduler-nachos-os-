#include "iotimer.h"
#include "main.h"
#include "sysdep.h"

// an ioTimer designed similiar to the tiemr. Which responsibility is 
//to set the schedule of next Iointerrupt

//initialize a ioTimer and set the interrupt if the eventQueue is not empty
 ioTimer:: ioTimer(CallBackObj *toCall){
    ioCallBack =toCall;
    SetInterrupt();
}

void ioTimer :: CallBack(){
    printf("IOTIMER callback! \n");
    ioCallBack->CallBack();
}

void ioTimer::SetInterrupt(ioRequest* req){
       // printf("set ioint now \n");
        //ASSERT(req!=NULL);
        int delay =TimerTicks；
        IntType t= IoInt;
        kernel->interrupt->Schedule(this,delay,t);
}