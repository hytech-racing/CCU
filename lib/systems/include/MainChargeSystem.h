#ifndef __MAINCHARGE_H__
#define __MAINCHARGE_H__


#include "CCUPID.h"
#include "EthernetInterface.h"
#include "CCUParams.h"

/**
 * MainChargeSystem has its own PID object for adjusting error
 * It needs to have a function that is a one loop of charging where CCU gets info about the cells, calculates correct current,
 * and sends out current set and whether to enable charging or not.
*/
class MainChargeSystem {
  public:
    /**
     * @param target_volt The wanted final voltage for an individual cell
     * @param max_charge_current The maximum charge current that should be given to ACU
     * @param max_cell_temp The maximum allowable cell temperature while charging
     * @param pid_kp The Kp parameter for the PID that controls charging current with respect to how close the max cell is to the target voltage
     * @param pid_ki The Ki parameter for the PID that controls charging current with respect to how close the max cell is to the target voltage
     * @param pid_kd The Kd parameter for the PID that controls charging current with respect to how close the max cell is to the target voltage
     */
    MainChargeSystem(float target_volt, float max_charge_current, float max_cell_temp, float pid_kp, float pid_ki, float pid_kd);
    /**
     * @param CCUInput_s The incoming struct from ACU
     * @param CCUOutput_s The output struct from CCU with charge current and whether to enable charging
     */
    void charge_cycle(CCUInput_s inputValues, CCUOutput_s& outputValues); //need to add safe start that ramps up to max over 10 seconds

  private:

    float target_voltage;
    float max_ac_charging_current;
    float max_allowable_cell_temperature;
    float ccu_pid_kp;
    float ccu_pid_ki;
    float ccu_pid_kd;
    PID VoltPid;
    };

#endif
