
#include "../threads/thread.h"
#pragma once
enum requestType { ioread, iowrite};
// each io event is considered as a io request

class ioRequest{
    public : 
    
     requestType type; 
     Thread* parentThread;
     int pendingTick;      //randomly generated (read >> write)
     int createStamp;      // time stamp on create (tick count)
     int Compare(ioRequest* i1,ioRequest* i2);

     ioRequest(requestType t,Thread *parent);         //generate simulate pendingTick
     ~ioRequest();
};

class ioHandler{
    public :
        void wakeUp(ioRequest *req);  //once the request is done, wake up the previous blocked thread.
        ioRequest* getNextInterrupt();     //search the eventQueue and set next IO interrupt, return Null if the queue is empty
};

class io{

    public :
       static void ioread(int arg);        //simulating  create a new request and put it in queue
       static  void iowrite(int arg);
};