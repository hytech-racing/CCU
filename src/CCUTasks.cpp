#include "CCUTasks.h"


void intitialize_all_interfaces()
{
    //Serial.begin(115200);

    CCUData ccu_data; //NOLINT (necessary for passing ccu_data struct as a reference)
    
    /* ACU Interface */
    ACUInterfaceInstance::create(millis(), 1000, ccu_data);

    /* Charger Interface */
    ChargerInterfaceInstance::create(ccu_data); //NOLINT (necessary for passing ccu_data struct as a reference)

    // CANInterfacesInstance::create();

    ChargerStateMachineInstance::create(ccu_data); //NOLINT (necessary for passing ccu_data struct as a reference)
  }

bool run_update_display_task(const unsigned long& sysMicros, const HT_TASK::TaskInfo& taskInfo) {

    return true;
}


bool run_read_dial_task(const unsigned long& sysMicros, const HT_TASK::TaskInfo& taskInfo) {

    return true;
}


bool handle_enqueue_acu_can_data(const unsigned long& sysMicros, const HT_TASK::TaskInfo& taskInfo) {
    ACUInterfaceInstance::instance().enqueue_ccu_status_data();
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
    CCUCANInterfaceImpl::send_all_CAN_msgs(CCUCANInterfaceImpl::acu_can_tx_buffer, &ACU_CAN);
    CCUCANInterfaceImpl::send_all_CAN_msgs(CCUCANInterfaceImpl::charger_can_tx_buffer, &CHARGER_CAN);
    return true;
}


bool sample_can_data(const unsigned long& sysMicros, const HT_TASK::TaskInfo& taskInfo) {
    etl::delegate<void(CANInterfaces &, const CAN_message_t &, unsigned long)> main_can_recv = etl::delegate<void(CANInterfaces &, const CAN_message_t &, unsigned long)>::create<CCUCANInterfaceImpl::ccu_CAN_recv>();
    process_ring_buffer(CCUCANInterfaceImpl::acu_can_rx_buffer, CANInterfacesInstance::instance(), sys_time::hal_millis(), main_can_recv); 
    process_ring_buffer(CCUCANInterfaceImpl::charger_can_rx_buffer, CANInterfacesInstance::instance(), sys_time::hal_millis(), main_can_recv); 

    return true;
}


bool run_kick_watchdog(const unsigned long& sysMicros, const HT_TASK::TaskInfo& taskInfo) {
    
    digitalWrite(WATCHDOG_PIN, WatchdogInstance::instance().get_watchdog_state(sys_time::hal_millis()));
    return true;

}

bool init_kick_watchdog(const unsigned long& sysMicros, const HT_TASK::TaskInfo& taskInfo)
{
    WatchdogInstance::create(WATCHDOG_KICK_INTERVAL_MS); // NOLINT
    pinMode(WATCHDOG_PIN, OUTPUT);
    return true;
}


bool tick_state_machine(const unsigned long &sysMicros, const HT_TASK::TaskInfo &taskInfo) {
    ChargerStateMachineInstance::instance().tick_state_machine(sys_time::hal_millis());
    return true;
}


bool print_data(const unsigned long& sysMicros, const HT_TASK::TaskInfo& taskInfo) {

    Serial.print("Charging Status: ");
    Serial.println(static_cast<int>(ChargerStateMachineInstance::instance().get_state()));
    Serial.print("Cell Voltage max: ");
    Serial.println(ACUInterfaceInstance::instance().get_latest_data().high_voltage);
    Serial.print("Cell voltage min: ");
    Serial.println(ACUInterfaceInstance::instance().get_latest_data().low_voltage);
    Serial.print("Cell voltage average: ");
    Serial.println(ACUInterfaceInstance::instance().get_latest_data().average_voltage);
    Serial.print("Cell voltage max and min delta: ");
    Serial.println((ACUInterfaceInstance::instance().get_latest_data().high_voltage) - (ACUInterfaceInstance::instance().get_latest_data().low_voltage));
    // Serial.print("Cell temp max: "); //maximum cell temperature that ACU says cells should have
    // Serial.println();
    // Serial.print("Current cell temp: "); 
    // Serial.println();
    Serial.print("Charging current: "); //how much current the charger is supplying
    Serial.println(ChargerInterfaceInstance::instance().get_latest_charger_data().output_current_high);
    return true;
}
