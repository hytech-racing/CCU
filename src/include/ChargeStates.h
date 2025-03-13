#ifndef __CHARGESTATES_H__
#define __CHARGESTATES_H__

enum ChargeStates {
    INITIAL, //not charging
    NO_BALANCING, //charging but no balancing
    BALANCING //charging with balancing
};
#endif