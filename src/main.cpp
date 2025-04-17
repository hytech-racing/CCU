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
#include "SystemTimeInterface.h"



FlexCAN_Type<CAN2> CHARGER_CAN; // gets defined in main as of right now
FlexCAN_Type<CAN1> ACU_CAN;

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
HT_TASK::Task queue_ACU_CAN(HT_TASK::DUMMY_FUNCTION, handle_enqueue_acu_can_data, 1, 100000UL);
HT_TASK::Task queue_Charger_CAN(HT_TASK::DUMMY_FUNCTION, handle_enqueue_charger_can_data, 1, 100000UL);
HT_TASK::Task send_ethernet(HT_TASK::DUMMY_FUNCTION, run_send_ethernet, CCUConstants::SEND_ETHERNET_PRIORITY, CCUConstants::HT_SCHED_PERIOD_US);
HT_TASK::Task receive_ethernet(HT_TASK::DUMMY_FUNCTION, run_receive_ethernet, CCUConstants::RECIEVE_ETHERNET_PRIORITY, CCUConstants::HT_SCHED_PERIOD_US);
HT_TASK::Task send_all_data(HT_TASK::DUMMY_FUNCTION, handle_send_all_data, 1);
HT_TASK::Task run_sample_CAN_data(HT_TASK::DUMMY_FUNCTION, sample_CAN_data, 2);
HT_TASK::Task kick_watchdog_task(init_kick_watchdog, run_kick_watchdog, 1);

 

bool evaluate_state_machine(const unsigned long& sysMicros, const HT_TASK::TaskInfo& taskInfo) {
  auto state = state_machine.tick_state_machine(sys_time::hal_millis());
  return true;    
}



/* Functions */
void setup() {

  qn::Ethernet.begin(); //begins QNEthernet


  intitialize_all_interfaces();

  scheduler.setTimingFunction(micros);

  scheduler.schedule(update_display_task);
  scheduler.schedule(read_dial_task);
  scheduler.schedule(queue_ACU_CAN);
  scheduler.schedule(queue_Charger_CAN);
  scheduler.schedule(send_ethernet);
  scheduler.schedule(receive_ethernet);
  scheduler.schedule(send_all_data);

  handle_CAN_setup(ACU_CAN, CCUConstants::CAN_BAUDRATE, &CCUCANInterfaceImpl::on_acu_can_receive);
  handle_CAN_setup(CHARGER_CAN, CCUConstants::CAN_BAUDRATE, &CCUCANInterfaceImpl::on_charger_can_receive);

  //while(!Serial) {};
  
}

void loop() {
  scheduler.run();
}