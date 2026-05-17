#include "MainChargeSystem.h"
#include <algorithm>
#include <cmath>

void MainChargeSystem::calculate_charge_current(float max_pack_voltage, float cell_cutoff_voltage, uint8_t dial_percent)
{
    // Get battery data from ACU
    const auto& acu_data = ACUInterfaceInstance::instance().get_latest_data();
    float max_cell_voltage = acu_data.high_voltage; // the highest voltage in any of the cells
    float total_pack_voltage = acu_data.pack_voltage; // the total voltage in the pack
    auto current_state = ChargerStateMachineInstance::instance().get_state();

    // Check safety conditions first
    if (!_is_safety_conditions_valid())
    {
        _charge_data.calculated_charge_current = 0.0F;
        return;
    }

    // Check if voltage limits reached/exceeded
    bool is_voltage_limit_exceeded = (max_cell_voltage >= cell_cutoff_voltage) || (total_pack_voltage > max_pack_voltage);

    if (is_voltage_limit_exceeded)
    {
        _charge_data.calculated_charge_current = 0.0F;
        return;
    }

    // Determine requested current based on state
    float requested_current = _get_current_for_state(current_state) * (static_cast<float>(dial_percent) / 100.0F);

    // Apply safety limits
    _charge_data.calculated_charge_current = _apply_current_limits(current_state, requested_current);
}

bool MainChargeSystem::_is_safety_conditions_valid()
{
    // Check BRB on charge cart (shutdown F is after BRB)
    bool is_shutdown_low = false;
    bool is_acu_shutdown_low = false;
    bool is_ccu_shutdown_low = false;

    is_shutdown_low = !ADCInterfaceInstance::instance().read_shdn_F_voltage();

    /**
     * Check ACU state: acu_state comes from the bms_status message. If shutdown is low on ACU (HVP is unplugged), acu_state = 3.
     * If acu_state = 2, we should/are safe to be charging
     * ACU States for Reference: STARTUP = 0, ACTIVE = 1, CHARGING = 2, FAULTED = 3, WELDED = 4, WELDCHECK = 5
     */
    is_acu_shutdown_low = ACUInterfaceInstance::instance().get_latest_data().acu_state != ACUState_e::CHARGING; //NOLINT

    // Check for error state from state machine
    is_ccu_shutdown_low = !(ChargerStateMachineInstance::instance().get_state() == ChargerState_e::CHARGING_120 ||
                                ChargerStateMachineInstance::instance().get_state() == ChargerState_e::CHARGING_240);

    if (is_shutdown_low || is_acu_shutdown_low || is_ccu_shutdown_low)
    {
        return false;
    }

    return true;
}

float MainChargeSystem::_apply_current_limits(ChargerState_e state, float requested_current)
{
    return std::max(0.0F,requested_current);
    // Temperature redundancy check? Derate check
}

float MainChargeSystem::_get_current_for_state(ChargerState_e state)
{
    switch (state)
    {
        case ChargerState_e::CHARGING_120:
        {
            // 120V Charging, max set at 3.5 amps
            return _max_120V_current_amp;
        }
        case ChargerState_e::CHARGING_240:
        {
            // 240V charging, max set at 11 amps
            return _max_240V_current_amp;
        }
        default:
        {
            return 0.0F;
        }
    }
}
