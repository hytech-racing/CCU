#include "ChargerStateMachine.h"


//logic for changing states - still need to account for dial_position
ChargingState_e ChargerStateMachine::tick_state_machine(unsigned long current_millis) 
{
    switch (_current_state) //takes in the _current_state variables and matches it to each case
    {
        case ChargingState_e::NOT_CHARGING:
        {
            //pinMode(_ccu_data.SHDN_E_READ, OUTPUT);

            if (_ccu_data.charging_enabled) {
                set_state(ChargingState_e::CHARGING, current_millis);
                break;
            }

            // Code that must run in NOT_CHARGING state (sending CAN messages, checking exit conditions)

            break;

        }

        case ChargingState_e::CHARGING:
        {
            if (!(_ccu_data.charging_enabled)) {
                set_state(ChargingState_e::DONE_CHARGING, current_millis);
                break;
            } 

            // Code that must run in CHARGING state (sending CAN messages, checking for exit condition, etc)

            break;
        }

        case ChargingState_e::DONE_CHARGING:
        {
            if (_ccu_data.charging_enabled) {
                set_state(ChargingState_e::CHARGING, current_millis);
                break;

            }

            // Code that must run in DONE_CHARGING state

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

