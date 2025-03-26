#ifndef MAINCHARGE_H
#define MAINCHARGE_H

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
 * @brief function that returns a float value of the current to be sent to charge controller for this charge cycle 
 * @param ACUAllData_s struct populated with raw data from ACU
 * @param CCUParams struct with params that control the charge control unit
 */
  float calculate_charge_current(ACUAllData_s inputValues, CCUParams& chargeParams); 
}

#endif