#ifndef __MAINCHARGE_H__
#define __MAINCHARGE_H__


#include "CCUParams.h"
#include "CCUEthernetInterface.h"

namespace MainChargeSystem{
  float calculate_charge_current(ACUAllData_s inputValues, CCUParams& chargeParams); 
}

#endif