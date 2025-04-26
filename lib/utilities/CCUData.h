#ifndef CCUDATA_H
#define CCUDATA_H

#include <cstdint>

struct CCUData
{
  bool balancing_enabled = false; //tells ACU whether balancing is allowed or not
  static constexpr float max_allowable_cell_temperature = 70; //need data for this
  static constexpr float cutoff_voltage = 4.2; //max voltage that cells can be at - if high = this, stop charging
  static constexpr float charger_current_max = 120; //amps
  float calculated_charge_current = 0;
  float threshold_voltage = 4.0; //when to begin tapering charge current - based purely on cutoff_voltage so value subject to change
  static constexpr float min_pack_voltage = 403; //need to double check this number
  static constexpr float max_pack_voltage = 520; 
  static constexpr const int SHDN_E_READ = 4;
};


namespace CCUConstants
{
  /* Task Constants */
  constexpr unsigned long KICK_WATCHDOG_PERIOD = 2000UL; //500 hz
  constexpr unsigned long KICK_WATCHDOG_PRIORITY = 1;

  constexpr unsigned long TICK_STATE_MACHINE_PERIOD = 1000UL; //1000 hz
  constexpr unsigned long TICK_STATE_MACHINE_PRIORITY = 2;

  constexpr unsigned long SAMPLE_CAN_DATA_PRIORITY = 3; //0?
  constexpr unsigned long SAMPLE_CAN_DATA_PERIOD = 1000UL; //1000 hz
  
  constexpr unsigned long ENQUEUE_ACU_CAN_DATA_PRIORITY = 4;
  constexpr unsigned long ENQUEUE_ACU_CAN_DATA_PERIOD = 100000UL; //100 hz

  constexpr unsigned long ENQUEUE_CHARGER_CAN_DATA_PRIORITY = 5;
  constexpr unsigned long ENQUEUE_CHARGER_CAN_DATA_PERIOD = 100000UL;

  constexpr unsigned long HT_SCHED_PERIOD_US = 20000UL;
  constexpr unsigned long UPDATE_DISPLAY_PRIORITY = 9;
  constexpr unsigned long READ_DIAL_PRIORITY = 10;
  constexpr unsigned long SEND_ETHERNET_PRIORITY = 8;
  constexpr unsigned long RECIEVE_ETHERNET_PRIORITY = 7;
  constexpr unsigned long SEND_ALL_DATA_PRIORITY = 6;
  constexpr unsigned long HT_SCHED_CAN_PERIOD = 100000UL;

  /* CAN Constants */
  const uint32_t CAN_BAUDRATE = 500000; //CAN for ACU
  const uint32_t CHARGER_CAN_BAUDRATE = 500000; //CAN for charger
}


#endif