#ifndef __MAINCHARGE_H__
#define __MAINCHARGE_H__


#include "CCUEthernetInterface.h"
#include "CCUParams.h"



class MainChargeSystem {
  public:
    /**
     * @param ACUAllData_s All raw data from the ACU
     * @param CCUParams User set params for the charge controller
     * @param CCUOutput_s The output struct from CCU with charge current and whether to enable charging
     */
    void calculate_charge_current(ACUAllData_s inputValues, CCUParams& chargeParams, CCUOutput_s &chargeOutputs); 

  private:
    };

#endif
