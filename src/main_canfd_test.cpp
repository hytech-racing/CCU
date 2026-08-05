#include <Arduino.h>

#include "CANInterface.h"
#include "fd_test.h"

FlexCAN_T4FD<CAN3> CAN;

const uint32_t MSG_ID = 0x15;
const uint8_t MSG_DATA = 0x45;

const uint32_t DELAY = 10;

void on_recv(const CANFD_message_t &msg)
{
    Serial.println("msg recvd");
    Serial.print("MB: "); Serial.print(msg.mb);
    Serial.print("  ID: 0x"); Serial.print(msg.id, HEX);
    Serial.print("  EDL: "); Serial.print(msg.edl);
    Serial.print("  BRS: "); Serial.print(msg.brs);
    Serial.print("  EXT: "); Serial.print(msg.flags.extended);
    Serial.print("  LEN: "); Serial.print(msg.len);
    Serial.print(" DATA: ");
    for ( uint8_t i = 0; i < 8; i++ ) {
      Serial.print(msg.buf[i]); Serial.print(" ");
    }
    Serial.print("  TS: "); Serial.println(msg.timestamp);

    // struct fd_test_fd_test_t m;
    // if (fd_test_fd_test_unpack(&m, msg.buf, msg.len) == 0) {
    //     Serial.printf("cnt=%lu b8=%08lX b32=%08lX b60=%08lX\n",
    //         m.fd_test_counter, m.fd_test_byte32,
    //         m.fd_test_byte32, m.fd_test_byte60);
    // }
}

void setup()
{
    CAN.begin();
    CAN.setRegions(64);
    
    CANFD_timings_t t;
    t.baudrate = 1000000;
    t.baudrateFD = 2000000;
    t.propdelay = 190;
    t.bus_length = 1;
    t.sample = 75;
    t.clock = CLK_24MHz;

    CAN.setBaudRate(t);
    CAN.enableMBInterrupts();
    CAN.onReceive(on_recv);
}

void loop()
{
    CAN.events();
    delay(DELAY);
    CANFD_message_t test_msg;
    test_msg.id = MSG_ID;
    test_msg.len = 64;
    test_msg.edl = 1;
    test_msg.brs = 1;
    for ( uint8_t i = 0; i < 64; i++ ) {
      test_msg.buf[i] = MSG_DATA;
    }
    CAN.write(test_msg);


    // struct fd_test_fd_test_t m = {};
    // static uint32_t counter = 0;
    // m.fd_test_counter = counter++;
    // m.fd_test_byte8  = 0xDEADBEEF;
    // m.fd_test_byte32 = 0xCAFEBABE;
    // m.fd_test_byte60 = 0x12345678;

    // CANFD_message_t test_msg;
    // test_msg.id  = 0x7F2;
    // test_msg.len = 64;
    // test_msg.edl = 1;
    // test_msg.brs = 1;
    // fd_test_fd_test_pack(test_msg.buf, &m, sizeof(test_msg.buf));
    // CAN.write(test_msg);
}
