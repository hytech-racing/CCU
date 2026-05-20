#include "MainChargeSystem.h"
#include <algorithm>
#include <cmath>


void MainChargeSystem::init(uint32_t init_millis)
{
    _init_millis = init_millis;
}

void MainChargeSystem::calculate_charge_current(float max_pack_voltage, float cell_cutoff_voltage, uint32_t curr_time_ms)
{
    // Get battery data from ACU
    const auto& acu_data = ACUInterfaceInstance::instance().get_latest_data();
    float max_cell_voltage = acu_data.high_voltage; // the highest voltage in any of the cells
    float total_pack_voltage = acu_data.total_voltage; // the total voltage in the pack
    auto current_state = ChargerStateMachineInstance::instance().get_state();

    uint32_t elapsed_time_ms = curr_time_ms - _init_millis;

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
    float requested_current = _get_current_for_state(current_state);

    // Apply safety limits
    _charge_data.calculated_charge_current = _apply_current_limits(current_state, requested_current, elapsed_time_ms);
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

float MainChargeSystem::_apply_current_limits(ChargerState_e state, float requested_current, uint32_t curr_time_ms)
{
    float limited_current = requested_current;

    const auto& acu_data = ACUInterfaceInstance::instance().get_latest_data();
    float curr_max_cell_temp = acu_data.max_cell_temp;
    float curr_max_board_temp = acu_data.max_board_temp;


    // Cell temp derate (stop completely at 45°C, 40°C start derating)
    float cell_temp_factor = _calculate_cell_temp_derate_factor(curr_max_cell_temp);

    // Board temper derate (stop completely 60°C, 50°C start derating)
    float board_temp_factor = _calculate_board_temp_derate_factor(curr_max_board_temp);

    // Startup derate
    float startup_delay_factor =  _startup_derate_factor(curr_time_ms);

    // Apply all derating factors
    limited_current *= startup_delay_factor;
    limited_current *= std::min(cell_temp_factor, board_temp_factor);

    return std::max(0.0F,limited_current);
}

float MainChargeSystem::_get_current_for_state(ChargerState_e state)
{
    switch (state)
    {
        case ChargerState_e::CHARGING_120:
        {
            // 120V Charging, max set at 3.5 amps
            return _charge_system_parameters.max_120V_current_amp;
        }
        case ChargerState_e::CHARGING_240:
        {
            // 240V charging, max set at 11 amps
            return _charge_system_parameters.max_240V_current_amp;
        }
        default:
        {
            return 0.0F;
        }
    }
}

float MainChargeSystem::_calculate_cell_temp_derate_factor(float curr_temp)
{
    if (curr_temp < _charge_system_parameters.thresholds.cell_temp_derate_thresh) {return 1.0F;}  // No derating
    if (curr_temp >= _charge_system_parameters.max_cell_cutoff_temp_celcius) {return 0.0F;}   // Stop charging immediatly if above max threshold

    return 1.0F - std::max(std::min(((curr_temp - _charge_system_parameters.thresholds.cell_temp_derate_thresh) / (_charge_system_parameters.max_cell_cutoff_temp_celcius - _charge_system_parameters.thresholds.cell_temp_derate_thresh)), 1.0F), 0.0F);
}

float MainChargeSystem::_calculate_board_temp_derate_factor(float curr_temp)
{
    if (curr_temp < _charge_system_parameters.thresholds.board_temp_derate_thresh) {return 1.0F;}  // No derating
    if (curr_temp >= _charge_system_parameters.max_board_cutoff_temp_celcius) {return 0.0F;}   // Stop charging immediatly if above max threshold

    return 1.0F - std::max(std::min(((curr_temp - _charge_system_parameters.thresholds.board_temp_derate_thresh) / (_charge_system_parameters.max_board_cutoff_temp_celcius - _charge_system_parameters.thresholds.board_temp_derate_thresh)), 1.0F), 0.0F);
}

float MainChargeSystem::_startup_derate_factor(uint16_t elapsed_time_ms)
{
    if (elapsed_time_ms < _charge_system_parameters.configs.startup_delay_ms)
    {
        return std::max(std::min((float)((float)(elapsed_time_ms - 0) / (_charge_system_parameters.configs.startup_delay_ms - 0)), 1.0F), 0.0F);
    }

    return 1.0F;
}

// float MainChargeSystem::_calculate_voltage_derate_factor(float curr_voltage)
// {
//     // Voltage derate (start peak of trapezoid at 470V (3.67), start derating at 500V (4V), stop completely 525V (4.17V))
//     // Below 3.7V: min current, 3.7V-4.0V: ramp up, above 4.0V: ramp down

//     // Below lower threshold we want to ramp
//     // Cell Voltage Region: Starting -> 3.6V, thus span is 5 degrees calculate factor using percentage of span
//     if (curr_voltage < _thresholds.cell_voltage_derate_lower_thresh)
//     {
//         return std::max(std::min(((curr_voltage - _thresholds.min_cell_voltage) / (_thresholds.cell_voltage_derate_lower_thresh - _thresholds.min_cell_voltage)), 1.0F), 0.0F);
//     }
//     // Think about doing time based delay because it doesn't make sense to start at 0 amps if we are under the threshold.

//     if (curr_voltage > _thresholds.cell_voltage_derate_upper_thresh)
//     {
//         return 1.0F - std::max(std::min(((curr_voltage - _thresholds.cell_voltage_derate_upper_thresh) / (_thresholds.max_cell_voltage - _thresholds.cell_voltage_derate_upper_thresh)), 1.0F), 0.0F);
//     }

//     return 1.0F;
// }