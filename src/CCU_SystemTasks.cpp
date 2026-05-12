#include "CCU_SystemTasks.h"


bool initialize_all_systems()
{
    // Create Level2System instance
    Level2SystemInstance::create(
        Level2InterfaceInstance::instance(),
        ADCInterfaceInstance::instance(),
        WatchdogInterfaceInstance::instance(),
        Level2SystemThresholds_s{}
    );

    // Create MainChargeSystem instance
    MainChargeSystemInstance::create();

    /* State Machine Initialization */

    /* Delegate Function Definitions */
    etl::delegate<bool()> is_120_conditions_ok = etl::delegate<bool()>::create([]() -> bool
                                                                                { return Level2SystemInstance::instance().check_120_conditions(ADCInterfaceInstance::instance()); });

    etl::delegate<bool()> is_120_switched = etl::delegate<bool()>::create([]() -> bool
                                                                                { return Level2SystemInstance::instance().is_120_switched(ADCInterfaceInstance::instance()); });

    etl::delegate<bool()> is_240_switched = etl::delegate<bool()>::create([]() -> bool
                                                                                { return Level2SystemInstance::instance().is_240_switched(ADCInterfaceInstance::instance()); });

    etl::delegate<bool()> is_state_B2_ready = etl::delegate<bool()>::create([]() -> bool
                                                                                { return Level2SystemInstance::instance().check_state_B2_conditions(ADCInterfaceInstance::instance(), Level2InterfaceInstance::instance()); });

    etl::delegate<bool()> is_state_C2_ready = etl::delegate<bool()>::create([]() -> bool
                                                                                { return Level2SystemInstance::instance().check_state_C2_conditions(ADCInterfaceInstance::instance(), Level2InterfaceInstance::instance()); });

        etl::delegate<bool()> is_shdn_C_high = etl::delegate<bool()>::create([]() -> bool
                                                                                { return Level2SystemInstance::instance().is_shdn_C_valid(ADCInterfaceInstance::instance()); });

    etl::delegate<void()> set_sw_shdn_high = etl::delegate<void()>::create([]() -> void
                                                                                { return WatchdogInterfaceInstance::instance().set_sw_not_ok_pin_high(); });

    etl::delegate<void()> set_sw_shdn_low = etl::delegate<void()>::create([]() -> void
                                                                                { return WatchdogInterfaceInstance::instance().set_sw_not_ok_pin_low(); });

    etl::delegate<void()> set_start_charge_high = etl::delegate<void()>::create([]() -> void
                                                                                { return Level2InterfaceInstance::instance().set_start_charge(HIGH); });

    etl::delegate<void()> set_start_charge_low = etl::delegate<void()>::create([]() -> void
                                                                                { return Level2InterfaceInstance::instance().set_start_charge(LOW); });
    ChargerStateMachineInstance::create(is_120_conditions_ok,
                                    is_120_switched,
                                    is_240_switched,
                                    is_state_B2_ready,
                                    is_state_C2_ready,
                                    is_shdn_C_high,
                                    set_sw_shdn_high,
                                    set_sw_shdn_low,
                                    set_start_charge_high,
                                    set_start_charge_low,
                                    sys_time::hal_millis());

    return true;


}


HT_TASK::TaskResponse tick_state_machine(const unsigned long &sysMicros, const HT_TASK::TaskInfo &taskInfo) {

    ChargerStateMachineInstance::instance().tick_state_machine(sys_time::hal_millis());
    return HT_TASK::TaskResponse::YIELD;
}

HT_TASK::TaskResponse calculate_charge_current(const unsigned long& sysMicros, const HT_TASK::TaskInfo& taskInfo) {

    bool is_balancing_enabled = false;

    MainChargeSystemInstance::instance().calculate_charge_current(
        CCUConstants::MAX_PACK_VOLTAGE,
        CCUConstants::CUTOFF_VOLTAGE,
        CCUConstants::CHARGER_CURRENT_MAX,
        is_balancing_enabled  // Will be updated by the function
    );

    return HT_TASK::TaskResponse::YIELD;
}