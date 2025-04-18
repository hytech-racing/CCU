#ifndef ACUINTERFACE_H
#define ACUINTERFACE_H

#include "SharedFirmwareTypes.h"
#include "etl/singleton.h"
#include "CCUData.h"

struct ACUInterfaceData_s 
{
    //unsigned long last_recv_status_millis;
    //uint16_t acu_state;
    volt average_voltage = 0;
    volt low_voltage = 0;
    volt high_voltage = 0;
    volt total_voltage = 0;
    //bool heartbeat_ok;
};

class ACUInterface
{
public:


    ACUInterface(CCUData &ccu_data) :  _ccu_data(ccu_data) {};

   
    ACUInterfaceData_s get_latest_data() {return _curr_data;};

    void set_latest_data(ACUInterfaceData_s data) {
        _curr_data = data;
    }

private:

    ACUInterfaceData_s _curr_data;
    CCUData &_ccu_data;

    
};

using ACUInterfaceInstance = etl::singleton<ACUInterface>;

#endif