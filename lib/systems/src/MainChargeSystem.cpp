/* Imports */
#include "MainChargeSystem.h"
#include "CCUParams.h"
#include "ACUInterface.h"
#include "ChargerInterface.h"
#include <algorithm>
#include <cmath>

extern struct CCUParams ccu_params;

/* Constructor */
MainChargeSystem::MainChargeSystem(float target_volt, float max_allow_cell_temp) : _target_voltage_per_cell(target_volt), _max_allowable_cell_temperature(max_allow_cell_temp){} 


/* This function uses data sent from ACU over CAN. The commented out function would be applicable over ethernet */
float MainChargeSystem::calculate_charge_current(float target_volt) {

  volt average_voltage = ACUInterfaceInstance::instance().get_latest_data().average_voltage; //average voltage across the cells
  volt low_voltage = ACUInterfaceInstance::instance().get_latest_data().low_voltage; //the lowest voltage in any of the cells
  volt high_voltage = ACUInterfaceInstance::instance().get_latest_data().high_voltage; //the highest voltage in any of the cells

  ccu_params.curr_charger_current = ChargerInterfaceInstance::instance().get_latest_charger_data().output_current_high; //the current the charger is supplying at the moment


  float charge_current; // amp (initialization)

  if (average_voltage <= ccu_params.cutoff_voltage) { //stop charging 

    ccu_params.balancing_enabled = false;
    return 0;

  } else {

    float voltage_taper = (high_voltage - target_volt) / (ccu_params.cutoff_voltage - target_volt);
    charge_current = ccu_params.charger_current_max * (1 - voltage_taper); 

  }

  return charge_current;
  
}


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