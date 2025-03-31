#ifndef ACUINTERFACE_H
#define ACUINTERFACE_H

#include "FlexCAN_T4.h"
#include "hytech.h"
#include "SharedFirmwareTypes.h"
#include "etl/singleton.h"

struct ACUInterfaceData_s
{
    unsigned long last_recv_status_millis;
    uint16_t acu_state;
    volt average_voltage;
    volt low_voltage;
    volt high_voltage;
    volt total_voltage;
    bool heartbeat_ok = false;
};

class ACUInterface {
public:

    ACUInterface() = delete;

    ACUInterface(unsigned long init_millis, unsigned long max_heartbeat_interval_ms) : _max_heartbeat_interval_ms(max_heartbeat_interval_ms)
    {
        _curr_data.last_recv_status_millis = 0;
        _curr_data.heartbeat_ok = false; // start out false
    };

    bool is_acu_heartbeat_not_ok() {return !_curr_data.heartbeat_ok; }
    void reset_acu_heartbeat();
    
    void receive_status_message(const CAN_message_t& msg, unsigned long curr_millis);
    void receive_voltages_message(const CAN_message_t& msg, unsigned long curr_millis);
    
    ACUInterfaceData_s get_latest_data() {return _curr_data;};

private:

    ACUInterfaceData_s _curr_data;

    unsigned long _max_heartbeat_interval_ms;
    bool _first_received_message_heartbeat_init = false;
    
};

using ACUInterfaceInstance = etl::singleton<ACUInterface>;

#endif /* ACUINTERFACE_H */