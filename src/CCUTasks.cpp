#include "CCUTasks.h"
#include "CCUCANInterfaceImpl.h"
#include "ACUInterface.h"
#include "CCUEthernetInterface.h"
#include "ChargerInterface.h"


bool run_update_display_task(const unsigned long& sysMicros, const HT_TASK::TaskInfo& taskInfo) {

    return true;
}


bool run_read_dial_task(const unsigned long& sysMicros, const HT_TASK::TaskInfo& taskInfo) {

    return true;
}


bool handle_enqueue_ACU_CAN_data(const unsigned long& sysMicros, const HT_TASK::TaskInfo& taskInfo) {
    ACUInterfaceInstance::instance().enqueue_ccu_status_data();
    return true;
}

bool handle_enqueue_Charger_CAN_data(const unsigned long& sysMicros, const HT_TASK::TaskInfo& taskInfo) {
    ChargerInterfaceInstance::instance().enqueue_charging_data();
    return true;
}


bool run_send_ethernet(const unsigned long& sysMicros, const HT_TASK::TaskInfo& taskInfo) {

    return true;
}


bool run_receive_ethernet(const unsigned long& sysMicros, const HT_TASK::TaskInfo& taskInfo) {

    return true;
}

bool handle_send_all_data(const unsigned long& sysMicros, const HT_TASK::TaskInfo& taskInfo) {
    CCUCANInterfaceImpl::send_all_CAN_msgs(CCUCANInterfaceImpl::acu_can_tx_buffer, &CCUCANInterfaceImpl::ACU_CAN);
    CCUCANInterfaceImpl::send_all_CAN_msgs(CCUCANInterfaceImpl::charger_can_tx_buffer, &CCUCANInterfaceImpl::CHARGER_CAN);
    return true;
}

/*
ChargerState_e evaulate_state_machine(ChargerStateMachine &current_state) {
     
} 
*/