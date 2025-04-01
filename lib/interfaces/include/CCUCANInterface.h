#ifndef CCUCANINTERFACE_H
#define CCUCANINTERFACE_H

#include "hytech.h"
#include "CANInterface.h"
#include "CCUParams.h"


using CANRXBufferType = Circular_Buffer<uint8_t, (uint32_t)16, sizeof(CAN_message_t)>;
using CANTXBufferType = Circular_Buffer<uint8_t, (uint32_t)128, sizeof(CAN_message_t)>; 

namespace CCUCANInterface
{
        const float CHARGERSCALINGFACTOR = 10;
        const float NUMCELLS = 126;

        extern CANRXBufferType CAN1_rxBuffer;
        extern CANTXBufferType CAN1_txBuffer;

        extern FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> CCU_CAN;

        void enqueue_charge_control_message(float max_charging_current);
        void enqueue_ccu_status_to_acu_message(float max_charging_current);
}

#endif