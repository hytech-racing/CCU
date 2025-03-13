/* Imports */
#include "MainChargeSystem.h"
#include <algorithm>
#include <cmath>


float MainChargeSystem::calculate_charge_current(ACUAllData_s inputValues, CCUParams &chargeParams){
    double max_cell_voltage = *std::max_element(inputValues.voltages, inputValues.voltages + (sizeof(inputValues.voltages) / sizeof(inputValues.voltages[0])));
    double max_cell_temperature = *std::max_element(inputValues.cell_temperatures, inputValues.cell_temperatures + (sizeof(inputValues.cell_temperatures) / sizeof(inputValues.cell_temperatures[0])));

    if (max_cell_voltage >= chargeParams.target_voltage || max_cell_temperature > chargeParams.max_allowable_cell_temperature) { //checks whether or not any of the cells are charged yet
      return 0;
    }
    else { 
      float temperature_scalar = ((chargeParams.max_allowable_cell_temperature - max_cell_temperature)/10); //This needs to be replaces with a log function  
      float distance_from_ideal_voltage = chargeParams.max_allowable_cell_voltage - max_cell_voltage;
      float voltage_scalar = ((log(distance_from_ideal_voltage+.5))/log(11))+.3;
      float final_scalar = std::min(temperature_scalar, voltage_scalar);  
      return chargeParams.max_allowable_current * final_scalar;
    }
}