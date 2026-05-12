#include "Level2System.h"


bool Level2System::check_120_conditions(ADCInterface& adc_interface)
{
    if ((adc_interface.read_control_pilot() < 0.2) &&
        (adc_interface.read_proximity_pilot() > 4.8) &&
        (adc_interface.read_240_enabled() == HIGH) &&
        (adc_interface.read_240_ok() == LOW))
    {
        return true;
    }

    return false;
}

bool Level2System::is_120_switched(ADCInterface& adc_interface)
{
    if ((adc_interface.read_240_ok() == LOW) && (adc_interface.read_jumper_out() == HIGH))
    {
        return true;
    }

    return false;
}

bool Level2System::is_240_switched(ADCInterface& adc_interface)
{
    if ((adc_interface.read_240_ok() == LOW) && (adc_interface.read_jumper_out() == LOW))
    {
        return true;
    }

    return false;
}

bool Level2System::is_shdn_C_valid(ADCInterface& adc_interface)
{
    return adc_interface.read_shdn_C_voltage();
}

bool Level2System::check_state_B2_conditions(ADCInterface& adc_interface, Level2Interface& level2_interface)
{
    volt control_voltage = adc_interface.read_control_pilot();
    volt proximity_voltage = adc_interface.read_proximity_pilot();

    if (control_voltage > _thresholds.state_B2_control_voltage_min &&
        control_voltage < _thresholds.state_B2_control_voltage_max &&
        proximity_voltage > _thresholds.state_B2_proximity_voltage_min &&
        proximity_voltage < _thresholds.state_B2_proximity_voltage_max &&
        level2_interface._is_pwm_duty_cycle_valid())
    {
        return true;
    }

    return false;
}

bool Level2System::check_state_C2_conditions(ADCInterface& adc_interface, Level2Interface& level2_interface)
{
    volt control_voltage = adc_interface.read_control_pilot();
    volt proximity_voltage = adc_interface.read_proximity_pilot();

    if (control_voltage > _thresholds.state_C2_control_voltage_min &&
        control_voltage < _thresholds.state_C2_control_voltage_max &&
        proximity_voltage > _thresholds.state_C2_proximity_voltage_min &&
        proximity_voltage < _thresholds.state_C2_proximity_voltage_max &&
        level2_interface._is_pwm_duty_cycle_valid())
    {
        return true;
    }

    return false;
}