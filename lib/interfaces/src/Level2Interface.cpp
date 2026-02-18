#include "Level2Interface.h"


void Level2Interface::init() {
    pinMode(teensy_cp_v, INPUT);
    pinMode(teensy_cp_pwm, INPUT);
    pinMode(teensy_pp_v, INPUT);
    pinMode(teensy_start_charge, OUTPUT);
    digitalWrite(teensy_start_charge, LOW);
    analogReadResolution(12);
}

void Level2Interface::toggle_240_charging() {
    if (enabled) {
        digitalWrite(teensy_start_charge, HIGH);
        Serial.println("writing toggle high");
    } 
    else 
    {
        digitalWrite(teensy_start_charge, LOW);
        Serial.println("writing toggle low");
    }
}

bool Level2Interface::check_240_charge_condition() {
    read_pin_vals();

    //lets check if we are in 240V mode
    _ccu_data.level_2_enabled = (cp_v_voltage > 0.1); //not in 240V mode
    enabled = _ccu_data.level_2_enabled;
    if (enabled) {
        cp_v_voltage = readPeakVoltage(teensy_cp_v, 3000); // 3 ms window
        if (cp_v_voltage >= 3.0) {
            //okay to start charge
            return true;
        } else {
            return false;
        }
    }

}

void Level2Interface::read_pin_vals() {
    cp_v_raw  = analogRead(teensy_cp_v);
    cp_pwm_raw = analogRead(teensy_cp_pwm);
    pp_v_raw  = analogRead(teensy_pp_v);
    cp_v_voltage  = (cp_v_raw  * ADC_REF_VOLTAGE) / ADC_MAX_COUNT;
    cp_pwm_voltage = (cp_pwm_raw * ADC_REF_VOLTAGE) / ADC_MAX_COUNT;
    pp_v_voltage  = (pp_v_raw  * ADC_REF_VOLTAGE) / ADC_MAX_COUNT;

}

float Level2Interface::readPeakVoltage(pin p, uint32_t window_us = 3000) {
    const uint32_t start = micros();
    uint16_t peak = 0;

    while ((micros() - start) < window_us)
    {
        uint16_t v = analogRead(p);
        if (v > peak) peak = v;
    }

    // Convert ADC counts to volts (assuming 3.3V ADC reference and 12-bit)
    return (peak * ADC_REF_VOLTAGE) / ADC_MAX_COUNT;
}