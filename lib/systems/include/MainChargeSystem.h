#ifndef __MAINCHARGE_H__
#define __MAINCHARGE_H__


#include "CCUEthernetInterface.h"




class MainChargeSystem {
  public:
    /**
     * @param target_volt The wanted final voltage for an individual cell
     * @param max_charge_current The maximum charge current that should be given to ACU
     * @param max_cell_temp The maximum allowable cell temperature while charging
     */
    MainChargeSystem(float target_volt, float max_charge_current, float max_cell_temp);
    /**
     * @param CCUInput_s The incoming struct from ACU
     * @param CCUOutput_s The output struct from CCU with charge current and whether to enable charging
     */
    float calculate_charge_current(ACUAllData_s inputValues, CCUOutput_s& outputValues); 

  private:

    float target_voltage;
    float max_ac_charging_current;
    float max_allowable_cell_temperature;
    };

#endif
