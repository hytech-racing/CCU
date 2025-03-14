#ifndef __CHARGESTATES_H__
#define __CHARGESTATES_H__

enum ChargeStates {
    INITIAL, //not charging
    CHARGING_NO_BALANCING, //charging but no balancing
    BALANCING //charging with balancing
};
#endif