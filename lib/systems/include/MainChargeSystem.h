#ifndef MAINCHARGE_H
#define MAINCHARGE_H

/* External Dependencies */
#include "SharedFirmwareTypes.h"

/* Local System Includes */
#include "ChargerStateMachine.h"
#include "Level2System.h"

/* Local Interface Includes */
#include "ACUInterface.h"
#include "ADCInterface.h"
#include "Level2Interface.h"
#include "SystemTimeInterface.h"
#include "WatchdogInterface.h"

#ifdef TEENSY_OPT_SMALLEST_CODE
#include <Arduino.h>
#endif

#ifdef TESTING_SYSTEMS
#include "mockArduino.h"
#endif

enum BalancingState_e
{
    NOT_BALANCING = 0,
    BALANCING
};

namespace charge_system_default_parameters
{
    const float _MAX_120V_CURRENT_AMP = 3.5;  // 3.5 amps is 35 in the charger CAN format
    const float _MAX_240V_CURRENT_AMP = 5.0; // 11 amps is 110 in the charger CAN format
};

struct ChargeSystemData_s
{
    float calculated_charge_current;
    ChargerState_e current_charger_state;
};

class MainChargeSystem {
    public:
        MainChargeSystem(float max_120V_current_amp = charge_system_default_parameters::_MAX_120V_CURRENT_AMP, float max_240V_current_amp = charge_system_default_parameters::_MAX_240V_CURRENT_AMP) :
            _max_120V_current_amp(max_120V_current_amp),
            _max_240V_current_amp(max_240V_current_amp)
        {
            _charge_data.calculated_charge_current = 0.0F;
        }

        /**
         * @brief Calculate and set the charge current based on cell state and charger state
         * @param max_pack_voltage Maximum allowable pack voltage
         * @param cell_cutoff_voltage Voltage to stop charging at
         * @param charger_current_max Maximum current (will be scaled based on 120V vs 240V state)
         */
        void calculate_charge_current(
            float max_pack_voltage,
            float cell_cutoff_voltage
        );

        /**
         * @brief Determine if cell balancing should be enabled
         * @param voltage_delta_threshold Voltage difference to trigger balancing (default 0.05V)
         * @param min_balance_voltage Minimum cell voltage to start balancing (default 3.0V)
         * @return true if balancing should be enabled
         */
        bool determine_balancing_state(
            ChargerState_e current_state,
            float voltage_delta_threshold = 0.02F,
            float min_balance_voltage = 3.0F
        );

        /**
         * @brief Get calculated charge current
         */
        float get_charge_current() const { return _charge_data.calculated_charge_current; }

        /**
         * @brief Get the current charge system data
         */
        const ChargeSystemData_s& get_charge_data() const { return _charge_data; }

    private:
        const float _max_120V_current_amp;
        const float _max_240V_current_amp;

        ChargeSystemData_s _charge_data;

        /**
         * @brief Check if it's safe to charge based on safety systems
         */
        bool _is_safety_conditions_valid();

        // /**
        //  * @brief Apply current limiting based on temperature and other factors
        //  */
        float _apply_current_limits(ChargerState_e state, float requested_current);

        /**
         * @brief Get appropriate current based on charger state
         */
        float _get_current_for_state(ChargerState_e state);
};

using MainChargeSystemInstance = etl::singleton<MainChargeSystem>;

#endif