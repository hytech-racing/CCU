#include "ChargerStateMachine.h"


//logic for changing states - still need to account for dial_position
void ChargerStateMachine::tick_state_machine(ChargerState_e& _current_state, bool balancing_enabled, int dial_position, bool start_button_pressed, unsigned long current_millis) 
{
    switch (_current_state) //takes in the _current_state variables and matches it to each case
    {
        case ChargerState_e::INITIAL:
        {
            if (start_button_pressed) {
                set_state(ChargerState_e::CHARGING_NO_BALANCING, current_millis);
                break;
            }

            if (balancing_enabled) {
                set_state(ChargerState_e::CHARGING_WITH_BALANCING, current_millis);
                break;
            }

            // Code that must run in INITIAL state (sending CAN messages, checking exit conditions)

            break;

        }

        case ChargerState_e::CHARGING_WITH_BALANCING:
        {
            if (!balancing_enabled) {
                set_state(ChargerState_e::CHARGING_NO_BALANCING, current_millis);
                break;
            } 

            // Code that must run in CHARGING_WITH_BALANCING state (sending CAN messages, checking for exit condition, etc)

            break;
        }

        case ChargerState_e::CHARGING_NO_BALANCING:
        {
            if (balancing_enabled) {
                set_state(ChargerState_e::CHARGING_WITH_BALANCING, current_millis);
                break;

            } else {
                set_state(ChargerState_e::CHARGING_NO_BALANCING, current_millis);
                break;
            }

            // Code that must run in CHARGING_NO_BALANCING state

        }
        default: // Should never occur
        {
            break;
        }

    }

}

void ChargerStateMachine::set_state(ChargerState_e new_state, unsigned long current_millis) 
{
    handle_exit_logic(_current_state, current_millis);
    _current_state = new_state;
    handle_entry_logic(_current_state, current_millis);
    
}

//reset each state as you leave it
void ChargerStateMachine::handle_exit_logic(ChargerState_e prev_state, unsigned long current_millis)
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
void ChargerStateMachine::handle_entry_logic(ChargerState_e new_state, unsigned long current_millis)
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

