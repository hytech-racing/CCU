/* Libraries */

#ifdef ARDUINO
#include <Arduino.h>

#endif

#include <QNEthernet.h>
#include "MainChargeSystem.h"
#include "SharedFirmwareTypes.h"
#include "CCUData.h"
#include "ht_sched.hpp"
#include "ht_task.hpp"
#include "ChargerStateMachine.h"
#include "CCUCANInterfaceImpl.h"
#include "CCUTasks.h"
#include "SystemTimeInterface.h"
#include "DisplaySystem.h"
#include <IntervalTimer.h>

IntervalTimer watchdogTimer; 

FlexCAN_Type<CAN2> CHARGER_CAN; // gets defined in main as of right now
FlexCAN_Type<CAN1> ACU_CAN;

/* Parameters */
ACUAllData_s acu_all_data;

/* Systems */
namespace qn = qindesign::network; //setup of qn namespace
qn::EthernetUDP udp; //setup of qn namespace


/* Scheduler Setup */
HT_SCHED::Scheduler& scheduler = HT_SCHED::Scheduler::getInstance(); 



// Task Declarations 
HT_TASK::Task update_display_task(init_update_display_task, run_update_display_task, CCUConstants::UPDATE_DISPLAY_PRIORITY, CCUConstants::UPDATE_DISPLAY_PERIOD);

HT_TASK::Task read_dial_task(HT_TASK::DUMMY_FUNCTION, run_read_dial_task, CCUConstants::READ_DIAL_PRIORITY, CCUConstants::HT_SCHED_PERIOD_US);
HT_TASK::Task queue_ACU_CAN(HT_TASK::DUMMY_FUNCTION, handle_enqueue_acu_can_data, CCUConstants::ENQUEUE_ACU_CAN_DATA_PRIORITY, CCUConstants::ENQUEUE_ACU_CAN_DATA_PERIOD);
HT_TASK::Task queue_Charger_CAN(HT_TASK::DUMMY_FUNCTION, handle_enqueue_charger_can_data, CCUConstants::ENQUEUE_CHARGER_CAN_DATA_PRIORITY, CCUConstants::ENQUEUE_CHARGER_CAN_DATA_PERIOD);
HT_TASK::Task send_ethernet(HT_TASK::DUMMY_FUNCTION, run_send_ethernet, CCUConstants::SEND_ETHERNET_PRIORITY, CCUConstants::HT_SCHED_PERIOD_US);
HT_TASK::Task receive_ethernet(HT_TASK::DUMMY_FUNCTION, run_receive_ethernet, CCUConstants::RECIEVE_ETHERNET_PRIORITY, CCUConstants::HT_SCHED_PERIOD_US);
HT_TASK::Task send_all_data(HT_TASK::DUMMY_FUNCTION, handle_send_all_data, CCUConstants::SEND_ALL_DATA_PRIORITY, CCUConstants::SEND_ALL_DATA_PERIOD);
HT_TASK::Task run_sample_can_data(HT_TASK::DUMMY_FUNCTION, sample_can_data, CCUConstants::SAMPLE_CAN_DATA_PRIORITY, CCUConstants::SAMPLE_CAN_DATA_PERIOD);
HT_TASK::Task kick_watchdog_task(init_kick_watchdog, run_kick_watchdog, CCUConstants::KICK_WATCHDOG_PRIORITY, CCUConstants::KICK_WATCHDOG_PERIOD);
HT_TASK::Task debug_print_task(HT_TASK::DUMMY_FUNCTION, print_data, CCUConstants::UPDATE_DISPLAY_PRIORITY, CCUConstants::UPDATE_DISPLAY_PERIOD); 
HT_TASK::Task tick_state_machine_task(HT_TASK::DUMMY_FUNCTION, tick_state_machine, CCUConstants::TICK_STATE_MACHINE_PRIORITY, CCUConstants::TICK_STATE_MACHINE_PERIOD);

HT_TASK::Task calculate_charge_current_task(HT_TASK::DUMMY_FUNCTION, calculate_charge_current, CCUConstants::TICK_STATE_MACHINE_PRIORITY, CCUConstants::TICK_STATE_MACHINE_PERIOD);


/* Functions */
void setup() {

  SPI.begin();
  SPI.beginTransaction(SPISettings(4000000, MSBFIRST, SPI_MODE0)); //NOLINT (spi settings)
 
  qn::Ethernet.begin(); //begins QNEthernet


  intitialize_all_interfaces();

  scheduler.setTimingFunction(micros);

  scheduler.schedule(read_dial_task);
  scheduler.schedule(queue_ACU_CAN);
  scheduler.schedule(queue_Charger_CAN);
  //scheduler.schedule(send_ethernet); //not using ethernet
  //scheduler.schedule(receive_ethernet);
  scheduler.schedule(send_all_data);
  //scheduler.schedule(debug_print_task); //only uncomment if display isn't updating values
  scheduler.schedule(run_sample_can_data);
  scheduler.schedule(kick_watchdog_task); 
 // scheduler.schedule(tick_state_machine_task); //this task times out watchdog for some reason (state machine would be nice to have but isn't a priority for CCU to work)
  scheduler.schedule(calculate_charge_current_task);
  scheduler.schedule(update_display_task);

  handle_CAN_setup(ACU_CAN, CCUConstants::CAN_BAUDRATE, &CCUCANInterfaceImpl::on_acu_can_receive);
  handle_CAN_setup(CHARGER_CAN, CCUConstants::CHARGER_CAN_BAUDRATE, &CCUCANInterfaceImpl::on_charger_can_receive);


  
}

void loop() {
  scheduler.run();
}