#include "MainChargeSystem.h"
#include <algorithm>
#include <cmath>

void MainChargeSystem::calculate_charge_current( float max_pack_voltage, float cutoff_voltage, float charger_current_max, bool is_balancing_enabled )
{
    // Get battery data from ACU
    const auto& acu_data = ACUInterfaceInstance::instance().get_latest_data();
    float average_voltage = acu_data.average_voltage; //average voltage across the cells
    float low_voltage = acu_data.low_voltage; //the lowest voltage in any of the cells
    float high_voltage = acu_data.high_voltage; //the highest voltage in any of the cells
    float total_voltage = acu_data.total_voltage; //the total voltage in the pack

    // Check safety conditions first
    if (!_is_safety_conditions_valid())
    {
        _charge_data.calculated_charge_current = 0.0F;
        _charge_data.is_balancing_enabled = false;
        is_balancing_enabled = false;
        return;
    }

    // Check if voltage limits reached/exceeded
    bool is_voltage_limit_exceeded = (high_voltage >= cutoff_voltage) || (total_voltage > max_pack_voltage);

    if (is_voltage_limit_exceeded)
    {
        _charge_data.calculated_charge_current = 0.0F;
        _charge_data.is_balancing_enabled = false;
        is_balancing_enabled = false;
        return;
    }

    ChargerState_e current_state = ChargerStateMachineInstance::instance().get_state();

    // Determine requested current based on state
    float requested_current = _get_current_for_state(current_state, charger_current_max);

    // Apply safety limits
    _charge_data.calculated_charge_current = _apply_current_limits(requested_current);

    // Update balancing state
    _charge_data.is_balancing_enabled = determine_balancing_state();
    is_balancing_enabled = _charge_data.is_balancing_enabled;
}

bool MainChargeSystem::determine_balancing_state(float voltage_delta_threshold, float min_balance_voltage)
{
    const auto& acu_data = ACUInterfaceInstance::instance().get_latest_data();

    // Calculate voltage delta (max - min)
    float voltage_delta = acu_data.high_voltage - acu_data.low_voltage;

    // Get current charger state
    ChargerState_e current_state = ChargerStateMachineInstance::instance().get_state();

    // Only balance if:
    // 1. All cells are above minimum safe voltage
    // 2. There's significant voltage imbalance
    // 3. We're not actively charging at high current (to avoid conflicts)
    // 4. We're in an active charging state
    bool cells_above_min = acu_data.low_voltage > min_balance_voltage;
    bool significant_imbalance = voltage_delta > voltage_delta_threshold;
    bool safe_current_for_balancing = _charge_data.calculated_charge_current < 5.0F;
    bool in_charge_state = (current_state == ChargerState_e::CHARGING_120) ||
                          (current_state == ChargerState_e::CHARGING_240);

    return cells_above_min && significant_imbalance &&
           safe_current_for_balancing && in_charge_state;
}

bool MainChargeSystem::_is_safety_conditions_valid()
{
    // Check E-stop on charge cart (shutdown E)
    bool is_shutdown_low = ( ADCInterfaceInstance::instance().read_shdn_E_voltage() != HIGH );

    /**
     * Check ACU state: acu_state comes from the bms_status message. If shutdown is low on ACU (HVP is unplugged), acu_state = 1.
     * If acu_state = 2, we should/are safe to be charging
     */
    bool is_acu_shutdown_low = ACUInterfaceInstance::instance().get_latest_data().acu_state == 1; //NOLINT

    // Check for error state from state machine
    ChargerState_e current_state = ChargerStateMachineInstance::instance().get_state();
    bool is_in_error_state = (current_state == ChargerState_e::ERROR);

    if (is_shutdown_low || is_acu_shutdown_low || is_in_error_state)
    {
        return false;
    }

    return true;
}

float MainChargeSystem::_apply_current_limits(float requested_current)
{
    // Never exceed maximum current
    float limited_current = std::min(requested_current, _MAXIMUM_NEVER_EXCEED_CURRENT);

    // Temperature redundancy check? Or does it get too hot at comp?

    // Ensure non-negative
    return std::max(0.0F, limited_current);
}

float MainChargeSystem::_get_current_for_state(ChargerState_e state, float charger_current_max)
{
    switch (state)
    {
        case ChargerState_e::CHARGING_120:
            // 120V Charging, max is ~4A
            return charger_current_max * 0.3F;  // Scale down for 120V = 3.6A

        case ChargerState_e::CHARGING_240:
            // Level 2 charging, can use full current ~12A
            return charger_current_max;

        case ChargerState_e::STARTUP:
        case ChargerState_e::CHECK_SWITCH:
        case ChargerState_e::CHARGE_120_UNLATCHED:
        case ChargerState_e::CHECK_240_B2_OK:
        case ChargerState_e::CHECK_240_C2_OK:
        case ChargerState_e::CHARGE_240_UNLATCHED:
        case ChargerState_e::ERROR:
        default:
            return 0.0F;
    }
}
