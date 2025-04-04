/* Libraries */

#ifdef ARDUINO
#include <Arduino.h>

#endif

#include <QNEthernet.h>
#include "MainChargeSystem.h"
#include "SharedFirmwareTypes.h"
#include "CCUParams.h"
#include "ht_sched.hpp"
#include "ht_task.hpp"
#include "ChargerStateMachine.h"
#include "CCUCANInterfaceImpl.h"
#include "CCUTasks.h"

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


/* Task Declarations */
HT_TASK::Task update_display_task(HT_TASK::DUMMY_FUNCTION, run_update_display_task, CCUConstants::UPDATE_DISPLAY_PRIORITY, CCUConstants::HT_SCHED_PERIOD_US); //not sure what the priorities and loop rate should be for each task
HT_TASK::Task read_dial_task(HT_TASK::DUMMY_FUNCTION, run_read_dial_task, CCUConstants::READ_DIAL_PRIORITY, CCUConstants::HT_SCHED_PERIOD_US);
HT_TASK::Task queue_ACU_CAN(HT_TASK::DUMMY_FUNCTION, handle_enqueue_acu_can_data, CCUConstants::ENQUEUE_ACU_CAN_DATA_PRIORITY, CCUConstants::HT_SCHED_PERIOD_US);
HT_TASK::Task queue_Charger_CAN(HT_TASK::DUMMY_FUNCTION, handle_enqueue_charger_can_data, CCUConstants::ENQUEUE_CHARGER_CAN_DATA_PRIORITY, CCUConstants::HT_SCHED_PERIOD_US);
HT_TASK::Task send_ethernet(HT_TASK::DUMMY_FUNCTION, run_send_ethernet, CCUConstants::SEND_ETHERNET_PRIORITY, CCUConstants::HT_SCHED_PERIOD_US);
HT_TASK::Task receive_ethernet(HT_TASK::DUMMY_FUNCTION, run_receive_ethernet, CCUConstants::RECIEVE_ETHERNET_PRIORITY, CCUConstants::HT_SCHED_PERIOD_US);
HT_TASK::Task send_all_data(HT_TASK::DUMMY_FUNCTION, handle_send_all_data, CCUConstants::SEND_ALL_DATA_PRIORITY, CCUConstants::HT_SCHED_PERIOD_US);


 
/* Extern CAN instances */
FlexCAN_Type<CAN1> CCUCANInterfaceImpl::ACU_CAN;
FlexCAN_Type<CAN2> CCUCANInterfaceImpl::CHARGER_CAN;

/* Functions */
void setup() {
  
  intitialize_all_interfaces();

  scheduler.setTimingFunction(micros);
  //scheduler.schedule(update_display_task);
  //scheduler.schedule(read_dial_task);
  scheduler.schedule(queue_ACU_CAN);
  //scheduler.schedule(queue_Charger_CAN);
  //scheduler.schedule(send_ethernet);
  //scheduler.schedule(receive_ethernet);
  scheduler.schedule(send_all_data);
  Serial.println("setup ok");
}

void loop() {
  scheduler.run();
  Serial.println("looping ccu + send");
  delay(10);
}