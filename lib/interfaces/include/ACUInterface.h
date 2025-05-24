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
    /* ACU Status Message */
    unsigned long last_recv_status_millis;
    uint16_t acu_state;
    bool heartbeat_ok;

    /* BMS Voltages */
    volt average_voltage;
    volt low_voltage;
    volt high_voltage;
    volt total_voltage;


    /* BMS Onboard Temps Data */
    celsius max_board_temp;


    /* BMS Onboard Detailed Temps Data */
    int ic_id;
    float temp_0;
    float temp_1;

    /* BMS Detailed Temps Data */
    int group_id;
    int ic_detailed_id;
    celsius therm_id_0;
    celsius therm_id_1;
    celsius therm_id_2;

    celsius min_cell_temp;
    celsius max_cell_temp;


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
        
        _curr_data.max_board_temp = 0;

        _curr_data.ic_id = 0;
        _curr_data.temp_0 = 0;
        _curr_data.temp_1 = 0;

        _curr_data.group_id = 0;
        _curr_data.ic_detailed_id = 0;
        _curr_data.therm_id_0 = 0;
        _curr_data.therm_id_1 = 0;
        _curr_data.therm_id_2 = 0;

        _curr_data.max_cell_temp = 0;
        _curr_data.min_cell_temp = 100;
    };

    bool is_acu_heartbeat_not_ok() {return !_curr_data.heartbeat_ok; }
    void reset_acu_heartbeat();
    
    void receive_status_message(const CAN_message_t& msg, unsigned long curr_millis);
    void receive_voltages_message(const CAN_message_t& msg, unsigned long curr_millis); //BMS_VOLTAGES and BMS_DETAILED_VOLTAGES
    void receive_temps_message(const CAN_message_t& msg, unsigned long curr_millis);
    
    
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