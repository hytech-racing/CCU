/* Libraries */
#include <Arduino.h>
#include <QNEthernet.h>
#include "MainChargeSystem.h"
#include "SharedFirmwareTypes.h"
#include "CCUParams.h"
#include "ht_sched.hpp"
#include "ht_task.hpp"
#include "ChargerStateMachine.h"

/* Parameters */
ACUAllData_s acu_all_data;
CCUParams ccu_params; 

/* Initialization of the charging state machine */
ChargerStateMachine state_machine;

/* Systems */
namespace qn = qindesign::network; //setup of qn namespace
qn::EthernetUDP udp; //setup of qn namespace


/* Scheduler Setup */
HT_SCHED::Scheduler& scheduler = HT_SCHED::Scheduler::getInstance(); 

/* Task Declarations 
HT_TASK::Task change_charging_state();
HT_TASK::Task update_display();
HT_TASK::Task read_dial();
HT_TASK::Task CAN_send();
HT_TASK::Task eth_send();
HT_TASK::Task CAN_recieve();
HT_TASK::Task eth_receive(); */

/* Functions */
void setup() {
  //Serial.begin(115200); //I dont know if this is the baudrate I also don't know if this is even needed
  qn::Ethernet.begin(); //begins QNEthernet
  
}

void loop() {
  scheduler.run();
  
}