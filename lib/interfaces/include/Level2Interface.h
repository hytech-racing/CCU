#ifndef LEVEL2INTERFACE_H
#define LEVEL2INTERFACE_H
//this is the interface for "240V" charging
//called level 2 because that is what SAE defines it as

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

    uint16_t cp_v_raw;
    uint16_t cp_pwm_raw;
    uint16_t pp_v_raw;
    float cp_v_voltage;
    float cp_pwm_voltage;
    float pp_v_voltage;
    static constexpr float ADC_REF_VOLTAGE = 3.3f;
    static constexpr float ADC_MAX_COUNT   = 4095.0f;

    CCUData &_ccu_data;

public:
    Level2Interface(
        CCUData &_ccu_data,
        pin cp_v = LEVEL2_PARAMS::CONTROL_V_SENSE,
        pin cp_pwm = LEVEL2_PARAMS::CONTROL_PWM_SENSE,
        pin pp_v = LEVEL2_PARAMS::PROXIMITY_SENSE,
        pin sc = LEVEL2_PARAMS::START_CHARGE) :
            teensy_cp_v(cp_v),
            teensy_cp_pwm(cp_pwm),
            teensy_pp_v(pp_v),
            enabled(_ccu_data.level_2_enabled),
            teensy_start_charge(sc)
    {};
    
    void init();
    void toggle_240_charging();
    void check_charge_condition();
    void read_pin_vals();
    float readPeakVoltage(pin p, uint32_t window_us = 3000);


};

#endif