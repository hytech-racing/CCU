#ifndef CCUCANBUFFERS_H
#define CCUCANBUFFERS_H

#include "FlexCAN_T4.h"

// Buffer type aliases for CAN RX/TX queues
using CANRXBufferType = Circular_Buffer<uint8_t, (uint32_t)16, sizeof(CAN_message_t)>;
using CANTXBufferType = Circular_Buffer<uint8_t, (uint32_t)128, sizeof(CAN_message_t)>;

// Extern declarations for shared CAN buffers
namespace CCUCANInterface {
    extern CANRXBufferType charger_can_rx_buffer;
    extern CANRXBufferType acu_can_rx_buffer;

    extern CANTXBufferType charger_can_tx_buffer;
    extern CANTXBufferType acu_can_tx_buffer;
}

#endif // CCUCANBUFFERS_H
