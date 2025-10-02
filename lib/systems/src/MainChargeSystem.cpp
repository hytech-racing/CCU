#include "MainChargeSystem.h"
#include <algorithm>
#include <cmath>


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

  bool shutdown_low = (digitalRead(_ccu_data.SHDN_E_READ) != HIGH); //e-stop on charge cart

  /** acu_state comes from the bms_status message. If shutdown is low on ACU (HVP is unplugged), acu_state = 1.
   *  If acu_state = 2, we should/are safe to be charging
   */
  bool acu_shutdown_low = ACUInterfaceInstance::instance().get_latest_data().acu_state == 1; //NOLINT
  
  bool voltage_reached = (high_voltage >= _ccu_data.cutoff_voltage) || (ACUInterfaceInstance::instance().get_latest_data().total_voltage > _ccu_data.max_pack_voltage); //NOLINT
  if (shutdown_low || acu_shutdown_low)
  {
    _ccu_data.charging_state = ChargingState_e::NOT_CHARGING;
  } else if(voltage_reached)
  {
    _ccu_data.charging_state = ChargingState_e::DONE_CHARGING;
  } else {
    _ccu_data.charging_state = ChargingState_e::CHARGING;
  }
  

  /* Tells the charger to stop charging if the shutdown button is pressed or one of the cell voltags is too high */
  if (voltage_reached || shutdown_low || acu_shutdown_low) {  //ACU will cause a BMS fault if there is a cell or board temp that is too high
    _ccu_data.calculated_charge_current = 0;
    _ccu_data.balancing_enabled = false;
  } else {
    _ccu_data.calculated_charge_current = _ccu_data.charger_current_max; // 120 = 3.4 amps
  } 
}
