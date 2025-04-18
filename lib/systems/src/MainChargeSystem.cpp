/* Imports */
#include "MainChargeSystem.h"
#include <algorithm>
#include <cmath>




/* Constructor */
//MainChargeSystem::MainChargeSystem(float target_volt, float max_allow_cell_temp) : _target_voltage_per_cell(target_volt), _max_allowable_cell_temperature(max_allow_cell_temp){} 


/* This function uses data sent from ACU over CAN. The commented out function would be applicable over ethernet */
float MainChargeSystem::calculate_charge_current() {

  float average_voltage;
  float low_voltage;
  float high_voltage;
  float total_voltage;
  float calculated_charge_current; 
  //float voltage_taper;
  float distance_from_ideal_voltage;
  //float voltage_scalar;

  float normalized_voltage;

  average_voltage = ACUInterfaceInstance::instance().get_latest_data().average_voltage; //average voltage across the cells
  low_voltage = ACUInterfaceInstance::instance().get_latest_data().low_voltage; //the lowest voltage in any of the cells
  high_voltage = ACUInterfaceInstance::instance().get_latest_data().high_voltage; //the highest voltage in any of the cells
  total_voltage = ACUInterfaceInstance::instance().get_latest_data().total_voltage; //the total voltage in the pack



  if (high_voltage >= _ccu_data.cutoff_voltage || average_voltage >= _ccu_data.threshold_voltage || total_voltage >= _ccu_data.max_pack_voltage) { //stop charging if one of the cells or the average, or the total voltage, is too high
    _ccu_data.balancing_enabled = false;
    return 0;
  } else if (total_voltage < 510) { //only start tapering once close to total voltage (505 volts)
    _ccu_data.balancing_enabled = true;
    return _ccu_data.charger_current_max;
  } else {

    normalized_voltage = (total_voltage / _ccu_data.max_pack_voltage);
    calculated_charge_current = (_ccu_data.charger_current_max * (1 - pow(normalized_voltage, 0.5))) * 100;
    //calculated_charge_current = _ccu_data.charger_current_max * (1 + (100*std::log10f(normalized_voltage))); //NOLINT - 100 is used for scaling purposes

   
  }

  _ccu_data.calculated_charge_current = calculated_charge_current;
  return calculated_charge_current;
}



    //this works, but not as efficient
    //voltage_taper = (average_voltage - _ccu_data.threshold_voltage) / (low_voltage - _ccu_data.cutoff_voltage);
    //calculated_charge_current = _ccu_data.charger_current_max * (1 - voltage_taper);

    //distance_from_ideal_voltage = ccu_params.target_voltage_per_cell - high_voltage;
    //voltage_scalar = ((logf(distance_from_ideal_voltage+.5))/log(11))+.3; //NOLINT
    //calculated_charge_current = _ccu_data.charger_current_max * voltage_scalar; 



/*
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