#ifndef CHARGESTATES_H
#define CHARGESTATES_H

enum ChargeStates {
    INITIAL, //not charging
    CHARGING_NO_BALANCING, //charging but no balancing
    BALANCING //charging with balancing
};
#endif