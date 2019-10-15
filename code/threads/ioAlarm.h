#include "../machine/callback.h"
#include "../machine/iotimer.h"
#include "../lib/utility.h"
class ioAlarm : public CallBackObj{
    public :
        ioAlarm();    //we get random pending tiem from iorequest
        ~ioAlarm() {delete iotimer}; 
        
        ioRequest *currentRequest;
    private : 
        ioHandler *ihandler;
        ioTimer *iotimer;
        void CallBack(); //called when a iorequest is finished
};