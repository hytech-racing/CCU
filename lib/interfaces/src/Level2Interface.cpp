#include "Level2Interface.h"


void Level2Interface::init()
{
    pinMode(_pinout.teensy_control_pwm_sense_pin, INPUT);
    pinMode(_pinout.teensy_start_charge_pin, OUTPUT);
}

bool Level2Interface::_is_pwm_duty_cycle_valid()
{
    unsigned long highTime = pulseIn(_pinout.teensy_control_pwm_sense_pin, HIGH, 100000);
    unsigned long lowTime  = pulseIn(_pinout.teensy_control_pwm_sense_pin, LOW, 100000);
    // Returns the length of the pulse in microseconds
    // Returns 0 if no pulse starts

    if (highTime == 0 || lowTime == 0)
    {
        // Handle 0% or 100% duty cycle (no transitions detected)
        _readings.control_pwm_duty_cycle = digitalRead(_pinout.teensy_control_pwm_sense_pin) ? 100.0 : 0.0;
        return false;
    }

    // Calculate duty cycle
    _readings.control_pwm_duty_cycle = ((float) highTime / (highTime + lowTime)) * 100.0;

    // Check if in valid range (9.5% to 96.5%)
    return (_readings.control_pwm_duty_cycle > 9.5 && _readings.control_pwm_duty_cycle < 96.5);
}

void Level2Interface::set_start_charge(bool state)
{
    digitalWrite(_pinout.teensy_start_charge_pin, state);
}

Level2_Data_s Level2Interface::getLevel2Data() const
{
    return _readings;
}