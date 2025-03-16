#include "ChargeStates.h"


ChargeStates change_state(ChargeStates current_state, bool balancing_enabled, int dial_position) {
    //logic for changing states - still need to account for dial_position

    switch (current_state) {

        //would we need a boolean for charging enabled, to tell CCU to start/stop charging? otherwise, how does ccu know when to start/stop?
        
        case ChargeStates::INITIAL:
            if (balancing_enabled) {
                return current_state = ChargeStates::BALANCING;
            } else {
                return current_state = ChargeStates::CHARGING_NO_BALANCING; 
            }
        case ChargeStates::BALANCING:
            if (balancing_enabled) {
                return current_state = ChargeStates::BALANCING;
            } else {
                return current_state = ChargeStates::CHARGING_NO_BALANCING;
            }
        case ChargeStates::CHARGING_NO_BALANCING:
            if (balancing_enabled) {
                return current_state = ChargeStates::BALANCING;
            } else {
                return current_state = ChargeStates::CHARGING_NO_BALANCING;
            }
        default: 
            return current_state;
    }
}