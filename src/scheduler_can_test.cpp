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

FlexCAN_Type<CAN2> CHARGER_CAN; // gets defined in main as of right now
FlexCAN_Type<CAN1> ACU_CAN;

/* Parameters */
ACUAllData_s acu_all_data;
//CCUParams ccu_params; 

/* Initialization of the charging state machine */
ChargerStateMachine state_machine;

/* Systems */
namespace qn = qindesign::network; //setup of qn namespace
qn::EthernetUDP udp; //setup of qn namespace


/* Scheduler Setup */
HT_SCHED::Scheduler& scheduler = HT_SCHED::Scheduler::getInstance();

etl::delegate<void(CANInterfaces &, const CAN_message_t &, unsigned long)> main_can_recv = etl::delegate<void(CANInterfaces &, const CAN_message_t &, unsigned long)>::create<CCUCANInterfaceImpl::ccu_CAN_recv>();



/* Task Declarations */
// HT_TASK::Task update_display_task(HT_TASK::DUMMY_FUNCTION, run_update_display_task, CCUConstants::UPDATE_DISPLAY_PRIORITY, CCUConstants::HT_SCHED_PERIOD_US); //not sure what the priorities and loop rate should be for each task
// HT_TASK::Task read_dial_task(HT_TASK::DUMMY_FUNCTION, run_read_dial_task, CCUConstants::READ_DIAL_PRIORITY, CCUConstants::HT_SCHED_PERIOD_US);
HT_TASK::Task queue_ACU_CAN(HT_TASK::DUMMY_FUNCTION, handle_enqueue_acu_can_data, 1, 100000UL); //NOLINT
HT_TASK::Task queue_Charger_CAN(HT_TASK::DUMMY_FUNCTION, handle_enqueue_charger_can_data, 1, 100000UL); //NOLINT
// HT_TASK::Task send_ethernet(HT_TASK::DUMMY_FUNCTION, run_send_ethernet, CCUConstants::SEND_ETHERNET_PRIORITY, CCUConstants::HT_SCHED_PERIOD_US);
// HT_TASK::Task receive_ethernet(HT_TASK::DUMMY_FUNCTION, run_receive_ethernet, CCUConstants::RECIEVE_ETHERNET_PRIORITY, CCUConstants::HT_SCHED_PERIOD_US);
HT_TASK::Task send_all_data(HT_TASK::DUMMY_FUNCTION, handle_send_all_data, 2); //NOLINT
HT_TASK::Task run_sample_CAN_data(HT_TASK::DUMMY_FUNCTION, sample_CAN_data, 2); //NOLINT



    

/* Functions */
void setup() {
  //Serial.begin(115200);
  //delay(4000);
  //Serial.println("started setup");
  //Serial.println("handle can setup");
  intitialize_all_interfaces();

  scheduler.setTimingFunction(micros);
  //scheduler.schedule(update_display_task);
  //scheduler.schedule(read_dial_task);
  scheduler.schedule(queue_ACU_CAN);
  scheduler.schedule(queue_Charger_CAN);
  //scheduler.schedule(send_ethernet);
  //scheduler.schedule(receive_ethernet);
  scheduler.schedule(send_all_data);
  //Serial.println("setup ok");

  handle_CAN_setup(ACU_CAN, CCUConstants::CAN_BAUDRATE, &CCUCANInterfaceImpl::on_acu_can_receive);
  handle_CAN_setup(CHARGER_CAN, CCUConstants::CAN_BAUDRATE, &CCUCANInterfaceImpl::on_charger_can_receive);

}

void loop() {
  scheduler.run();
  //delay(10);
  
}