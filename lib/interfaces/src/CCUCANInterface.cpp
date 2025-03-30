#include "CCUCANInterface.h"

#include <cstdint>




CCUParams chargeParams;

CANRXBufferType CAN1_rxBuffer;
CANTXBufferType CAN1_txBuffer;




void CCUCANInterface::send_charge_control_message(float max_charging_current)
{
    uint16_t scaled_charging_current = static_cast<uint16_t>(max_charging_current * CCUCANInterface::CHARGERSCALINGFACTOR);
    uint16_t scaled_maximum_voltage = static_cast<uint16_t>(chargeParams.target_voltage_per_cell * CCUCANInterface::NUMCELLS * CCUCANInterface::CHARGERSCALINGFACTOR);

    CHARGER_CONTROL_t msg;
    
    if (max_charging_current != 0)
    {
        msg.max_charging_voltage_high = static_cast<uint8_t>(scaled_maximum_voltage >>8); //NOLINT takes the most significant byte
        msg.max_charging_voltage_low = static_cast<uint8_t>(scaled_maximum_voltage & 0xFF); //NOLINT takes the least significant byte
        msg.max_charging_current_high = static_cast<uint8_t>(scaled_charging_current >>8); //NOLINT takes the most significant byte
        msg.max_charging_current_low = static_cast<uint8_t>(scaled_charging_current & 0xFF); //NOLINT takes the least significant byte
        msg.control = (0); //NOLINT enables the charger 
    }
    else
    {
        msg.max_charging_voltage_high = static_cast<uint8_t>(0); //NOLINT ensures we are not charging
        msg.max_charging_voltage_low = static_cast<uint8_t>(0); //NOLINT ensures we are not charging
        msg.max_charging_current_high = static_cast<uint8_t>(0); //NOLINT ensures we are not charging
        msg.max_charging_current_low = static_cast<uint8_t>(0); //NOLINT ensures we are not charging
        msg.control = (1); //NOLINT turns charging off
    }
    CAN_util::enqueue_msg(&msg, &Pack_CHARGER_CONTROL_hytech, CCUCANInterface::CAN1_txBuffer);
}