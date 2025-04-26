#include "CCUCANInterfaceImpl.h"

#include <cstdint>

 
namespace CCUCANInterfaceImpl {

/* RX buffers */
CANRXBufferType charger_can_rx_buffer;
CANRXBufferType acu_can_rx_buffer;

/* TX buffers */
CANTXBufferType charger_can_tx_buffer;
CANTXBufferType acu_can_tx_buffer;

void on_acu_can_receive(const CAN_message_t &msg) {
    //Serial.println("recvd ACU");
    uint8_t buf[sizeof(CAN_message_t)];
    memmove(buf, &msg, sizeof(msg)); // NOLINT (decay of array to pointer)
    acu_can_rx_buffer.push_back(buf, sizeof(CAN_message_t));
    // Serial.println(" acu msg recvd");
    // Serial.print("MB: "); Serial.print(msg.mb);
   //  Serial.print("  ID: 0x"); Serial.print(msg.id, HEX);
    // Serial.print("  EXT: "); Serial.print(msg.flags.extended);
    // Serial.print("  LEN: "); Serial.print(msg.len);
    // Serial.print(" DATA: ");
    // for ( uint8_t i = 0; i < 8; i++ ) {
    //     Serial.print(msg.buf[i]); Serial.print(" ");
    // }
    // Serial.print("  TS: "); Serial.println(msg.timestamp);  
}

void on_charger_can_receive(const CAN_message_t &msg) {
    //Serial.println("recvd charger");
    uint8_t buf[sizeof(CAN_message_t)];
    memmove(buf, &msg, sizeof(msg)); // NOLINT (decay of array to pointer)
    charger_can_rx_buffer.push_back(buf, sizeof(CAN_message_t));
    // Serial.println(" charger msg recvd");
    // Serial.print("MB: "); Serial.print(msg.mb);
    // Serial.print("  ID: 0x"); Serial.print(msg.id, HEX);
    // Serial.print("  EXT: "); Serial.print(msg.flags.extended);
    // Serial.print("  LEN: "); Serial.print(msg.len);
    // Serial.print(" DATA: ");
    // for ( uint8_t i = 0; i < 8; i++ ) {
    //     Serial.print(msg.buf[i]); Serial.print(" ");
    // }
    // Serial.print("  TS: "); Serial.println(msg.timestamp); 
}

void ccu_CAN_recv(CANInterfaces &interfaces, const CAN_message_t &msg, unsigned long millis) {
    //Serial.println("can recv");
    switch (msg.id) {
    
    case BMS_VOLTAGES_CANID: 
    {
        interfaces.acu_interface.receive_voltages_message(msg, millis);
        break;
    }
    case BMS_STATUS_CANID:
    {
        interfaces.acu_interface.receive_status_message(msg, millis);
        break;
    }
    case CHARGER_DATA_CANID:
    {
        interfaces.charger_interface.receive_charger_data_message(msg, millis);
        break;
    }
    
    default:
    {
        break;
    }

    }
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

} // namespace CCUCANInterfaceImpl
