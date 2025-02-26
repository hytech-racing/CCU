/* Imports */
#include "MainChargeSystem.h"
#include <algorithm>

MainChargeSystem::MainChargeSystem(float target_volt, float max_charge_current, float max_cell_temp, float pid_kp, float pid_ki, float pid_kd) : target_voltage(target_volt), max_ac_charging_current(max_charge_current), max_allowable_cell_temperature(max_cell_temp), VoltPid(ccu_pid_kp, ccu_pid_ki, ccu_pid_kd){}

void MainChargeSystem::charge_cycle(CCUInput_s inputValues, CCUOutput_s &outputValues){
    if (inputValues.max_cell_voltage >= target_voltage || inputValues.max_cell_temperature > max_allowable_cell_temperature) { //checks whether or not any of the cells are charged yet
      outputValues.current_flow = false; //this will be function that actually turns on/off current flow 
      outputValues.current_setpoint = 0;
    }
    else { 
      float temperature_scalar = (max_allowable_cell_temperature - inputValues.max_cell_temperature); //This needs to be replaces with a log function  
      float voltage_scalar = VoltPid.compute(target_voltage, inputValues.max_cell_voltage);
      float final_scalar = std::min(temperature_scalar, voltage_scalar);
      outputValues.current_flow = true; //needs to be replaced with the actual thing to set current flow to the correct value
      outputValues.current_setpoint = max_ac_charging_current * final_scalar; //currently the PID returns a value greater than 1   
    }
}
 