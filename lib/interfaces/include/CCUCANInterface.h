#ifndef CCUCANINTERFACE_H
#define CCUCANINTERFACE_H

#include "hytech.h"
#include "CANInterface.h"



using CANRXBufferType = Circular_Buffer<uint8_t, (uint32_t)16, sizeof(CAN_message_t)>;
using CANTXBufferType = Circular_Buffer<uint8_t, (uint32_t)128, sizeof(CAN_message_t)>;

namespace CCUCANInterface{

        extern CANRXBufferType CAN1_rxBuffer;
        extern CANTXBufferType CAN1_txBuffer;
        void send_charge_control_message(FlexCAN_T4_Base *can_interface, uint16_t max_charging_current);
}
