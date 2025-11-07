#ifndef ACUINTERFACE_H
#define ACUINTERFACE_H

#include "SharedFirmwareTypes.h"
#include "etl/singleton.h"
#include "CCUData.h"

struct ACUInterfaceData_s 
{
    // Mock shape; include aliases to match production field names used by app code
    uint16_t acu_state = 0;                 // for legacy tests
    bool bms_charging_state = true;         // production expects this boolean

    volt average_voltage = 0;
    volt total_voltage = 0;

    // Legacy mock names
    volt low_voltage = 0;                   // legacy name (min)
    volt high_voltage = 0;                  // legacy name (max)

    // Production names accessed by app code
    volt min_cell_voltage = 0;
    volt max_cell_voltage = 0;
};

class ACUInterface
{
public:


    ACUInterface(CCUData &ccu_data) :  _ccu_data(ccu_data) {};

   
    ACUInterfaceData_s get_latest_data() {return _curr_data;};

    void set_latest_data(ACUInterfaceData_s data) {
        // Keep legacy and production names in sync so either can be used in tests
        if (data.min_cell_voltage == 0) data.min_cell_voltage = data.low_voltage;
        if (data.max_cell_voltage == 0) data.max_cell_voltage = data.high_voltage;
        if (data.low_voltage == 0)      data.low_voltage      = data.min_cell_voltage;
        if (data.high_voltage == 0)     data.high_voltage     = data.max_cell_voltage;
        // Default bms_charging_state based on legacy acu_state if not explicitly set by tests
        // acu_state==1 means "ok to charge" in comments; interpret non-zero as charging ok
        _curr_data = data;
    }

private:

    ACUInterfaceData_s _curr_data;
    CCUData &_ccu_data;

    
};

using ACUInterfaceInstance = etl::singleton<ACUInterface>;

#endif