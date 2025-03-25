#ifndef __MAINCHARGE_H__
#define __MAINCHARGE_H__

#ifdef TEENSY_OPT_SMALLEST_CODE
#include "CCUEthernetInterface.h"
#endif

#include "CCUParams.h"
#include "SharedFirmwareTypes.h"

namespace MainChargeSystem
{
  constexpr int NUM_CELLS = 126; 
  constexpr int NUM_TEMP_SENSORS = 48;
  constexpr int MAXIMUM_NEVER_EXCEED_CURRENT = 25; //25 is a tentative amp value based on 6kw at 240 volts, may need to be adjusted depending on voltage



  /**
 * @brief void returning function that sets current_setpoint in the output struct to a calculated current value based on current cell voltage and temp 
 * @param ACUAllData_s struct populated with raw data from ACU
 * @param CCUParams struct with params that control the charge control unit
 */
  float calculate_charge_current(ACUAllData_s inputValues, CCUParams& chargeParams); 
}

#endif