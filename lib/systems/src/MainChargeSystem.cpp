/* Imports */
#include "MainChargeSystem.h"
#include <algorithm>
#include <cmath>

MainChargeSystem::MainChargeSystem(float target_volt, float max_charge_current, float max_cell_temp) : target_voltage(target_volt), max_ac_charging_current(max_charge_current), max_allowable_cell_temperature(max_cell_temp){}

float MainChargeSystem::calculate_charge_current(ACUAllData_s inputValues, CCUOutput_s &outputValues){
    double max_cell_voltage = *std::max_element(inputValues.voltages, inputValues.voltages + (sizeof(inputValues.voltages) / sizeof(inputValues.voltages[0])));
    double max_cell_temperature = *std::max_element(inputValues.cell_temperatures, inputValues.cell_temperatures + (sizeof(inputValues.cell_temperatures) / sizeof(inputValues.cell_temperatures[0])));

    if (max_cell_voltage >= target_voltage || max_cell_temperature > max_allowable_cell_temperature) { //checks whether or not any of the cells are charged yet
      outputValues.current_flow = false; //this will be function that actually turns on/off current flow 
      outputValues.current_setpoint = 0;
      return 0;
    }
    else { 
      float temperature_scalar = ((max_allowable_cell_temperature - max_cell_temperature)/10); //This needs to be replaces with a log function  
      float distance_from_ideal_voltage = target_voltage - max_cell_voltage;
      float voltage_scalar = ((log(distance_from_ideal_voltage+.5))/log(11))+.3;
      float final_scalar = std::min(temperature_scalar, voltage_scalar);
      outputValues.current_flow = true; //needs to be replaced with the actual thing to set current flow to the correct value
      outputValues.current_setpoint = max_ac_charging_current * final_scalar; //currently the PID returns a value greater than 1   
      return max_ac_charging_current * final_scalar;
    }
}