#include "Level2Interface.h"


void Level2Interface::init() {
    pinMode(teensy_cp_v, INPUT);
    pinMode(teensy_cp_pwm, INPUT);
    pinMode(teensy_pp_v, INPUT);
    pinMode(teensy_start_charge, OUTPUT);
    digitalWrite(teensy_start_charge, LOW);
    analogReadResolution(12);
}
 
/**
 * to toggle 240V fet between on and off
 */
void Level2Interface::start_240_charging() {
    if (_ccu_data.level_2_ready) {
        digitalWrite(teensy_start_charge, HIGH);
        _ccu_data.level_2_enabled = true;
        Serial.println("writing toggle high");
    } 
    else 
    {
        digitalWrite(teensy_start_charge, LOW);
        _ccu_data.level_2_enabled = false;
        Serial.println("writing toggle low");
    }
}

/**
 * checking if we can go flip on the EVSE switch
 */
void Level2Interface::check_240_charge_condition() {
    return;
    read_pin_vals();

    //lets check if we are in 240V mode
    if (cp_v_voltage > 0.1) { //if 240 enabled is high, then we are
        if (cp_v_voltage >= 3.0) { //change 3.0  to the value of correct value
            //okay to start charge
            _ccu_data.level_2_ready = true;
        } else {
            _ccu_data.level_2_ready = false;
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
    Serial.printf("CP Voltage: %.2f", cp_v_voltage);
    Serial.printf("CP PWM: %.2f", cp_pwm_voltage);
    Serial.printf("PP Voltage: %.2f", pp_v_voltage);
}