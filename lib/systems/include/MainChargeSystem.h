#ifndef MAINCHARGE_H
#define MAINCHARGE_H

#include "CCUData.h"

#include "ACUInterface.h"

#include "SharedFirmwareTypes.h"

#ifdef TEENSY_OPT_SMALLEST_CODE
#include <Arduino.h>
#endif

#ifdef TESTING_SYSTEMS
#include "mockArduino.h"
#endif


class MainChargeSystem {
  public:
    /**
     * @param target_volt The wanted final voltage for an individual cell, the charger will not charge past this voltage
     * @param max_cell_temp The maximum allowable cell temperature while charging
     */
    MainChargeSystem(CCUData &ccu_data) :  _ccu_data(ccu_data) {};

  /**
 * @brief function that returns a float value of the current to be sent to charge controller for this charge cycle 
 * @param ACUAllData_s struct populated with raw data from ACU
 */
    void calculate_charge_current(); 

  private:
    const float _MAXIMUM_NEVER_EXCEED_CURRENT = 25; //25 is a tentative amp value based on 6kw at 240 volts, may need to be adjusted depending on voltage
    float _target_voltage_per_cell; //final voltage that we should charge to
    float _max_allowable_cell_temperature;
    CCUData &_ccu_data;
};

using MainChargeSystemInstance = etl::singleton<MainChargeSystem>;


#endif