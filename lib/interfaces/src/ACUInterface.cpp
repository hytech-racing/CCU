#include "ACUInterface.h"

#include "CCUCANBuffers.h"
#include "hytech.h"

void ACUInterface::reset_acu_heartbeat()
{
    _curr_data.heartbeat_ok = true;
}

void ACUInterface::receive_status_message(const CAN_message_t &msg, unsigned long curr_millis) {
    BMS_STATUS_t bms_status_msg;
    Unpack_BMS_STATUS_hytech(&bms_status_msg, &msg.buf[0], msg.len);
    _curr_data.acu_shdn_out_voltage_high = bms_status_msg.shdn_out_voltage_state;

    // As long as we're using millis() function, loop overrun not a concern
    
    if(_curr_data.last_recv_status_millis == 0)
    {
        _first_received_message_heartbeat_init = true;
    }
    
    _curr_data.last_recv_status_millis = curr_millis;
    
}


void ACUInterface::receive_voltage_statistics_message(const CAN_message_t& msg, unsigned long curr_millis)
{
    BMS_VOLTAGES_t voltages_msg;
    Unpack_BMS_VOLTAGES_hytech(&voltages_msg, &msg.buf[0], msg.len);
    _curr_data.average_voltage = HYTECH_average_voltage_ro_fromS(static_cast<float>(voltages_msg.average_voltage_ro));
    _curr_data.min_cell_voltage = HYTECH_min_cell_voltage_ro_fromS(static_cast<float>(voltages_msg.min_cell_voltage_ro));
    _curr_data.max_cell_voltage = HYTECH_max_cell_voltage_ro_fromS(static_cast<float>(voltages_msg.max_cell_voltage_ro));
    _curr_data.total_voltage = HYTECH_total_voltage_ro_fromS(static_cast<float>(voltages_msg.total_voltage_ro));

}


void ACUInterface::receive_temp_statistics_message(const CAN_message_t& msg, unsigned long curr_millis) 
{
    BMS_ONBOARD_TEMPS_t board_temps = {};
    Unpack_BMS_ONBOARD_TEMPS_hytech(&board_temps, &msg.buf[0], msg.len);
    _curr_data.max_board_temp = HYTECH_max_board_temp_ro_fromS(board_temps.max_board_temp_ro);
    _curr_data.min_cell_temp = HYTECH_min_cell_temp_ro_fromS(board_temps.min_cell_temp_ro);
    _curr_data.max_cell_temp = HYTECH_max_cell_temp_ro_fromS(board_temps.max_cell_temp_ro);
    

    _ccu_data.max_board_temp = _curr_data.max_board_temp;
    _ccu_data.min_cell_temp = _curr_data.min_cell_temp;
    _ccu_data.max_cell_temp = _curr_data.max_cell_temp;
}


void ACUInterface::receive_cell_group_temps_message(const CAN_message_t& msg, unsigned long curr_millis)
{
    BMS_CHIP_TEMPS_t chip_temps{};
    Unpack_BMS_CHIP_TEMPS_hytech(&chip_temps, &msg.buf[0], msg.len);
    _curr_data.cell_group_temp_current_chip = chip_temps.chip_id;

    _curr_data.cell_group_temp_1 = HYTECH_thermistor_cell_group_temp_0_ro_fromS(static_cast<float>(chip_temps.thermistor_cell_group_temp_0_ro));
    _curr_data.cell_group_temp_2 = HYTECH_thermistor_cell_group_temp_1_ro_fromS(static_cast<float>(chip_temps.thermistor_cell_group_temp_1_ro));

}


void ACUInterface::receive_board_temps(const CAN_message_t& msg, unsigned long curr_millis)
{
    BMS_ONBOARD_CURRENT_TEMP_t onboard_current_temps{};
    Unpack_BMS_ONBOARD_CURRENT_TEMP_hytech(&onboard_current_temps, &msg.buf[0], msg.len);

    _curr_data.board_temp_current_chip = onboard_current_temps.chip_id;
    _curr_data.board_temp = HYTECH_temp_0_ro_fromS(static_cast<float>(onboard_current_temps.temp_0_ro));
}


void ACUInterface::enqueue_ccu_status_data()
{
    CCU_STATUS_t ccu_status = {};
    ccu_status.charger_enabled = _ccu_data.balancing_enabled; // Treat this as a balancing_enabled boolean
    CAN_util::enqueue_msg(&ccu_status, &Pack_CCU_STATUS_hytech, CCUCANInterface::acu_can_tx_buffer);
}

void ACUInterface::receive_cell_voltages(const CAN_message_t& msg, unsigned long curr_millis)
{
    BMS_CELL_VOLTAGES_t cell_voltages_msg{};
    Unpack_BMS_CELL_VOLTAGES_hytech(&cell_voltages_msg, &msg.buf[0], msg.len);

    _curr_data.cell_voltage_current_chip = cell_voltages_msg.chip_id;
    _curr_data.cell_voltage_1 = HYTECH_cell_group_voltage_0_ro_fromS(static_cast<float>(cell_voltages_msg.cell_group_voltage_0_ro));
    _curr_data.cell_voltage_2 = HYTECH_cell_group_voltage_1_ro_fromS(static_cast<float>(cell_voltages_msg.cell_group_voltage_1_ro));
    _curr_data.cell_voltage_3 = HYTECH_cell_group_voltage_2_ro_fromS(static_cast<float>(cell_voltages_msg.cell_group_voltage_2_ro));
}