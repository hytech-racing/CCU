#ifndef CCUTASKS_H
#define CCUTASKS_H

#include <ht_sched.hpp>

#include "CCUCANInterfaceImpl.h"
#include "ACUInterface.h"
#include "CCUEthernetInterface.h"
#include "ChargerInterface.h"
#include "SystemTimeInterface.h"


void intitialize_all_interfaces();

bool run_update_display_task(const unsigned long& sysMicros, const HT_TASK::TaskInfo& taskInfo);

bool run_read_dial_task(const unsigned long& sysMicros, const HT_TASK::TaskInfo& taskInfo);

bool handle_enqueue_acu_can_data(const unsigned long& sysMicros, const HT_TASK::TaskInfo& taskInfo);

bool handle_enqueue_charger_can_data(const unsigned long& sysMicros, const HT_TASK::TaskInfo& taskInfo);

bool run_send_ethernet(const unsigned long& sysMicros, const HT_TASK::TaskInfo& taskInfo);

bool run_receive_ethernet(const unsigned long& sysMicros, const HT_TASK::TaskInfo& taskInfo);

bool handle_send_all_data(const unsigned long& sysMicros, const HT_TASK::TaskInfo& taskInfo);

bool sample_CAN_data(const unsigned long& sysMicros, const HT_TASK::TaskInfo& taskInfo);


//ChargerState_e evaulate_state_machine(ChargerStateMachine &current_state);

//bool run_receive_ACU_CAN(const unsigned long& sysMicros, const HT_TASK::TaskInfo& taskInfo);

//bool run_receive_Charger_CAN(const unsigned long& sysMicros, const HT_TASK::TaskInfo& taskInfo);

#endif