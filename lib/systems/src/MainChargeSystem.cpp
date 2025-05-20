#include "MainChargeSystem.h"
#include <algorithm>
#include <cmath>

/* Constructor */
//MainChargeSystem::MainChargeSystem(float target_volt, float max_allow_cell_temp) : _target_voltage_per_cell(target_volt), _max_allowable_cell_temperature(max_allow_cell_temp){} 


void MainChargeSystem::calculate_charge_current() {

  float average_voltage = 0;
  float low_voltage = 0;
  float high_voltage = 0;
  float total_voltage = 0;
  float calculated_charge_current = 0; 

  average_voltage = ACUInterfaceInstance::instance().get_latest_data().average_voltage; //average voltage across the cells
  low_voltage = ACUInterfaceInstance::instance().get_latest_data().low_voltage; //the lowest voltage in any of the cells
  high_voltage = ACUInterfaceInstance::instance().get_latest_data().high_voltage; //the highest voltage in any of the cells
  total_voltage = ACUInterfaceInstance::instance().get_latest_data().total_voltage; //the total voltage in the pack



  /* Tells the charger to stop charging if the shutdown button is pressed or one of the cell voltags is too high */
  if (digitalRead(_ccu_data.SHDN_E_READ) != HIGH || high_voltage >= _ccu_data.cutoff_voltage) {  //ACU will cause a BMS fault if there is a cell or board temp that is too high
    _ccu_data.calculated_charge_current = 0;
    _ccu_data.balancing_enabled = false;
  } else { 
    if (low_voltage < _ccu_data.balancing_voltage) {
      _ccu_data.calculated_charge_current = _ccu_data.safe_charging_current; //15 - safe charging current to be at if not cell balancing
    } else {
      _ccu_data.calculated_charge_current = _ccu_data.charger_current_max; //30 as of now
    }
  } 
}





/* Applicable for ethernet message that has all cel voltages and temperatures. However, since we aren't using ethernet,
/* getting these values over CAN could overflow the buffer
float MainChargeSystem::calculate_charge_current(ACUAllData_s inputValues)
{ 
  float max_cell_voltage = 0;
  float max_cell_temperature = 0;  

  for (auto& e : inputValues.voltages)
  {
    if (e > max_cell_voltage) 
    {
      max_cell_voltage = e;
    }
  }

  for (auto& e : inputValues.cell_temperatures)
  {
    if (e > max_cell_temperature) 
    {
      max_cell_temperature = e;
    }
  }

  if (max_cell_voltage <= _target_voltage_per_cell && max_cell_temperature < _max_allowable_cell_temperature) //checks exit conditions
  {
    float temperature_scalar = ((_max_allowable_cell_temperature - max_cell_temperature)/10); //NOLINT when the difference is less than 10, temperature can affect charge current, assumed that when the temperature difference is greater that we don't care
    float distance_from_ideal_voltage = _target_voltage_per_cell - max_cell_voltage;
    float voltage_scalar = ((logf(distance_from_ideal_voltage+.5))/log(11))+.3; //NOLINT this is an equation and the numbers are important, it comes from the assumption that the difference between the cell voltage we want and the minimum cell voltage will be within 4 volts, at x=4 it is = to 1, at x=0 it is zero, follows ln path otherwise.
    float final_scalar = std::min(temperature_scalar, voltage_scalar); 
    float saftey_check = std::min(final_scalar, static_cast<float>(1.00)); //ensures we never go above the set MAXIMUM_NEVER_EXCEED_CURRENT
    float calculated_current = _MAXIMUM_NEVER_EXCEED_CURRENT * saftey_check; 

    return calculated_current; //amps
  }
  return 0; //amps
}  */