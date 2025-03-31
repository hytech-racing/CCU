#include "ChargerInterface.h"

void ChargerInterface::receive_charger_data_message(const CAN_message_t& msg, unsigned long curr_millis) {
    CHARGER_DATA_t charger_data_msg;
    Unpack_CHARGER_DATA_hytech(&charger_data_msg, &msg.buf[0], msg.len);
    _curr_data.output_dc_voltage_high = charger_data_msg.output_dc_voltage_high;
    _curr_data.output_dc_voltage_low = charger_data_msg.output_dc_voltage_low;
    _curr_data.output_current_high = charger_data_msg.output_current_high;
    _curr_data.output_current_low = charger_data_msg.output_current_low;
    _curr_data.flags = charger_data_msg.flags;
    _curr_data.input_ac_voltage_high = charger_data_msg.input_ac_voltage_high;
    _curr_data.input_ac_voltage_low = charger_data_msg.input_ac_voltage_low;
}
