#include "MainChargeSystem.h"
#include <algorithm>
#include <cmath>

constexpr const int SHUTDOWN_LOW = 1;

void MainChargeSystem::calculate_charge_current() {
    float average_voltage = ACUInterfaceInstance::instance().get_latest_data().average_voltage; //NOLINT
    float low_voltage = ACUInterfaceInstance::instance().get_latest_data().low_voltage; //NOLINT
    float high_voltage = ACUInterfaceInstance::instance().get_latest_data().high_voltage; //NOLINT
    float total_voltage = ACUInterfaceInstance::instance().get_latest_data().total_voltage; //NOLINT

    

    
    
    if (shutdown_low || acu_shutdown_low)
    {
        _ccu_data.charging_state = ChargingState_e::NOT_CHARGING;
    } else if(voltage_reached)
    {
        _ccu_data.charging_state = ChargingState_e::DONE_CHARGING;
    } else {
        _ccu_data.charging_state = ChargingState_e::CHARGING;
    }
    

    /* Tells the charger to stop charging if the shutdown button is pressed or one of the cell voltages is too high */
    if (voltage_reached || shutdown_low || acu_shutdown_low) {  //ACU will cause a BMS fault if there is a cell or board temp that is too high
        _ccu_data.calculated_charge_current = 0;
        _ccu_data.charging_enabled = false;
    } else {
        _ccu_data.calculated_charge_current = _ccu_data.charger_current_max; // 120 = 3.4 amps
    } 
}
