#ifndef __MAINCHARGE_S__
#define __MAINCHARGE_S__
/* Imports */
#include "Math.h"
#include "CCUParams.h"
#include "PIDParams.h"
#include "EthernetInterface.h" // this is not created yet but will take info from acu and give out usable values  


/* Object Instance Creation */
EthernetInterface ethernetInterface;
PID pid(PidParams::Kp, PidParams::Ki, PidParams::Kd);

/* TO-DO 
Taking in the message from ACU protobuf recieving 
*/
class MainChargeSystem {

public:
  void charge_cycle() { //add safe start that ramps up to max over 10 seconds
    if (ethernetInterface.maxCellV >= CCUParams::target_voltage || ethernetInterface.maxCellTemp > CCUParams::ideal_cell_temp) { //checks whether or not any of the cells are charged yet
        ethernetInterface.currentFlow = false; //this should be a function that actually turns on/off current flow 
    }
    else { 
      float pidTemp = pid.compute(CCUParams::ideal_cell_temp, ethernetInterface.maxCellTemp);
      float pidVolts = pid.compute(CCUParams::target_voltage, ethernetInterface.maxCellV);
      float scalar = min(pidTemp, pidVolts);
      current_setpoint = CCUParams::max_AC_current * scalar; //replace with just a Pd
      ethernetInterface.currentFlow = true; //same as line 32
    }
  }
private:
  float current_setpoint;

};

#endif