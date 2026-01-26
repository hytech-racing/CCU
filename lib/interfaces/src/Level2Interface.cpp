#include "Level2Interface.h"

void Level2Interface::init() {
    pinMode(teensy_cp_v, INPUT);
    pinMode(teensy_cp_pwm, INPUT);
    pinMode(teensy_pp_v, INPUT);
    pinMode(teensy_start_charge, OUTPUT);
    digitalWrite(teensy_start_charge, LOW);
    analogReadResolution(12);
}

void toggle_240_charging() {
    if (enabled) {
        digitalWrite(teensy_start_charge, HIGH);
    } 
    else 
    {
        digitalWrite(teensy_start_charge, HIGH);
    }
}

void check_charge_condition() {
    uint16_t cp_v_raw  = analogRead(teensy_cp_v);
    uint16_t cp_pwm_raw = analogRead(teensy_cp_pwm);
    uint16_t pp_v_raw  = analogRead(teensy_pp_v);
    float cp_v_voltage  = (cp_v_raw  * ADC_REF_VOLTAGE) / ADC_MAX_COUNT;
    float cp_pwm_voltage = (cp_pwm_raw * ADC_REF_VOLTAGE) / ADC_MAX_COUNT;
    float pp_v_voltage  = (pp_v_raw  * ADC_REF_VOLTAGE) / ADC_MAX_COUNT;
    
    //lets check if we are in 240V mode
    CCUData.level_2_enabled = !(cp_v_voltage <= 0.1); //not in 240V mode
    
}