/* Imports */
#include "MainChargeSystem.h"
#include <algorithm>
#include <cmath>

/**
 * @brief void returning function that sets current_setpoint in the output struct to a calculated current value based on current cell voltage and temp 
 * @param ACUAllData_s struct populated with raw data from ACU
 * @param CCUParams struct with params that control the charge control unit
 */
float MainChargeSystem::calculate_charge_current(ACUAllData_s inputValues, CCUParams &chargeParams)
 {

    double max_cell_voltage = *std::max_element(inputValues.voltages, inputValues.voltages + (sizeof(inputValues.voltages) / sizeof(inputValues.voltages[0]))); //sizeof is needed because max value takes in a start and end memory location of the array
    double max_cell_temperature = *std::max_element(inputValues.cell_temperatures, inputValues.cell_temperatures + (sizeof(inputValues.cell_temperatures) / sizeof(inputValues.cell_temperatures[0])));

    if (max_cell_voltage >= chargeParams.target_voltage || max_cell_temperature > chargeParams.max_allowable_cell_temperature) { //checks whether or not any of the cells are charged yet
      return 0;
    }
    else { 
      float temperature_scalar = ((chargeParams.max_allowable_cell_temperature - max_cell_temperature)/10); //divide by 10 to ensuse that scalar is within 0-1. 
      float distance_from_ideal_voltage = chargeParams.max_allowable_cell_voltage - max_cell_voltage;
      float voltage_scalar = ((log(distance_from_ideal_voltage+.5))/log(11))+.3;
      float final_scalar = std::min(temperature_scalar, voltage_scalar);  
      float calculated_current = 25 * final_scalar; //25 is a tentative amp value based on 6kw at 240 volts, may need to be asjusted depending on voltage
      return calculated_current;
    }
}
