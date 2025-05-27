#include "ACUInterface.h"

#include "CCUCANInterfaceImpl.h"



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

void ACUInterface::receive_temps_message(const CAN_message_t& msg, unsigned long curr_millis) 
{
    BMS_ONBOARD_TEMPS_t board_temps{};
    Unpack_BMS_ONBOARD_TEMPS_hytech(&board_temps, &msg.buf[0], msg.len);
    _curr_data.max_board_temp = HYTECH_high_temp_ro_fromS(static_cast<float>(board_temps.high_temp_ro)); //Only being sent the max board temp
    _ccu_data.max_board_temp = _curr_data.max_board_temp;
    

    BMS_DETAILED_TEMPS_t detailed_temps{};
    Unpack_BMS_DETAILED_TEMPS_hytech(&detailed_temps, &msg.buf[0], msg.len);
    _curr_data.group_id = detailed_temps.group_id; //size of uint8_t
    _curr_data.ic_detailed_id = detailed_temps.ic_id; //size of uint8_t
    _curr_data.therm_id_0 = HYTECH_thermistor_id_0_ro_fromS(static_cast<float>(detailed_temps.thermistor_id_0_ro));
    _curr_data.therm_id_1 = HYTECH_thermistor_id_1_ro_fromS(static_cast<float>(detailed_temps.thermistor_id_1_ro));
    _curr_data.therm_id_2 = HYTECH_thermistor_id_2_ro_fromS(static_cast<float>(detailed_temps.thermistor_id_2_ro));

    
    /* For every cell temp (only data from three thermistors) */
    // uint8_t ic = _curr_data.ic_detailed_id; //will update based on the ic_id that is sent in the CAN message

    // for (int therm = 0; therm < 4; therm++) { //no data for thermistor_id_3
    //     switch (therm) {
    //         case 0: _curr_data.bms_detailed_temps[ic][therm] = _curr_data.therm_id_0; break;
    //         case 1: _curr_data.bms_detailed_temps[ic][therm] = _curr_data.therm_id_1; break;
    //         case 2: _curr_data.bms_detailed_temps[ic][therm] = _curr_data.therm_id_2; break;
    //         case 3: _curr_data.bms_detailed_temps[ic][therm] = 0; break; 
    //         default: _curr_data.bms_detailed_temps[ic][therm] = 0;
    //     };

    //     /* Checking for min and max cell temps */
    //     _curr_data.current_temp = static_cast<celsius>(_curr_data.bms_detailed_temps[ic][therm]); 
    //     if (_curr_data.current_temp > _ccu_data.max_cell_temp) {
    //         _ccu_data.max_cell_temp = _curr_data.current_temp;
    //     }
    //     if (_curr_data.current_temp < _ccu_data.min_cell_temp) {
    //         _ccu_data.min_cell_temp = _curr_data.current_temp;
    //     }
    // }


   float thermistor_temps[3] = {_curr_data.therm_id_0, _curr_data.therm_id_1, _curr_data.therm_id_2};
    for (auto temp : thermistor_temps) { //NOLINT (size of thermistor temps will not change)
        if (temp > _ccu_data.max_cell_temp) {
            _curr_data.max_cell_temp = temp;
        }
        if (temp < _ccu_data.min_cell_temp) {
            _curr_data.min_cell_temp = temp;
        }
    }


    BMS_ONBOARD_DETAILED_TEMPS_t onboard_detailed_temps{};
    Unpack_BMS_ONBOARD_DETAILED_TEMPS_hytech(&onboard_detailed_temps, &msg.buf[0], msg.len);
    _curr_data.ic_id = onboard_detailed_temps.ic_id;
    _curr_data.temp_0 = HYTECH_temp_0_ro_fromS(static_cast<float>(onboard_detailed_temps.temp_0_ro));
    _curr_data.temp_1 = HYTECH_temp_1_ro_fromS(static_cast<float>(onboard_detailed_temps.temp_1_ro));


}

void ACUInterface::enqueue_ccu_status_data()
{
    CCU_STATUS_t ccu_status = {};
    ccu_status.charger_enabled = _ccu_data.balancing_enabled; // Treat this as a balancing_enabled boolean
    CAN_util::enqueue_msg(&ccu_status, &Pack_CCU_STATUS_hytech, CCUCANInterfaceImpl::acu_can_tx_buffer);
}
