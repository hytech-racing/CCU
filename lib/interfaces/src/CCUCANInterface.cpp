#include "CCUCANInterface.h"

#include <cstdint>

CANRXBufferType CAN1_rxBuffer;
CANTXBufferType CAN1_txBuffer;


void CCUCANInterface::send_charge_control_message(FlexCAN_T4_Base *can_interface, uint16_t max_charging_current)
{
    uint16_t scaled_charging_current = static_cast<uint16_t>(max_charging_current *10);

    CHARGER_CONTROL_t msg;
    
    msg.max_charging_voltage_high = static_cast<uint8_t>(0x14);
    msg.max_charging_voltage_low = static_cast<uint8_t>(0xB4);
    msg.max_charging_current_high = static_cast<uint8_t>(scaled_charging_current >>8);
    msg.max_charging_current_low = static_cast<uint8_t>(scaled_charging_current & 0xFF);

    CAN_util::enqueue_msg(&msg, &Pack_CHARGER_CONTROL_hytech, CCUCANInterface::CAN1_txBuffer);
}