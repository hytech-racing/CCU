#ifndef Level2Interface
#define Level2Interface

#include <etl/singleton.h>
#include <Arduino.h>
#include "CCUData.h"

using pin = size_t;


/* 240V Charging Constants */
namespace LEVEL2_PARAMS {

    constexpr const pin CONTROL_V_SENSE = 37; //pin to read voltage on CP line
    constexpr const pin CONTROL_PWM_SENSE = 29; // pin to read PWM signal from CP
    constexpr const pin PROXIMITY_SENSE = 15; // pin to read voltage on PP
    constexpr const pin START_CHARGE = 32; //pin used to control start charging fet

};

class Level2Interface
{
private:
    pin teensy_cp_v;
    pin teensy_cp_pwm;
    pin teensy_pp_v;
    bool enabled;
    pin teensy_start_charge;

    constexpr float ADC_REF_VOLTAGE = 3.3f;
    constexpr float ADC_MAX_COUNT   = 4095.0f;

public:
    Level2Interface(
        pin cp_v = LEVEL2_PARAMS::CONTROL_V_SENSE,
        pin cp_pwm = LEVEL2_PARAMS::CONTROL_PWM_SENSE,
        pin pp_v = LEVEL2_PARAMS::PROXIMITY_SENSE,
        pin sc = LEVEL2_PARAMS::START_CHARGE) :
            teensy_cp_v(cp_v),
            teensy_cp_pwm(cp_pwm),
            teensy_pp_v(pp_v),
            enabled(CCUData.level_2_enabled),
            teensy_start_charge(sc)
    {};
    
    void init();
    void toggle_240_charging();
    void check_charge_condition();


}