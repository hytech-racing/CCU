#include "ACUInterface.h"

#include "CCUCANInterfaceImpl.h"

extern struct CCUParams ccu_params;

void ACUInterface::reset_acu_heartbeat()
{
    _curr_data.heartbeat_ok = true;
}

void ACUInterface::receive_status_message(const CAN_message_t &msg, unsigned long curr_millis) {
    BMS_STATUS_t bms_status_msg;
    Unpack_BMS_STATUS_hytech(&bms_status_msg, &msg.buf[0], msg.len);
    _curr_data.acu_state = bms_status_msg.state;

    // As long as we're using millis() function, loop overrun not a concern
    
    if(_curr_data.last_recv_status_millis == 0)
    {
        _first_received_message_heartbeat_init = true;
    }
    
    _curr_data.last_recv_status_millis = curr_millis;
}

void ACUInterface::receive_voltages_message(const CAN_message_t& msg, unsigned long curr_millis)
{
    BMS_VOLTAGES_t voltages_msg;
    Unpack_BMS_VOLTAGES_hytech(&voltages_msg, &msg.buf[0], msg.len);
    _curr_data.average_voltage = HYTECH_average_voltage_ro_fromS(static_cast<float>(voltages_msg.average_voltage_ro));
    _curr_data.low_voltage = HYTECH_low_voltage_ro_fromS(static_cast<float>(voltages_msg.low_voltage_ro));
    _curr_data.high_voltage = HYTECH_high_voltage_ro_fromS(static_cast<float>(voltages_msg.high_voltage_ro));
    _curr_data.total_voltage = HYTECH_total_voltage_ro_fromS(static_cast<float>(voltages_msg.total_voltage_ro));
}

void ACUInterface::enqueue_ccu_status_data()
{
    CCU_STATUS_t ccu_status = {};
    ccu_status.charger_enabled = ccu_params.balancing_enabled; // Treat this as a balancing_enabled boolean
    CAN_util::enqueue_msg(&ccu_status, &Pack_CCU_STATUS_hytech, CCUCANInterfaceImpl::acu_can_tx_buffer);
}
