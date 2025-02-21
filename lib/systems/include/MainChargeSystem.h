#ifndef __MAINCHARGE_H__
#define __MAINCHARGE_H__


#include "CCUPID.h"
#include "EthernetInterface.h"
#include "CCUParams.h"


class MainChargeSystem {
  public:
    MainChargeSystem() : pid() {}
    void charge_cycle(CCUInputValues inputValues, CCUOutputValues& outputValues); //need to add safe start that ramps up to max over 10 seconds
  private:
    PID pid;
    };

#endif
