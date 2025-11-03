#ifndef ACUINTERFACE_H
#define ACUINTERFACE_H

#include "FlexCAN_T4.h"
#include "hytech.h"
#include "SharedFirmwareTypes.h"
#include "etl/singleton.h"
#include <etl/delegate.h>
#include "CANInterface.h"
#include "CCUData.h"

namespace acu_interface_defaults {
    constexpr const size_t NUM_CELLS = 126;
    constexpr const size_t NUM_CELLTEMPS = 48;
    constexpr const size_t NUM_CHIPS = 12;
    constexpr const size_t VOLTAGE_CELLS_PER_GROUP = 3;
    constexpr const size_t VOLTAGE_CELL_GROUPS_PER_IC_EVEN = 4;
    constexpr const size_t VOLTAGE_CELL_GROUPS_PER_IC_ODD = 3;
    constexpr const size_t TEMP_CELL_GROUPS_PER_IC = 2;
    constexpr const size_t TEMP_CELLS_PER_GROUP = 2;
};

struct ACUInterfaceParams_s {
    size_t num_cells;
    size_t num_celltemps;
    size_t num_chips;
    size_t voltage_cell_groups_per_ic_even;
    size_t voltage_cell_groups_per_ic_odd;
    size_t temp_cell_groups_per_ic;
    size_t voltage_cells_per_group;
    size_t temp_cells_per_group;
};

struct ACUInterfaceData_s 
{
    /* ACU Status Message */
    unsigned long last_recv_status_millis;
    uint16_t acu_state;
    bool heartbeat_ok;

    /* BMS Voltages */
    volt average_voltage;
    volt min_cell_voltage;
    volt max_cell_voltage;
    volt total_voltage;

    /* BMS Cell Voltages Data */
    volt cell_voltages[126];

    /* BMS Cell Temps Message */
    celsius cell_group_temps[48];

    /* BMS Onboard Current Temps Message */
    celsius max_board_temp;
    celsius max_cell_temp;
    celsius min_cell_temp;

    /* BMS Board Current Temp */
    celsius board_temps[12];

};
class ACUInterface
{
public:

    ACUInterface(unsigned long init_millis, unsigned long max_heartbeat_interval_ms, CCUData &ccu_data, ACUInterfaceParams_s params = {
                    .num_cells = acu_interface_defaults::NUM_CELLS,
                    .num_celltemps = acu_interface_defaults::NUM_CELLTEMPS,
                    .num_chips = acu_interface_defaults::NUM_CHIPS,
                    .voltage_cell_groups_per_ic_even = acu_interface_defaults::VOLTAGE_CELL_GROUPS_PER_IC_EVEN,
                    .voltage_cell_groups_per_ic_odd = acu_interface_defaults::VOLTAGE_CELL_GROUPS_PER_IC_ODD,
                    .temp_cell_groups_per_ic = acu_interface_defaults::TEMP_CELL_GROUPS_PER_IC,
                    .voltage_cells_per_group = acu_interface_defaults::VOLTAGE_CELLS_PER_GROUP,
                    .temp_cells_per_group = acu_interface_defaults::TEMP_CELLS_PER_GROUP
                }) : _max_heartbeat_interval_ms(max_heartbeat_interval_ms), _ccu_data(ccu_data), _acu_params(params)
    {
        _curr_data.last_recv_status_millis = 0;
        _curr_data.heartbeat_ok = false; // start out false
        _curr_data.acu_state = 0;

        _curr_data.average_voltage = 0;
        _curr_data.min_cell_voltage = 0;
        _curr_data.max_cell_voltage = 0;    
        _curr_data.total_voltage = 0;

        for (size_t i = 0; i < 126; ++i)
        {
            _curr_data.cell_voltages[i] = 0;
        }

        for (size_t i = 0; i < 48; ++i)
        {
            _curr_data.cell_group_temps[i] = 0;
        }
        for (size_t i = 0; i < 12; ++i)
        {
            _curr_data.board_temps[i] = 0;
        }

        _curr_data.max_board_temp = 0;
        _curr_data.max_cell_temp = 0;
        _curr_data.min_cell_temp = 0;

    };


    bool is_acu_heartbeat_not_ok() {return !_curr_data.heartbeat_ok; }
    void reset_acu_heartbeat();
    
    void receive_status_message(const CAN_message_t& msg, unsigned long curr_millis);
    void receive_voltages_message(const CAN_message_t& msg, unsigned long curr_millis); //BMS_VOLTAGES and BMS_DETAILED_VOLTAGES
    void receive_onboard_temps_message(const CAN_message_t& msg, unsigned long curr_millis);
    void receive_current_temps_message(const CAN_message_t& msg, unsigned long curr_millis);
    void receive_cell_voltages(const CAN_message_t& msg, unsigned long curr_millis);
    void receive_onboard_current_temps(const CAN_message_t& msg, unsigned long curr_millis);
    
    
    ACUInterfaceData_s get_latest_data() {return _curr_data;};

    void enqueue_ccu_status_data();

private:
    ACUInterfaceParams_s _acu_params;
    ACUInterfaceData_s _curr_data;
    CCUData &_ccu_data;

    unsigned long _max_heartbeat_interval_ms;
    bool _first_received_message_heartbeat_init = false;
        
};
using ACUInterfaceInstance = etl::singleton<ACUInterface>;

#endif /* ACUINTERFACE_H */