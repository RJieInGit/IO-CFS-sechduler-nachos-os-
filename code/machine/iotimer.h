#include "copyright.h"
#include "utility.h"
#include "callback.h"
#include "./io.h"
#pragma once 

// The following class defines a hardware timer. 
class ioTimer : public CallBackObj {
  public:
    ioTimer(CallBackObj *toCall);
				// Initialize the timer, and callback to "toCall"
				// every time slice.
    virtual ~ioTimer() {}
    
    void Disable() { disable = TRUE; }
    				// Turn timer device off, so it doesn't
				// generate any more interrupts.
    void CallBack();		// called internally when the hardware
				// timer generates an interrupt

    void SetInterrupt(ioRequest* req);  	// cause an interrupt to occur in the
    				// the future after a fixed or random
				// delay

  private:
    int ticks;         //the simulated pending ticks before we finish the iorequest
    CallBackObj *ioCallBack; // call this every Time that the scheduled iointerrupt is done 
    bool disable;		// turn off the timer device after next
    				// interrupt.
    
   
    ioHandler *ihandler;
    
};