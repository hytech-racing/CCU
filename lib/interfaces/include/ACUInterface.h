#ifndef ACUINTERFACE_H
#define ACUINTERFACE_H

#include "FlexCAN_T4.h"
#include "hytech.h"
#include "SharedFirmwareTypes.h"
#include "etl/singleton.h"
#include <etl/delegate.h>
#include "CANInterface.h"
#include "CCUData.h"

struct ACUInterfaceData_s 
{
    unsigned long last_recv_status_millis;
    uint16_t acu_state;
    volt average_voltage;
    volt low_voltage;
    volt high_voltage;
    volt total_voltage;
    bool heartbeat_ok;
};

class ACUInterface
{
public:

    ACUInterface(unsigned long init_millis, unsigned long max_heartbeat_interval_ms, CCUData &ccu_data) : _max_heartbeat_interval_ms(max_heartbeat_interval_ms), _ccu_data(ccu_data)
    {
        _curr_data.last_recv_status_millis = 0;
        _curr_data.heartbeat_ok = false; // start out false
        _curr_data.acu_state = 0;
        _curr_data.average_voltage = 0;
        _curr_data.low_voltage = 0;
        _curr_data.high_voltage = 0;
        _curr_data.total_voltage = 0;
    };

    bool is_acu_heartbeat_not_ok() {return !_curr_data.heartbeat_ok; }
    void reset_acu_heartbeat();
    
    void receive_status_message(const CAN_message_t& msg, unsigned long curr_millis);
    void receive_voltages_message(const CAN_message_t& msg, unsigned long curr_millis);
    void recieve_voltages_b_message(const CAN_message_t& msg, unsigned long curr_millis); //BMS detailed voltages - not sure what I do with this data
    
    ACUInterfaceData_s get_latest_data() {return _curr_data;};

    void enqueue_ccu_status_data();

private:

    ACUInterfaceData_s _curr_data;
    CCUData &_ccu_data;

    unsigned long _max_heartbeat_interval_ms;
    bool _first_received_message_heartbeat_init = false;
    
};

using ACUInterfaceInstance = etl::singleton<ACUInterface>;

#endif /* ACUINTERFACE_H */