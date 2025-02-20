#ifndef __MAINCHARGE_H__
#define __MAINCHARGE_H__


#include "CCUPID.h"
#include "EthernetInterface.h"
#include "CCUParams.h"



/* Object Instance Creation */ //should I be creating these instances in this headder file??

/* TO-DO 
Taking in the message from ACU protobuf recieving 
*/
class MainChargeSystem {
  public:
    MainChargeSystem() : pid() {}
    float charge_cycle(CCUInputValues inputValues, CCUOutputValues& outputValues); //add safe start that ramps up to max over 10 seconds
  private:
    float current_setpoint;
    PID pid;
    };

#endif
