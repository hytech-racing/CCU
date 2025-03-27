#include "ChargerStateMachine.h"


//logic for changing states - still need to account for dial_position
ChargerState_e ChargerStateMachine::evaluate_charger_state_machine(ChargerState_e& _current_state, bool balancing_enabled, int dial_position, bool start_button_pressed) 
{
    switch (_current_state) //takes in the _current_state variables and matches it to each case
    {
        case ChargerState_e::INITIAL:
        {
            if (start_button_pressed) {
                set_state(ChargerState_e::CHARGING_NO_BALANCING);
                break;
            }

            if (balancing_enabled) {
                set_state(ChargerState_e::CHARGING_WITH_BALANCING);
                break;
            }

            // Code that must run in INITIAL state (sending CAN messages, checking exit conditions)

            break;

        }

        case ChargerState_e::CHARGING_WITH_BALANCING:
        {
            if (!balancing_enabled) {
                set_state(ChargerState_e::CHARGING_NO_BALANCING);
                break;
            } 

            // Code that must run in CHARGING_WITH_BALANCING state (sending CAN messages, checking for exit condition, etc)

            break;
        }

        case ChargerState_e::CHARGING_NO_BALANCING:
        {
            if (balancing_enabled) {
                set_state(ChargerState_e::CHARGING_WITH_BALANCING);
                break;

            } else {
                set_state(ChargerState_e::CHARGING_NO_BALANCING);
                break;
            }

            // Code that must run in CHARGING_NO_BALANCING state

        }
        default: // Should never occur
        {
            break;
        }

    }
    return _current_state;
}

void ChargerStateMachine::set_state(ChargerState_e new_state) 
{
    handle_exit_logic(_current_state);
    _current_state = new_state;
    handle_entry_logic(_current_state);
    
}

//reset each state as you leave it
void ChargerStateMachine::handle_exit_logic(ChargerState_e prev_state)
{
    switch(prev_state)
    {
        case ChargerState_e::INITIAL:
        {
            break;
        }
        case ChargerState_e::CHARGING_NO_BALANCING:
        {
            break;
        }
        case ChargerState_e::CHARGING_WITH_BALANCING:
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
void ChargerStateMachine::handle_entry_logic(ChargerState_e new_state)
{
    switch(new_state)
    {
        case ChargerState_e::INITIAL:
        {
            break;
        }
        case ChargerState_e::CHARGING_NO_BALANCING:
        {
            break;
        }
        case ChargerState_e::CHARGING_WITH_BALANCING:
        {
            break;
        }
        default:
        {
            break;
        }
    }
}

