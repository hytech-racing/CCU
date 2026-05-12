#include "CCU_InterfaceTasks.h"

void initialize_all_interfaces()
{
    analogReadResolution(CCUInterfaces::ANALOG_READ_RESOLUTION);


    /* ADC Interface */
    ADCInterfaceInstance::create(   ADCPinout_s { CCUInterfaces::SHDN_A_PIN,
                                CCUInterfaces::SHDN_B_PIN,
                                CCUInterfaces::SHDN_C_PIN,
                                CCUInterfaces::SHDN_D_PIN,
                                CCUInterfaces::SHDN_E_PIN,
                                CCUInterfaces::SHDN_F_PIN,
                                CCUInterfaces::SHDN_G_PIN,
                                CCUInterfaces::SCALED_24V_PIN,
                                CCUInterfaces::CONTROL_PILOT_PIN,
                                CCUInterfaces::PROXIMITY_PILOT_PIN,
                                CCUInterfaces::TEENSY_240_ENABLED_PIN,
                                CCUInterfaces::TEENSY_240_OK_PIN,
                                CCUInterfaces::JUMPER_OUT_PIN },
                                    ADCConversions_s { CCUInterfaces::GLV_CONV_FACTOR,
                                CCUInterfaces::CONTROL_PILOT_CONV_FACTOR,
                                CCUInterfaces::PROXIMITY_PILOT_CONV_FACTOR,
                                CCUInterfaces::JUMPER_OUT_CONV_FACTOR },
                                4096.0f
    );
    ADCInterfaceInstance::instance().init(sys_time::hal_millis());


    /* CAN Interfaces Construct */
    CANInterfacesInstance::create(ACUInterfaceInstance::instance(), ChargerInterfaceInstance::instance(), EnergyMeterInterfaceInstance::instance());


    /* Charger Interface */
    ChargerInterface(ACUInterfaceInstance::instance());


    /* Display Interface */
    DisplayInterfaceInstance::create(   DisplayPinout_s { CCUInterfaces::LCD_CS_PIN,
                                    CCUInterfaces::LCD_DC_PIN,
                                    CCUInterfaces::LCD_MOSI_PIN,
                                    CCUInterfaces::LCD_SCK_PIN,
                                    CCUInterfaces::LCD_RESET_PIN,
                                    CCUInterfaces::LCD_MISO_PIN }
    );
    DisplayInterfaceInstance::instance().init();


    /* Level2 Interface */
    Level2InterfaceInstance::create( Level2Pinout_s { CCUInterfaces::CONTROL_PWM_SENSE_PIN,
                                    CCUInterfaces::START_CHARGE_PIN }
    );
    Level2InterfaceInstance::instance().init();


    /* Watchdog Interface */
    WatchdogInterfaceInstance::create( WatchdogPinout_s {
                                CCUInterfaces::WATCHDOG_KICK_PIN,
                                CCUInterfaces::SOFTWARE_NOT_OK_PIN }
    );

}


HT_TASK::TaskResponse run_kick_watchdog(const unsigned long& sysMicros, const HT_TASK::TaskInfo& taskInfo)
{
    WatchdogInterfaceInstance::instance().update_watchdog_state(sys_time::hal_millis());
    return HT_TASK::TaskResponse::YIELD;
}

HT_TASK::TaskResponse run_read_dial_task(const unsigned long& sysMicros, const HT_TASK::TaskInfo& taskInfo)
{
    return HT_TASK::TaskResponse::YIELD;
}


HT_TASK::TaskResponse handle_enqueue_acu_can_data(const unsigned long& sysMicros, const HT_TASK::TaskInfo& taskInfo)
{
    ACUInterfaceInstance::instance().enqueue_ccu_status_data();
    return HT_TASK::TaskResponse::YIELD;
}


HT_TASK::TaskResponse handle_enqueue_charger_can_data(const unsigned long& sysMicros, const HT_TASK::TaskInfo& taskInfo)
{
    ChargerInterfaceInstance::instance().enqueue_charging_data(ACUInterfaceInstance::instance(), MainChargeSystemInstance::instance().get_charge_current());
    return HT_TASK::TaskResponse::YIELD;
}


HT_TASK::TaskResponse run_send_ethernet(const unsigned long& sysMicros, const HT_TASK::TaskInfo& taskInfo)
{
    return HT_TASK::TaskResponse::YIELD;
}


HT_TASK::TaskResponse run_receive_ethernet(const unsigned long& sysMicros, const HT_TASK::TaskInfo& taskInfo)
{
    return HT_TASK::TaskResponse::YIELD;
}


HT_TASK::TaskResponse handle_send_all_data(const unsigned long& sysMicros, const HT_TASK::TaskInfo& taskInfo)
{
    CCUCANInterfaceImpl::send_all_CAN_msgs(CCUCANInterfaceImpl::acu_can_tx_buffer, &ACU_CAN);
    CCUCANInterfaceImpl::send_all_CAN_msgs(CCUCANInterfaceImpl::charger_can_tx_buffer, &CHARGER_CAN);
    return HT_TASK::TaskResponse::YIELD;
}


HT_TASK::TaskResponse sample_can_data(const unsigned long& sysMicros, const HT_TASK::TaskInfo& taskInfo)
{
    etl::delegate<void(CANInterfaces &, const CAN_message_t &, unsigned long)> main_can_recv = etl::delegate<void(CANInterfaces &, const CAN_message_t &, unsigned long)>::create<CCUCANInterfaceImpl::ccu_CAN_recv>();
    process_ring_buffer(CCUCANInterfaceImpl::acu_can_rx_buffer, CANInterfacesInstance::instance(), sys_time::hal_millis(), main_can_recv);
    process_ring_buffer(CCUCANInterfaceImpl::charger_can_rx_buffer, CANInterfacesInstance::instance(), sys_time::hal_millis(), main_can_recv);

    return HT_TASK::TaskResponse::YIELD;
}


HT_TASK::TaskResponse init_update_display_task(const unsigned long& sysMicros, const HT_TASK::TaskInfo& taskInfo)
{
    DisplayInterfaceInstance::instance().init();
    return HT_TASK::TaskResponse::YIELD;
}


HT_TASK::TaskResponse run_update_display_task(const unsigned long& sysMicros, const HT_TASK::TaskInfo& taskInfo)
{
    DisplayInterfaceInstance::instance().display_data();
    DisplayInterfaceInstance::instance().refresh_display_data(sys_time::hal_millis());
    return HT_TASK::TaskResponse::YIELD;
}


HT_TASK::TaskResponse debug_prints(const unsigned long& sysMicros, const HT_TASK::TaskInfo& taskInfo)
{
    const auto& acu_data = ACUInterfaceInstance::instance().get_latest_data();
    const auto& charger_data = ChargerInterfaceInstance::instance().get_latest_charger_data();
    const auto& level2_data = Level2InterfaceInstance::instance().getLevel2Data();

    Serial.println();

    /* General Status */
    Serial.printf("Balancing Enabled  : %s\n", MainChargeSystemInstance::instance().is_balancing_enabled() ? "YES" : "NO");
    Serial.printf("Charging State  : %d\n", static_cast<int>(ChargerStateMachineInstance::instance().get_state()));
    Serial.printf("BMS State       : %d\n", static_cast<int>(acu_data.acu_state));
    Serial.println();

    /* Voltage Information */
    Serial.printf("Cell Voltage Max   : %.3f V\n", acu_data.high_voltage);
    Serial.printf("Cell Voltage Min   : %.3f V\n", acu_data.low_voltage);
    Serial.printf("Cell Voltage Avg   : %.3f V\n", acu_data.average_voltage);
    Serial.printf("Cell Voltage Delta : %.3f V\n", acu_data.high_voltage - acu_data.low_voltage);
    Serial.printf("Pack Voltage       : %.2f V\n", acu_data.total_voltage);
    Serial.println();

    /* Temperature Information */
    Serial.printf("Max Cell Temp      : %.2f C\n", acu_data.max_cell_temp);
    Serial.printf("Min Cell Temp      : %.2f C\n", acu_data.min_cell_temp);
    Serial.printf("Max Board Temp     : %.2f C\n", acu_data.max_board_temp);
    Serial.println();

    /* Charge Current Information */
    Serial.printf("Charger Current    : %.2f A\n", charger_data.output_current_low);
    Serial.printf("Calc Charge Curr   : %.2f A\n", MainChargeSystemInstance::instance().get_charge_current());
    Serial.println();


    /* Charge Information */
    Serial.println();
    Serial.printf("CP PWM   : %.2f V   %5.1f%%\n", level2_data.control_pwm, level2_data.control_pwm_duty_cycle);

    // Serial.print("CP Voltage Sense      ");
    // Serial.print(ADCInterfaceInstance::instance().read_control_pilot());
    // Serial.print("        ");
    // Serial.println(Level2InterfaceInstance::instance().getLevel2Data().cp_v_voltage);

    // Serial.print("PP Voltage Sense      ");
    // Serial.print(Level2InterfaceInstance::instance().getLevel2Data().pp_v_raw);
    // Serial.print("        ");
    // Serial.println(Level2InterfaceInstance::instance().getLevel2Data().pp_v_voltage);


   /* SHDN Information */
    Serial.println();
    Serial.printf("SHDN_A : %s\n", ADCInterfaceInstance::instance().read_shdn_A_voltage() ? "HIGH" : "LOW");
    Serial.printf("SHDN_B : %s\n", ADCInterfaceInstance::instance().read_shdn_B_voltage() ? "HIGH" : "LOW");
    Serial.printf("SHDN_C : %s\n", ADCInterfaceInstance::instance().read_shdn_C_voltage() ? "HIGH" : "LOW");
    Serial.printf("SHDN_D : %s\n", ADCInterfaceInstance::instance().read_shdn_D_voltage() ? "HIGH" : "LOW");
    Serial.printf("SHDN_E : %s\n", ADCInterfaceInstance::instance().read_shdn_E_voltage() ? "HIGH" : "LOW");
    Serial.printf("SHDN_F : %s\n", ADCInterfaceInstance::instance().read_shdn_F_voltage() ? "HIGH" : "LOW");
    Serial.printf("SHDN_G : %s\n", ADCInterfaceInstance::instance().read_shdn_G_voltage() ? "HIGH" : "LOW");
    Serial.println();

   return HT_TASK::TaskResponse::YIELD;
}
