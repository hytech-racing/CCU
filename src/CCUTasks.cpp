#include "CCUTasks.h"


CCUData ccu_data; //NOLINT (necessary for passing ccu_data struct as a reference)

HT_TASK::TaskResponse intitialize_all_interfaces()
{
    /* ACU Interface */
    ACUInterfaceInstance::create(millis(), 1000, ccu_data);

    /* Charger Interface */
    ChargerInterfaceInstance::create(ccu_data); //NOLINT (necessary for passing ccu_data struct as a reference)

    ChargerStateMachineInstance::create(ccu_data); //NOLINT (necessary for passing ccu_data struct as a reference)

    WatchdogInstance::create();
    WatchdogInstance::instance().init(); 

    CANInterfacesInstance::create(ACUInterfaceInstance::instance(), ChargerInterfaceInstance::instance());

    pinMode(ccu_data.SHDN_E_READ, INPUT);

    /* These should be put in a CCU Systems Tasks but I put it here just to get CCU working asap */
    MainChargeSystemInstance::create(ccu_data); //NOLINT (necessary for passing ccu_data struct as a reference)
    DisplayInterfaceInstance::create(ccu_data); //NOLINT 

    return HT_TASK::TaskResponse::YIELD;

}


HT_TASK::TaskResponse run_read_dial_task(const unsigned long& sysMicros, const HT_TASK::TaskInfo& taskInfo) {

    return HT_TASK::TaskResponse::YIELD;
}


HT_TASK::TaskResponse handle_enqueue_acu_can_data(const unsigned long& sysMicros, const HT_TASK::TaskInfo& taskInfo) {
    ACUInterfaceInstance::instance().enqueue_ccu_status_data();
    return HT_TASK::TaskResponse::YIELD;
}


HT_TASK::TaskResponse handle_enqueue_charger_can_data(const unsigned long& sysMicros, const HT_TASK::TaskInfo& taskInfo) {
    ChargerInterfaceInstance::instance().enqueue_charging_data();
    return HT_TASK::TaskResponse::YIELD;
}


HT_TASK::TaskResponse run_send_ethernet(const unsigned long& sysMicros, const HT_TASK::TaskInfo& taskInfo) {

    return HT_TASK::TaskResponse::YIELD;
}


HT_TASK::TaskResponse run_receive_ethernet(const unsigned long& sysMicros, const HT_TASK::TaskInfo& taskInfo) {

    return HT_TASK::TaskResponse::YIELD;
}


HT_TASK::TaskResponse handle_send_all_data(const unsigned long& sysMicros, const HT_TASK::TaskInfo& taskInfo) {

    CCUCANInterfaceImpl::send_all_CAN_msgs(CCUCANInterfaceImpl::acu_can_tx_buffer, &ACU_CAN);
    CCUCANInterfaceImpl::send_all_CAN_msgs(CCUCANInterfaceImpl::charger_can_tx_buffer, &CHARGER_CAN);
    return HT_TASK::TaskResponse::YIELD;
}


HT_TASK::TaskResponse sample_can_data(const unsigned long& sysMicros, const HT_TASK::TaskInfo& taskInfo) {

    etl::delegate<void(CANInterfaces &, const CAN_message_t &, unsigned long)> main_can_recv = etl::delegate<void(CANInterfaces &, const CAN_message_t &, unsigned long)>::create<CCUCANInterfaceImpl::ccu_CAN_recv>();
    process_ring_buffer(CCUCANInterfaceImpl::acu_can_rx_buffer, CANInterfacesInstance::instance(), sys_time::hal_millis(), main_can_recv); 
    process_ring_buffer(CCUCANInterfaceImpl::charger_can_rx_buffer, CANInterfacesInstance::instance(), sys_time::hal_millis(), main_can_recv); 

    return HT_TASK::TaskResponse::YIELD;
}


HT_TASK::TaskResponse init_kick_watchdog(const unsigned long& sysMicros, const HT_TASK::TaskInfo& taskInfo)
{
    WatchdogInstance::create(WATCHDOG_KICK_INTERVAL_MS); // NOLINT
    pinMode(WATCHDOG_PIN, OUTPUT);
    pinMode(SOFTWARE_OK_PIN, OUTPUT);
    return HT_TASK::TaskResponse::YIELD;
}


HT_TASK::TaskResponse run_kick_watchdog(const unsigned long& sysMicros, const HT_TASK::TaskInfo& taskInfo) {
    
    digitalWrite(WATCHDOG_PIN, WatchdogInstance::instance().get_watchdog_state(sys_time::hal_millis()));
    return HT_TASK::TaskResponse::YIELD;
}


HT_TASK::TaskResponse tick_state_machine(const unsigned long &sysMicros, const HT_TASK::TaskInfo &taskInfo) {
   
    ChargerStateMachineInstance::instance().tick_state_machine(sys_time::hal_millis());
    return HT_TASK::TaskResponse::YIELD;
}

HT_TASK::TaskResponse calculate_charge_current(const unsigned long& sysMicros, const HT_TASK::TaskInfo& taskInfo) {
   
    MainChargeSystemInstance::instance().calculate_charge_current();
    return HT_TASK::TaskResponse::YIELD;
}

HT_TASK::TaskResponse init_update_display_task(const unsigned long& sysMicros, const HT_TASK::TaskInfo& taskInfo) {

    DisplayInterfaceInstance::instance().init();
    return HT_TASK::TaskResponse::YIELD;
}

HT_TASK::TaskResponse run_update_display_task(const unsigned long& sysMicros, const HT_TASK::TaskInfo& taskInfo) {
    DisplayInterfaceInstance::instance().display_data();
    return HT_TASK::TaskResponse::YIELD;
}



HT_TASK::TaskResponse print_data(const unsigned long& sysMicros, const HT_TASK::TaskInfo& taskInfo) {
    
    Serial.print("Charge enable: ");
    Serial.println(ccu_data.balancing_enabled);
    Serial.print("Charging Status: ");
    // Serial.println(static_cast<int>(ChargerStateMachineInstance::instance().get_state()));
    // Serial.print("BMS Status: ");
    // Serial.println(static_cast<int>(ACUInterfaceInstance::instance().get_latest_data().acu_state));
    // Serial.print("Cell Voltage max: ");
    // Serial.println(ACUInterfaceInstance::instance().get_latest_data().high_voltage);
    // Serial.print("Cell voltage min: ");
    // Serial.println(ACUInterfaceInstance::instance().get_latest_data().low_voltage);
    // Serial.print("Cell voltage average: ");
    // Serial.println(ACUInterfaceInstance::instance().get_latest_data().average_voltage);
    // Serial.print("Cell voltage max and min delta: ");
    // Serial.println((ACUInterfaceInstance::instance().get_latest_data().high_voltage) - (ACUInterfaceInstance::instance().get_latest_data().low_voltage));
    // Serial.print("Total pack voltage: ");
    // Serial.println(ACUInterfaceInstance::instance().get_latest_data().total_voltage);
    // Serial.print("Cell temp max: "); //maximum cell temperature that ACU says cells should have
    // Serial.println(ccu_data.max_cell_temp);
    // Serial.print("Cell temp min: "); 
    // Serial.println(ccu_data.min_cell_temp);
    // Serial.print("Max Board Temp: ");
    // Serial.println(ccu_data.max_board_temp);
    // Serial.print("Charging current: "); //how much current the charger is supplying
    // Serial.println(ChargerInterfaceInstance::instance().get_latest_charger_data().output_current_low);

    // Serial.print("Calculated charge current: ");
    // Serial.println(ccu_data.calculated_charge_current);

     Serial.print("cell temps");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 12; j++) {
           
            Serial.print(ACUInterfaceInstance::instance().get_latest_data().bms_detailed_temps[j][i]);
            Serial.print(",");
        }
        Serial.println("");
    }
   // Serial.print("SHDN_E high: ");
   // Serial.println(digitalRead(ccu_data.SHDN_E_READ) == HIGH);

   Serial.print("cell voltages");
   for (int chip = 0; chip < 12; chip++) {
    Serial.print("cell ");
    Serial.print(chip);
    Serial.print("voltages: ");
    for (int cell = 0; cell < 12; cell++) {
        Serial.print(ACUInterfaceInstance::instance().get_latest_data().cell_voltages[chip][cell]);
        Serial.print(" ");
    }
    Serial.println("");
   }

   return HT_TASK::TaskResponse::YIELD;
}
