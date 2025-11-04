#include "ACUInterface.h"

#include "CCUCANBuffers.h"
#include "hytech.h"

template<size_t num_cells, size_t num_celltemps, size_t num_chips>
void ACUInterface<num_cells, num_celltemps, num_chips>::reset_acu_heartbeat()
{
    _curr_data.heartbeat_ok = true;
}

template<size_t num_cells, size_t num_celltemps, size_t num_chips>
void ACUInterface<num_cells, num_celltemps, num_chips>::receive_status_message(const CAN_message_t &msg, unsigned long curr_millis) {
    BMS_STATUS_t bms_status_msg;
    Unpack_BMS_STATUS_hytech(&bms_status_msg, &msg.buf[0], msg.len);
    _curr_data.bms_charging_state = bms_status_msg.charging_state;

    // As long as we're using millis() function, loop overrun not a concern
    
    if(_curr_data.last_recv_status_millis == 0)
    {
        _first_received_message_heartbeat_init = true;
    }
    
    _curr_data.last_recv_status_millis = curr_millis;
    
}

template<size_t num_cells, size_t num_celltemps, size_t num_chips>
void ACUInterface<num_cells, num_celltemps, num_chips>::receive_voltage_statistics_message(const CAN_message_t& msg, unsigned long curr_millis)
{
    BMS_VOLTAGES_t voltages_msg;
    Unpack_BMS_VOLTAGES_hytech(&voltages_msg, &msg.buf[0], msg.len);
    _curr_data.average_voltage = HYTECH_average_voltage_ro_fromS(static_cast<float>(voltages_msg.average_voltage_ro));
    _curr_data.min_cell_voltage = HYTECH_min_cell_voltage_ro_fromS(static_cast<float>(voltages_msg.min_cell_voltage_ro));
    _curr_data.max_cell_voltage = HYTECH_max_cell_voltage_ro_fromS(static_cast<float>(voltages_msg.max_cell_voltage_ro));
    _curr_data.total_voltage = HYTECH_total_voltage_ro_fromS(static_cast<float>(voltages_msg.total_voltage_ro));

}

template<size_t num_cells, size_t num_celltemps, size_t num_chips>
void ACUInterface<num_cells, num_celltemps, num_chips>::receive_temp_statistics_message(const CAN_message_t& msg, unsigned long curr_millis) 
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

template<size_t num_cells, size_t num_celltemps, size_t num_chips>
void ACUInterface<num_cells, num_celltemps, num_chips>::receive_cell_group_temps_message(const CAN_message_t& msg, unsigned long curr_millis)
{
    BMS_CHIP_TEMPS_t chip_temps{};
    Unpack_BMS_CHIP_TEMPS_hytech(&chip_temps, &msg.buf[0], msg.len);
    size_t chip_id = chip_temps.chip_id;
    size_t group_id = chip_temps.thermistor_group_id;

    size_t chip_start_index, group_start_index, temps_per_chip;
    temps_per_chip = _acu_params.temp_cell_groups_per_ic * _acu_params.temp_cells_per_group;
    chip_start_index = chip_id * temps_per_chip;
    group_start_index = chip_start_index + group_id * _acu_params.temp_cells_per_group;

    _curr_data.cell_group_temps[group_start_index] = HYTECH_thermistor_cell_group_temp_0_ro_fromS(static_cast<float>(chip_temps.thermistor_cell_group_temp_0_ro));
    _curr_data.cell_group_temps[group_start_index + 1] = HYTECH_thermistor_cell_group_temp_1_ro_fromS(static_cast<float>(chip_temps.thermistor_cell_group_temp_1_ro));

}

template<size_t num_cells, size_t num_celltemps, size_t num_chips>
void ACUInterface<num_cells, num_celltemps, num_chips>::receive_board_temps(const CAN_message_t& msg, unsigned long curr_millis)
{
    BMS_ONBOARD_CURRENT_TEMP_t onboard_current_temps{};
    Unpack_BMS_ONBOARD_CURRENT_TEMP_hytech(&onboard_current_temps, &msg.buf[0], msg.len);
    _curr_data.board_temps[onboard_current_temps.chip_id] = HYTECH_temp_0_ro_fromS(static_cast<float>(onboard_current_temps.temp_0_ro));
}

template<size_t num_cells, size_t num_celltemps, size_t num_chips>
void ACUInterface<num_cells, num_celltemps, num_chips>::enqueue_ccu_status_data()
{
    CCU_STATUS_t ccu_status = {};
    ccu_status.charger_enabled = _ccu_data.balancing_enabled; // Treat this as a balancing_enabled boolean
    CAN_util::enqueue_msg(&ccu_status, &Pack_CCU_STATUS_hytech, CCUCANInterface::acu_can_tx_buffer);
}
template<size_t num_cells, size_t num_celltemps, size_t num_chips>
void ACUInterface<num_cells, num_celltemps, num_chips>::receive_cell_voltages(const CAN_message_t& msg, unsigned long curr_millis)
{
    BMS_CELL_VOLTAGES_t cell_voltages_msg{};
    Unpack_BMS_CELL_VOLTAGES_hytech(&cell_voltages_msg, &msg.buf[0], msg.len);
    size_t chip_id = cell_voltages_msg.chip_id;
    size_t group_id = cell_voltages_msg.cell_group_id;
    size_t chip_start_index, group_start_index, voltages_per_chip_pair;
    voltages_per_chip_pair = (_acu_params.voltage_cell_groups_per_ic_even + _acu_params.voltage_cell_groups_per_ic_odd) * _acu_params.voltage_cells_per_group;

    // Will be more clear once transitioned to hardcoded chip cell counts
    chip_start_index = (chip_id + 1 / 2) * voltages_per_chip_pair - (chip_id % 2 == 1 ? _acu_params.voltage_cell_groups_per_ic_odd * _acu_params.voltage_cells_per_group : 0);
    group_start_index = chip_start_index + group_id * _acu_params.voltage_cells_per_group;
    
    _curr_data.cell_voltages[group_start_index] = HYTECH_cell_group_voltage_0_ro_fromS(static_cast<float>(cell_voltages_msg.cell_group_voltage_0_ro));
    _curr_data.cell_voltages[group_start_index + 1] = HYTECH_cell_group_voltage_1_ro_fromS(static_cast<float>(cell_voltages_msg.cell_group_voltage_1_ro));
    _curr_data.cell_voltages[group_start_index + 2] = HYTECH_cell_group_voltage_2_ro_fromS(static_cast<float>(cell_voltages_msg.cell_group_voltage_2_ro));
}