/* Libraries */
#include <Arduino.h>
#include <QNEthernet.h>
#include "MainChargeSystem.h"
/* Parameters */
bool charge_enable = false;

/* Systems */
namespace qn = qindesign::network; //setup of qn namespace
qn::EthernetUDP udp; //setup of qn namespace

/* Functions */


void setup() {
  //Serial.begin(115200); //I dont know if this is the baudrate I also don't know if this is even needed
  qn::Ethernet.begin(); //begins QNEthernet
  
}

void loop() {
}