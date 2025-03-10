/* Imports */
#include "MainChargeSystem.h"
#include <algorithm>
#include <cmath>

MainChargeSystem::MainChargeSystem(float target_volt, float max_charge_current, float max_cell_temp) : target_voltage(target_volt), max_ac_charging_current(max_charge_current), max_allowable_cell_temperature(max_cell_temp){}

void MainChargeSystem::charge_cycle(CCUInput_s inputValues, CCUOutput_s &outputValues){
    if (inputValues.max_cell_voltage >= target_voltage || inputValues.max_cell_temperature > max_allowable_cell_temperature) { //checks whether or not any of the cells are charged yet
      outputValues.current_flow = false; //this will be function that actually turns on/off current flow 
      outputValues.current_setpoint = 0;
    }
    else { 
      float temperature_scalar = ((max_allowable_cell_temperature - inputValues.max_cell_temperature)/10); //This needs to be replaces with a log function  
      float distance_from_ideal_voltage = target_voltage - inputValues.max_cell_voltage;
      float voltage_scalar = ((log(distance_from_ideal_voltage+.5))/log(11))+.3;
      float final_scalar = std::min(temperature_scalar, voltage_scalar);
      outputValues.current_flow = true; //needs to be replaced with the actual thing to set current flow to the correct value
      outputValues.current_setpoint = max_ac_charging_current * final_scalar; //currently the PID returns a value greater than 1   
    }
}