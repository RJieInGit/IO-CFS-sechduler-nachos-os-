#include "../machine/callback.h"
#include "../machine/iotimer.h"
#include "../lib/utility.h"
#pragma once
class ioAlarm : public CallBackObj{
    public :
        ioAlarm();    //we get random pending tiem from iorequest
        ~ioAlarm() {delete iotimer;}; 
        
        ioRequest *currentRequest;
        ioHandler *ihandler;
        ioTimer *iotimer;
    private : 
       
        void CallBack(); //called when a iorequest is finished
};