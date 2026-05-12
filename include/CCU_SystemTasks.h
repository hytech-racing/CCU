#ifndef CCU_SYSTEMTASKS_H
#define CCU_SYSTEMTASKS_H

/* External Dependencies */
#include <ht_task.hpp>
#include "SharedFirmwareTypes.h"

/* Local Dependencies */
#include "CCU_Constants.h"

/* Local System Includes */
#include "Level2System.h"
#include "MainChargeSystem.h"
#include "ChargerStateMachine.h"

/* Local Interface Includes */
#include "ChargerInterface.h"
#include "SystemTimeInterface.h"
#include "WatchdogInterface.h"
#include "ChargerStateMachine.h"
#include "SystemTimeInterface.h"
#include "DisplayInterface.h"
#include "Level2Interface.h"
#include "CANInterface.h"
#include "CCUCANInterfaceImpl.h"
#include "ACUInterface.h"
#include "CCUEthernetInterface.h"

/**
 * @brief Creates an instance of all systems.
 */
bool initialize_all_systems();

HT_TASK::TaskResponse tick_state_machine(const unsigned long& sysMicros, const HT_TASK::TaskInfo& taskInfo);

HT_TASK::TaskResponse calculate_charge_current(const unsigned long& sysMicros, const HT_TASK::TaskInfo& taskInfo);


#endif