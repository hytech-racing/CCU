/* Imports */
#include <Arduino.h>
#include <PID_RT.h>
#include "CCUParams.h"
#include "PIDParams.h"
#include "EthernetInterface.h" // this is not created yet but will take info from acu and give out usable values  

/* TO-DO 
Taking in the message from ACU protobuf recieving 
*/


bool current_flow = false;
float current_setpoint;

/* Object Instance Creation */
EthernetInterface ethernetInterface;
CCUParams ccuParams;
PID_RT pid;
PIDParams pidParams;

/* Logic */
void charge_setup() {
  pid.setInterval(pidParams.PIDrunInterval);
  pid.setKp(pidParams.Kp);
  pid.setKi(pidParams.Ki);
  pid.setKd(pidParams.Kd);
}

void charge_cycle() { //add safe start that ramps up to max over 10 seconds
  if (ethernetInterface.maxCellV >= ccuParams.target_voltage || ethernetInterface.maxCellTemp > ccuParams.ideal_cell_temp) { //checks whether or not any of the cells are charged yet
      current_flow = false; //this should be a function that actually turns on/off current flow 
  }
  else { 
    pid.compute(ethernetInterface.maxCellTemp-ccuParams.ideal_cell_temp); //also probably account to voltage
    float pidTemp = pid.getOutput();
    pid.compute(ethernetInterface.maxCellV-ccuParams.target_voltage);
    float pidVolts = pid.getOutput();
    float scalar = min(pidTemp, pidVolts);
    current_setpoint = ccuParams.max_AC_current * scalar; //replace with just a Pd
    current_flow = true; //same as line 32
  }
}