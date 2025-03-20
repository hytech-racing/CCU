#ifndef __CHARGESTATES_H__
#define __CHARGESTATES_H__

enum class ChargeStates {
    INITIAL, //not charging
    CHARGING_NO_BALANCING, //charging but no balancing
    BALANCING //charging with balancing
};

ChargeStates change_state(ChargeStates current_state, bool balancing_enabled, int dial_position);


#endif