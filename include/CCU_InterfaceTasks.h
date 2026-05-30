#ifndef CCU_INTERFACETASKS_H
#define CCU_INTERFACETASKS_H

/* External Dependencies */
#include <ht_task.hpp>
#include "SharedFirmwareTypes.h"

/* Local Dependencies */
#include "CCU_Constants.h"

/* Local System Includes */
#include "Level2System.h"
#include "MainChargeSystem.h"
#include "ChargerStateMachine.h"

/* Local Interface Include */
#include "ACUInterface.h"
#include "CANInterface.h"
#include "CCUCANInterfaceImpl.h"
#include "CCUEthernetInterface.h"
#include "ChargerInterface.h"
#include "DisplayInterface.h"
#include "Level2Interface.h"
#include "SystemTimeInterface.h"
#include "WatchdogInterface.h"
#include "ButtonInterface.h"
#include "RotaryEncoderInterface.h"

/* For Debugging */
#include "ChargerStateMachine.h"


/**
 * @brief Creates an instance of all interfaces. Init functions are called if necessary.
 */
void initialize_all_interfaces();

/**
 * @brief This task will fetch the watchdog state from WatchdogSystem and write it to the watchdog pin.
 */
::HT_TASK::TaskResponse run_kick_watchdog(const unsigned long& sysMicros, const HT_TASK::TaskInfo& taskInfo);

::HT_TASK::TaskResponse run_update_display_task(const unsigned long& sysMicros, const HT_TASK::TaskInfo& taskInfo);

::HT_TASK::TaskResponse run_toggle_display_task(const unsigned long& sysMicros, const HT_TASK::TaskInfo& taskInfo);

::HT_TASK::TaskResponse run_read_encoder_task(const unsigned long& sysMicros, const HT_TASK::TaskInfo& taskInfo);

::HT_TASK::TaskResponse handle_enqueue_acu_can_data(const unsigned long& sysMicros, const HT_TASK::TaskInfo& taskInfo);

::HT_TASK::TaskResponse handle_enqueue_charger_can_data(const unsigned long& sysMicros, const HT_TASK::TaskInfo& taskInfo);

::HT_TASK::TaskResponse run_send_ethernet(const unsigned long& sysMicros, const HT_TASK::TaskInfo& taskInfo);

::HT_TASK::TaskResponse run_receive_ethernet(const unsigned long& sysMicros, const HT_TASK::TaskInfo& taskInfo);

::HT_TASK::TaskResponse sample_can_data(const unsigned long& sysMicros, const HT_TASK::TaskInfo& taskInfo);

::HT_TASK::TaskResponse handle_send_all_data(const unsigned long& sysMicros, const HT_TASK::TaskInfo& taskInfo);

::HT_TASK::TaskResponse debug_prints(const unsigned long& sysMicros, const HT_TASK::TaskInfo& taskInfo);


#endif