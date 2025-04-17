#ifndef CCUPARAMS_H
#define CCUPARAMS_H

#include <cstdint>

struct CCUParams
{
  bool balancing_enabled = false; //tells ACU whether balancing is allowed or not
  constexpr unsigned float target_voltage_per_cell = 3.1; //per cell
  constexpr unsigned float max_allowable_cell_temperature = 70; //need data for this
  constexpr unsigned float cutoff_voltage = 4; //need this value
  constexpr unsigned float curr_charger_current = 0;
  constexpr unsigned float charger_current_max = 13; //amps - double check this value (datasheet?)
};


namespace CCUConstants
{
  /* HT Scheduler Constants */
  constexpr unsigned long HT_SCHED_PERIOD_US = 20000UL;
  constexpr unsigned long UPDATE_DISPLAY_PRIORITY = 2;
  constexpr unsigned long READ_DIAL_PRIORITY = 2;
  constexpr unsigned long ENQUEUE_ACU_CAN_DATA_PRIORITY = 1;
  constexpr unsigned long ENQUEUE_CHARGER_CAN_DATA_PRIORITY = 2;
  constexpr unsigned long SEND_ETHERNET_PRIORITY = 2;
  constexpr unsigned long RECIEVE_ETHERNET_PRIORITY = 2;
  constexpr unsigned long SEND_ALL_DATA_PRIORITY = 2;
  constexpr unsigned long HT_SCHED_CAN_PERIOD = 100000UL;

  /* CAN Constants */
  const uint32_t CAN_BAUDRATE = 500000UL; 
}


#endif