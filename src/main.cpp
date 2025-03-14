/* Libraries */
#include <Arduino.h>
#include <QNEthernet.h>
#include "MainChargeSystem.h"
#include "shared_firmware_types.h"
#include "CCUParams.h"
#include "ht_sched.hpp"

/* Parameters */
ACUAllData_s acu_all_data;
CCUParams ccu_params; 

/* Systems */
namespace qn = qindesign::network; //setup of qn namespace
qn::EthernetUDP udp; //setup of qn namespace

HT_SCHED::Scheduler& scheduler = HT_SCHED::Scheduler::getInstance(); //initializing HTScheduler

/* Functions */
void setup() {
  //Serial.begin(115200); //I dont know if this is the baudrate I also don't know if this is even needed
  qn::Ethernet.begin(); //begins QNEthernet
  
}

void loop() {
  scheduler.run();
}