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
     * @param ccu_data A reference to the main CCU data struct
     */
    MainChargeSystem(CCUData &ccu_data) :  _ccu_data(ccu_data) {};

    /**
     * @brief Calculates the correct charge current based on ACU data and
     * safety limits. Updates _ccu_data.calculated_charge_current and
     * _ccu_data.charging_state directly.
     */
    void calculate_charge_current(); 

  private:
    CCUData &_ccu_data;
};

using MainChargeSystemInstance = etl::singleton<MainChargeSystem>;


#endif