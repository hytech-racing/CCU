#ifndef ACUINTERFACE_H
#define ACUINTERFACE_H

#include "FlexCAN_T4.h"
#include "hytech.h"
#include "SharedFirmwareTypes.h"
#include "etl/singleton.h"
#include <etl/delegate.h>
#include "CANInterface.h"
#include "ACUData.h"
#include "CCUData.h"


struct ACUInterfaceData_s 
{
    /* ACU Status Message */
    unsigned long last_recv_status_millis;
    bool acu_shdn_out_voltage_high;
    bool heartbeat_ok;

    /* BMS Voltages */
    volt average_voltage;
    volt min_cell_voltage;
    volt max_cell_voltage;
    volt total_voltage;

    /* BMS Onboard Current Temps Message */
    celsius max_board_temp;
    celsius max_cell_temp;
    celsius min_cell_temp;

    /* BMS Detailed Data for Comp */

    size_t cell_voltage_current_chip;
    volt cell_voltage_1;
    volt cell_voltage_2;
    volt cell_voltage_3;

    size_t cell_group_temp_current_chip;
    celsius cell_group_temp_1;
    celsius cell_group_temp_2;

    size_t board_temp_current_chip;
    celsius board_temp;

};

class ACUInterface
{
public:

    ACUInterface(unsigned long init_millis, unsigned long max_heartbeat_interval_ms, CCUData &ccu_data) : _max_heartbeat_interval_ms(max_heartbeat_interval_ms), _ccu_data(ccu_data)
    {
        _curr_data.last_recv_status_millis = 0;
        _curr_data.heartbeat_ok = false; // start out false
        _curr_data.acu_shdn_out_voltage_high = false;

        _curr_data.average_voltage = 0;
        _curr_data.min_cell_voltage = 0;
        _curr_data.max_cell_voltage = 0;    
        _curr_data.total_voltage = 0;

        _curr_data.max_board_temp = 0;
        _curr_data.max_cell_temp = 0;
        _curr_data.min_cell_temp = 0;

    };


    bool is_acu_heartbeat_not_ok() {return !_curr_data.heartbeat_ok; }
    void reset_acu_heartbeat();
    
    void receive_status_message(const CAN_message_t& msg, unsigned long curr_millis);
    void receive_voltage_statistics_message(const CAN_message_t& msg, unsigned long curr_millis); //BMS_VOLTAGES and BMS_DETAILED_VOLTAGES
    void receive_temp_statistics_message(const CAN_message_t& msg, unsigned long curr_millis);
    void receive_cell_group_temps_message(const CAN_message_t& msg, unsigned long curr_millis);
    void receive_cell_voltages(const CAN_message_t& msg, unsigned long curr_millis);
    void receive_board_temps(const CAN_message_t& msg, unsigned long curr_millis);


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