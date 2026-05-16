#ifndef ACUINTERFACE_H
#define ACUINTERFACE_H

/* External Dependencies */
#include "hytech.h"
#include "FlexCAN_T4.h"
#include "SharedFirmwareTypes.h"
#include "etl/singleton.h"
#include <etl/delegate.h>
#include <array>
#include <etl/optional.h>

/* Local Interface Includes */
#include "CANInterface.h"

namespace default_acu_params
{
    constexpr size_t NUM_CHIPS = 12;
    constexpr size_t NUM_CELL_VOLTAGES_PER_CHIP = 12;
    constexpr size_t NUM_CELL_TEMPS_PER_CHIP = 4;
    constexpr size_t NUM_BOARD_TEMPS_PER_CHIP = 1;
    constexpr size_t NUM_DATA_PER_GROUP = 3;
}

struct ACUInterfaceData_s
{
    /* ACU Status Message */
    unsigned long last_recv_status_millis;
    ACUState_e acu_state;
    bool heartbeat_ok;

    /* BMS Voltages */
    volt average_voltage;
    volt low_voltage;
    volt high_voltage;
    volt pack_voltage;

    /* BMS Temps Data */
    celsius max_cell_temp;
    celsius min_cell_temp;
    celsius avg_cell_temp;
    celsius max_board_temp;

    /* BMS Detailed Data */
    std::array<std::array<etl::optional<volt>, default_acu_params::NUM_CELL_VOLTAGES_PER_CHIP>, default_acu_params::NUM_CHIPS> cell_voltages;
    std::array<std::array<etl::optional<celsius>, default_acu_params::NUM_CELL_TEMPS_PER_CHIP>, default_acu_params::NUM_CHIPS> cell_temps;
    std::array<etl::optional<celsius>, default_acu_params::NUM_CHIPS> board_temps;

    /* Elcon Charger Status */
    bool is_charging_enabled;
};

class ACUInterface
{
public:

    ACUInterface(unsigned long init_millis, unsigned long max_heartbeat_interval_ms) : _max_heartbeat_interval_ms(max_heartbeat_interval_ms)
    {
        _curr_data.last_recv_status_millis = 0;
        _curr_data.heartbeat_ok = false; // start out false
        _curr_data.acu_state = ACUState_e::STARTUP;
        _curr_data.average_voltage = 0;
        _curr_data.low_voltage = 0;
        _curr_data.high_voltage = 0;
        _curr_data.pack_voltage = 0;
        _curr_data.max_cell_temp = 0;
        _curr_data.min_cell_temp = 100;
        _curr_data.avg_cell_temp = 0;
        _curr_data.max_board_temp = 0;
    };

    /**
     *
     */
    bool is_acu_heartbeat_not_ok() {return !_curr_data.heartbeat_ok; }

    /**
     *
     */
    void reset_acu_heartbeat();

    /**
     *
     */
    void receive_status_message(const CAN_message_t& msg, unsigned long curr_millis);

    /**
     *
     */
    void receive_voltages_message(const CAN_message_t& msg, unsigned long curr_millis); //BMS_VOLTAGES and BMS_DETAILED_VOLTAGES

    /**
     * @brief handles packaging of detailed cell voltages message
    */
    void receive_detailed_voltages_message(const CAN_message_t& msg, unsigned long curr_millis);

    /**
     *
     */
    void receive_onboard_temps_message(const CAN_message_t& msg, unsigned long curr_millis);

    /**
     *
     */
    void receive_detailed_temps_message(const CAN_message_t& msg, unsigned long curr_millis);

    /**
     *
     */
    void receive_onboard_detailed_temps(const CAN_message_t& msg, unsigned long curr_millis);

    /**
     *
     */
    void set_is_charging_enabled(bool state);

    /**
     *
     */
    void enqueue_ccu_status_data();

    ACUInterfaceData_s get_latest_data() { return _curr_data; };

private:

    unsigned long _max_heartbeat_interval_ms;
    bool _first_received_message_heartbeat_init = false;

    ACUInterfaceData_s _curr_data;
};

using ACUInterfaceInstance = etl::singleton<ACUInterface>;

#endif /* ACUINTERFACE_H */