#ifndef __MAINCHARGE_H__
#define __MAINCHARGE_H__


#include "CCUEthernetInterface.h"
#include "CCUParams.h"

namespace MainChargeSystem{
  void calculate_charge_current(ACUAllData_s inputValues, CCUParams& chargeParams, CCUOutput_s &chargeOutputs); 
}

#endif