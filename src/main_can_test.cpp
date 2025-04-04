#include <Arduino.h>

#include "CCUCANInterfaceImpl.h"

FlexCAN_T4<CAN1> MAIN_CAN;

void on_recv(const CAN_message_t &msg)
{
    Serial.println("msg recvd");
    Serial.print("MB: "); Serial.print(msg.mb);
    Serial.print("  ID: 0x"); Serial.print(msg.id, HEX);
    Serial.print("  EXT: "); Serial.print(msg.flags.extended);
    Serial.print("  LEN: "); Serial.print(msg.len);
    Serial.print(" DATA: ");
    for ( uint8_t i = 0; i < 8; i++ ) {
      Serial.print(msg.buf[i]); Serial.print(" ");
    }
    Serial.print("  TS: "); Serial.println(msg.timestamp);
  }
    

void setup()
{
    Serial.begin(115200);
    handle_CAN_setup(MAIN_CAN, 500000, &on_recv);
    
}

void loop()
{
    delay(100);
    CAN_message_t test_msg;
    test_msg.id = 0xdd;
    test_msg.len = 1;
    test_msg.buf[0] = 0x45;
    MAIN_CAN.write(test_msg);
}