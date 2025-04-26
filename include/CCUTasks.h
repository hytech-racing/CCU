#ifndef CCUTASKS_H
#define CCUTASKS_H

#include <ht_sched.hpp>
#include "CANInterface.h"
#include "CCUCANInterfaceImpl.h"
#include "ACUInterface.h"
#include "CCUEthernetInterface.h"
#include "ChargerInterface.h"
#include "SystemTimeInterface.h"
#include "CCU_Constants.h"
#include "WatchdogInterface.h"
#include "ChargerStateMachine.h"
#include "SharedFirmwareTypes.h"
#include "SystemTimeInterface.h"
#include "CCUData.h"
#include "MainChargeSystem.h"


void intitialize_all_interfaces();

bool run_update_display_task(const unsigned long& sysMicros, const HT_TASK::TaskInfo& taskInfo);

bool run_read_dial_task(const unsigned long& sysMicros, const HT_TASK::TaskInfo& taskInfo);

bool handle_enqueue_acu_can_data(const unsigned long& sysMicros, const HT_TASK::TaskInfo& taskInfo);

bool handle_enqueue_charger_can_data(const unsigned long& sysMicros, const HT_TASK::TaskInfo& taskInfo);

bool run_send_ethernet(const unsigned long& sysMicros, const HT_TASK::TaskInfo& taskInfo);

bool run_receive_ethernet(const unsigned long& sysMicros, const HT_TASK::TaskInfo& taskInfo);

bool handle_send_all_data(const unsigned long& sysMicros, const HT_TASK::TaskInfo& taskInfo);

bool sample_can_data(const unsigned long& sysMicros, const HT_TASK::TaskInfo& taskInfo);

bool init_kick_watchdog(const unsigned long& sysMicros, const HT_TASK::TaskInfo& taskInfo);

bool run_kick_watchdog(const unsigned long& sysMicros, const HT_TASK::TaskInfo& taskInfo);

bool tick_state_machine(const unsigned long& sysMicros, const HT_TASK::TaskInfo& taskInfo);

bool calculate_charge_current(const unsigned long& sysMicros, const HT_TASK::TaskInfo& taskInfo);

bool print_data(const unsigned long& sysMicros, const HT_TASK::TaskInfo& taskInfo);



#endif