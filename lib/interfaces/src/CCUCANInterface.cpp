#include "CCUCANInterface.h"
#include "CCUCANBuffers.h"

#include <cstdint>

// Include concrete interface definitions for method calls in ccu_CAN_recv
#include "ACUInterface.h"
#include "ChargerInterface.h"
#include "EMInterface.h"

namespace CCUCANInterface {

/* RX buffers */
CANRXBufferType charger_can_rx_buffer;
CANRXBufferType acu_can_rx_buffer;

/* TX buffers */
CANTXBufferType charger_can_tx_buffer;
CANTXBufferType acu_can_tx_buffer;

void on_acu_can_receive(const CAN_message_t &msg) {
    uint8_t buf[sizeof(CAN_message_t)];
    memmove(buf, &msg, sizeof(msg)); // NOLINT (decay of array to pointer)
    acu_can_rx_buffer.push_back(buf, sizeof(CAN_message_t));
}

void on_charger_can_receive(const CAN_message_t &msg) {
    uint8_t buf[sizeof(CAN_message_t)];
    memmove(buf, &msg, sizeof(msg)); // NOLINT (decay of array to pointer)
    charger_can_rx_buffer.push_back(buf, sizeof(CAN_message_t));
}


void send_all_CAN_msgs(CANTXBufferType &buffer, FlexCAN_T4_Base *can_interface) {
    CAN_message_t msg;
    while (buffer.available()) {
        CAN_message_t msg;
        uint8_t buf[sizeof(CAN_message_t)];
        buffer.pop_front(buf, sizeof(CAN_message_t));
        memmove(&msg, buf, sizeof(msg)); // NOLINT (decay of array to pointer)
        can_interface->write(msg);
    } 
}

} // namespace CCUCANInterface
