#include "ChargerStateMachine.h"

constexpr const int SHUTDOWN_LOW = 1;

//logic for changing states - still need to account for dial_position
ChargingState_e ChargerStateMachine::tick_state_machine(unsigned long current_millis) 
{
    const auto& latest_data = ACUInterfaceInstance::instance().get_latest_data();

    const float high_voltage = latest_data.high_voltage; //NOLINT
    const float total_voltage = latest_data.total_voltage; //NOLINT
    // acu_state comes from bms_status. If shutdown is low on ACU (HVP unplugged), acu_state = 1. Else if acu_state = 2, safe to charge.
    const bool acu_shutdown_low = latest_data.acu_state == SHUTDOWN_LOW;
    const bool shutdown_low = (digitalRead(_ccu_data.SHDN_E_READ) != HIGH); //e-stop on charge cart
    const bool voltage_reached = (high_voltage >= _ccu_data.cutoff_voltage) || (ACUInterfaceInstance::instance().get_latest_data().total_voltage > _ccu_data.max_pack_voltage); //NOLINT

    switch (_current_state) //takes in the _current_state variables and matches it to each case
    {
        case ChargingState_e::NOT_CHARGING:
        {
            //pinMode(_ccu_data.SHDN_E_READ, OUTPUT);
            _ccu_data.calculated_charge_current = 0;

            if (_ccu_data.charging_enabled && !shutdown_low && !acu_shutdown_low && !voltage_reached) {
                set_state(ChargingState_e::CHARGING, current_millis);
                break;
            }

            // Code that must run in NOT_CHARGING state (sending CAN messages, checking exit conditions)

            break;

        }

        case ChargingState_e::CHARGING:
        {
            _ccu_data.calculated_charge_current = _ccu_data.charger_current_max;

            if (_ccu_data.charging_enabled && !shutdown_low && !acu_shutdown_low && voltage_reached) {
                set_state(ChargingState_e::DONE_CHARGING, current_millis);
                break;
            } else if (!_ccu_data.charging_enabled || shutdown_low || acu_shutdown_low) {
                set_state(ChargingState_e::NOT_CHARGING, current_millis);
                break;
            }

            // Code that must run in CHARGING state (sending CAN messages, checking for exit condition, etc)

            break;
        }

        case ChargingState_e::DONE_CHARGING:
        {
            _ccu_data.charging_enabled = false;
            _ccu_data.calculated_charge_current = 0;

            // if (_ccu_data.charging_enabled) {
            //     set_state(ChargingState_e::CHARGING, current_millis);
            //     break;
            // }

            // Code that must run in DONE_CHARGING state

            break;
        }
        default: // Should never occur
        {
            break;
        }

    }
    return _current_state;
}

void ChargerStateMachine::set_state(ChargingState_e new_state, unsigned long current_millis) 
{
    handle_exit_logic(_current_state, current_millis);
    _current_state = new_state;
    handle_entry_logic(_current_state, current_millis);
    
}

//reset each state as you leave it
void ChargerStateMachine::handle_exit_logic(ChargingState_e prev_state, unsigned long current_millis)
{
    switch(prev_state)
    {
        case ChargingState_e::NOT_CHARGING:
        {
            //pinMode(_ccu_data.SHDN_E_READ, OUTPUT);
            break;
        }
        case ChargingState_e::DONE_CHARGING:
        {
            break;
        }
        case ChargingState_e::CHARGING:
        {
            break;
        }
        default: 
        {
            break;
        }
    }
}

//make sure each state is reset before you enter it
void ChargerStateMachine::handle_entry_logic(ChargingState_e new_state, unsigned long current_millis)
{
    switch(new_state)
    {
        case ChargingState_e::NOT_CHARGING:
        {
           // pinMode(_ccu_data.SHDN_E_READ, OUTPUT);
            break;
        }
        case ChargingState_e::DONE_CHARGING:
        {
            break;
        }
        case ChargingState_e::CHARGING:
        {
            break;
        }
        default:
        {
            break;
        }
    }
}

