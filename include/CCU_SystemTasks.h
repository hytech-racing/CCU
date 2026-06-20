#ifndef CCU_SYSTEMTASKS_H
#define CCU_SYSTEMTASKS_H

/* External Dependencies */
#include <ht_task.hpp>
#include "SharedFirmwareTypes.h"
#include "CANInterface.h"

/* Local Dependencies */
#include "CCU_Constants.h"

/* Local System Includes */
#include "Level2System.h"
#include "MainChargeSystem.h"
#include "ChargerStateMachine.h"

/* Local Interface Includes */
#include "ACUInterface.h"
#include "ButtonInterface.h"
#include "CCUCANInterfaceImpl.h"
#include "CCUEthernetInterface.h"
#include "ChargerInterface.h"
#include "DisplayInterface.h"
#include "Level2Interface.h"
#include "RotaryEncoderInterface.h"
#include "SystemTimeInterface.h"
#include "WatchdogInterface.h"

/**
 * @brief Creates an instance of all systems.
 */
bool initialize_all_systems();

extern etl::delegate<bool()> is_120_conditions_ok;
extern etl::delegate<bool()> is_120_switched;
extern etl::delegate<bool()> is_240_switched;
extern etl::delegate<bool()> is_state_B2_ready;
extern etl::delegate<bool()> is_state_C2_ready;
extern etl::delegate<bool()> is_shdn_C_high;
extern etl::delegate<bool()> reset_error_requested;
extern etl::delegate<void()> set_sw_shdn_high;
extern etl::delegate<void()> set_sw_shdn_low;
extern etl::delegate<void()> set_start_charge_high;
extern etl::delegate<void()> set_start_charge_low;
extern etl::delegate<void()> reset_startup_time_ms;

::HT_TASK::TaskResponse tick_state_machine(const unsigned long& sysMicros, const HT_TASK::TaskInfo& taskInfo);

::HT_TASK::TaskResponse calculate_charge_current(const unsigned long& sysMicros, const HT_TASK::TaskInfo& taskInfo);


#endif