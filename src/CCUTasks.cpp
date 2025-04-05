#include "CCUTasks.h"
#include "SystemTimeInterface.h"


void intitialize_all_interfaces()
{
    Serial.begin(115200);
    
    /* ACU Interface */
    ACUInterfaceInstance::create(millis(), 1000);

    /* Charger Interface */
    ChargerInterfaceInstance::create();

    // CANInterfacesInstance::create();
  }

bool run_update_display_task(const unsigned long& sysMicros, const HT_TASK::TaskInfo& taskInfo) {

    return true;
}


bool run_read_dial_task(const unsigned long& sysMicros, const HT_TASK::TaskInfo& taskInfo) {

    return true;
}


bool handle_enqueue_acu_can_data(const unsigned long& sysMicros, const HT_TASK::TaskInfo& taskInfo) {
    // Serial.println("handle enqueue acu data");
    ACUInterfaceInstance::instance().enqueue_ccu_status_data();
    // Serial.println("got past acu interface instance.instance");
    return true;
}


bool handle_enqueue_charger_can_data(const unsigned long& sysMicros, const HT_TASK::TaskInfo& taskInfo) {
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
    // Serial.println("handle send all data");
    CCUCANInterfaceImpl::send_all_CAN_msgs(CCUCANInterfaceImpl::acu_can_tx_buffer, &ACU_CAN);
    // Serial.println("sending acu");
    CCUCANInterfaceImpl::send_all_CAN_msgs(CCUCANInterfaceImpl::charger_can_tx_buffer, &CHARGER_CAN);
    //Serial.println("sending charger");
    return true;
}


bool sample_CAN_data(const unsigned long& sysMicros, const HT_TASK::TaskInfo& taskInfo) {
    // Serial.println("Sampling");
    etl::delegate<void(CANInterfaces &, const CAN_message_t &, unsigned long)> main_can_recv = etl::delegate<void(CANInterfaces &, const CAN_message_t &, unsigned long)>::create<CCUCANInterfaceImpl::ccu_CAN_recv>();
    process_ring_buffer(CCUCANInterfaceImpl::acu_can_rx_buffer, CANInterfacesInstance::instance(), millis(), main_can_recv); 
    process_ring_buffer(CCUCANInterfaceImpl::charger_can_rx_buffer, CANInterfacesInstance::instance(), millis(), main_can_recv); 

    return true;
}



/*
ChargerState_e evaulate_state_machine(ChargerStateMachine &current_state) {
     
} 
*/