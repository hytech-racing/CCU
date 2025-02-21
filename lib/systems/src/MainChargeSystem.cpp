/* Imports */
#include "MainChargeSystem.h"

namespace calc {
  float min(float v1, float v2){
  //minimum value function
      if (v1 < v2){
          return v1;
      }
      else{
          return v2;
      }
  };
};

void MainChargeSystem::charge_cycle(CCUInputValues inputValues, CCUOutputValues &outputValues){
    if (inputValues.maxCellV >= CCUParams::target_voltage || inputValues.maxCellTemp > CCUParams::ideal_cell_temp) { //checks whether or not any of the cells are charged yet
      outputValues.currentFlow = false; //this will be function that actually turns on/off current flow 
      outputValues.current_setpoint = 0;
    }
    else { 
      float pidTemp = pid.compute(CCUParams::ideal_cell_temp, inputValues.maxCellTemp); 
      float pidVolts = pid.compute(CCUParams::target_voltage, inputValues.maxCellV);
      float scalar = calc::min(pidTemp, pidVolts);
      outputValues.currentFlow = true; //needs to be replaced with the actual thing to set current flow to the correct value
      outputValues.current_setpoint = CCUParams::max_AC_current * scalar; //currently the PID returns a value greater than 1   
    }
}
