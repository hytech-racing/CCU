#include "ChargerInterface.h"
#include "CCUCANInterfaceImpl.h"

extern struct CCUParams ccu_params;

void ChargerInterface::receive_charger_data_message(const CAN_message_t& msg, unsigned long curr_millis) {
    CHARGER_DATA_t charger_data_msg;
    charger_data charger_data;
    Unpack_CHARGER_DATA_hytech(&charger_data_msg, &msg.buf[0], msg.len);
    charger_data.output_dc_voltage_high = charger_data_msg.output_dc_voltage_high;
    charger_data.output_dc_voltage_low = charger_data_msg.output_dc_voltage_low;
    charger_data.output_current_high = charger_data_msg.output_current_high;
    charger_data.output_current_low = charger_data_msg.output_current_low;
    charger_data.flags = charger_data_msg.flags;
    charger_data.input_ac_voltage_high = charger_data_msg.input_ac_voltage_high;
    charger_data.input_ac_voltage_low = charger_data_msg.input_ac_voltage_low;
}

void ChargerInterface::enqueue_charging_data()
{
    // Charging voltage is in units of 100mV
    // So, we want 530V to be max charge voltage
    // We want the high/low bytes of the 16-bit int to be 5300 (decimal), which is 0x14B4 (hex)

    // NOTE: The "high" and "low" values are not max and min-- rather, they are the "high" and "low"
    // bytes of a 16-bit integer.
    CHARGER_CONTROL_t charger_control = {};
    charger_control.max_charging_voltage_high = 0x14; //NOLINT (see comment)
    charger_control.max_charging_voltage_low = 0xB4; //NOLINT (see comment)
    charger_control.max_charging_current_high = MainChargeSystem::calculate_charge_current(ccu_params.target_voltage_per_cell); //charging current reads from function
    charger_control.max_charging_current_low = 0; 
    CAN_util::enqueue_msg(&charger_control, &Pack_CHARGER_CONTROL_hytech, CCUCANInterfaceImpl::charger_can_tx_buffer);
}
