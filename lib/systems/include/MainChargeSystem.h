#ifndef __MAINCHARGE_H__
#define __MAINCHARGE_H__



#include "CCUParams.h"
#include "CCUEthernetInterface.h"



namespace MainChargeSystem
{
  /**
 * @brief void returning function that sets current_setpoint in the output struct to a calculated current value based on current cell voltage and temp 
 * @param ACUAllData_s struct populated with raw data from ACU
 * @param CCUParams struct with params that control the charge control unit
 */
  float calculate_charge_current(ACUAllData_s inputValues, CCUParams& chargeParams); 
}

#endif