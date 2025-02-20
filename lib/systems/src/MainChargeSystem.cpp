/* Imports */
#include "MainChargeSystem.h"

//need to add a way to create the PID object so the same one is used for the charging so that the prev_error works
namespace calc {
  float min(float v1, float v2){
      if (v1 < v2){
          return v1;
      }
      else{
          return v2;
      }
  };
};

float MainChargeSystem::charge_cycle(CCUInputValues inputValues, CCUOutputValues &outputValues){
    if (inputValues.maxCellV >= CCUParams::target_voltage || inputValues.maxCellTemp > CCUParams::ideal_cell_temp) { //checks whether or not any of the cells are charged yet
      outputValues.currentFlow = false; //this should be a function that actually turns on/off current flow 
      current_setpoint = 0;
      return current_setpoint;
    }
    else { 
      float pidTemp = pid.compute(CCUParams::ideal_cell_temp, inputValues.maxCellTemp); 
      float pidVolts = pid.compute(CCUParams::target_voltage, inputValues.maxCellV);
      float scalar = calc::min(pidTemp, pidVolts);
      outputValues.currentFlow = true; //needs to be replaced with the actual thing to set current flow to the correct value
      current_setpoint = CCUParams::max_AC_current * scalar; //currently the PID returns a value greater than 1
      return current_setpoint;      
    }
}
