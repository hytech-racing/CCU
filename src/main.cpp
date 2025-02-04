/* Libraries */
#include <Arduino.h>
#include "MainCharge_sys.h"
#include <QNEthernet.h>

/* Parameters */
bool charge_enable = false;

/* Systems */
namespace qn = qindesign::network; //setup of qn namespace
qn::EthernetUDP udp; //setup of qn namespace

/* Functions */
void configure_charging();

void setup() {
  //Serial.begin(115200); //I dont know if this is the baudrate I also don't know if this is even needed
  qn::Ethernet.begin(); //begins QNEthernet
}

void loop() {
  charge_cycle();
}