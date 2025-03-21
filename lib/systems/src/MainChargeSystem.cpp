/* Imports */
#include "MainChargeSystem.h"
#include <algorithm>
#include <cmath>

constexpr int NUM_CELLS = 126; 
constexpr int NUM_TEMP_SENSORS = 48;
constexpr int MAXIMUM_NEVER_EXCEED_CURRENT = 25; //25 is a tentative amp value based on 6kw at 240 volts, may need to be adjusted depending on voltage

float MainChargeSystem::calculate_charge_current(ACUAllData_s inputValues, CCUParams &chargeParams)
{ 
  float max_cell_voltage = 0;
  float max_cell_temperature = 0;  

  for (int i = 0; i < NUM_CELLS; i++)
  {
    if (inputValues.voltages[i] > max_cell_voltage) 
    {
      max_cell_voltage = inputValues.voltages[i];
    }
  }

  for (int i = 0; i < NUM_TEMP_SENSORS; i++)
  {
    if (inputValues.cell_temperatures[i] > max_cell_temperature) 
    {
      max_cell_temperature = inputValues.cell_temperatures[i];
    }
  }
  

  if (max_cell_voltage <= chargeParams.target_voltage && max_cell_temperature < chargeParams.max_allowable_cell_temperature) //checks exit conditions
  {
    float temperature_scalar = ((chargeParams.max_allowable_cell_temperature - max_cell_temperature)/10); //when the difference is less than 10, temperature can affect charge current, assumed that when the temperature difference is greater that we don't care
    float distance_from_ideal_voltage = chargeParams.max_allowable_cell_voltage - max_cell_voltage;
    float voltage_scalar = ((log(distance_from_ideal_voltage+.5))/log(11))+.3; //this equation comes from the assumption that the difference between the cell voltage we want and the minimum cell voltage will be within 4 volts, at x=4 it is = to 1, at x=0 it is zero, follows ln path otherwise.
    float final_scalar = std::min(temperature_scalar, voltage_scalar); 
    float saftey_check = std::min(final_scalar, static_cast<float>(1)); //ensures we never go above the set MAXIMUM_NEVER_EXCEED_CURRENT
    float calculated_current = MAXIMUM_NEVER_EXCEED_CURRENT * saftey_check; 

    return calculated_current; //amps
  }

  return 0; //amps

}
