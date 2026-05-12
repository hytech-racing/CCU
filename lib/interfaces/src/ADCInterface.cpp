#include "ADCInterface.h"

void ADCInterface::init(uint32_t init_millis)
{
    // Pin Configuration
    pinMode(_adc_parameters.pinout.teensy_shdn_A_pin, INPUT);
    pinMode(_adc_parameters.pinout.teensy_shdn_B_pin, INPUT);
    pinMode(_adc_parameters.pinout.teensy_shdn_C_pin, INPUT);
    pinMode(_adc_parameters.pinout.teensy_shdn_D_pin, INPUT);
    pinMode(_adc_parameters.pinout.teensy_shdn_E_pin, INPUT);
    pinMode(_adc_parameters.pinout.teensy_shdn_F_pin, INPUT);
    pinMode(_adc_parameters.pinout.teensy_shdn_G_pin, INPUT);
    pinMode(_adc_parameters.pinout.teensy_scaled_24V_pin, INPUT);
    pinMode(_adc_parameters.pinout.teensy_control_pilot_pin, INPUT);
    pinMode(_adc_parameters.pinout.teensy_proximity_pilot_pin, INPUT);

    _init_millis = init_millis;
}


bool ADCInterface::read_shdn_A_voltage()
{
    bool out = digitalRead(_adc_parameters.pinout.teensy_shdn_A_pin);
    return out;
}


bool ADCInterface::read_shdn_B_voltage()
{
    bool out = digitalRead(_adc_parameters.pinout.teensy_shdn_B_pin);
    return out;
}


bool ADCInterface::read_shdn_C_voltage()
{
    bool out = digitalRead(_adc_parameters.pinout.teensy_shdn_C_pin);
    return out;
}


bool ADCInterface::read_shdn_D_voltage()
{
    bool out = digitalRead(_adc_parameters.pinout.teensy_shdn_D_pin);
    return out;
}


bool ADCInterface::read_shdn_E_voltage()
{
    bool out = digitalRead(_adc_parameters.pinout.teensy_shdn_E_pin);
    return out;
}


bool ADCInterface::read_shdn_F_voltage()
{
    bool out = digitalRead(_adc_parameters.pinout.teensy_shdn_F_pin);
    return out;
}


bool ADCInterface::read_shdn_G_voltage()
{
    bool out = digitalRead(_adc_parameters.pinout.teensy_shdn_G_pin);
    return out;
}


volt ADCInterface::read_global_lv_value()
{
    volt data = static_cast<float>(analogRead(_adc_parameters.pinout.teensy_scaled_24V_pin)) * _adc_parameters.conversions.glv_conv_factor; // input before voltage divider (4.3k / (4.3k + 36k))
    return data;
}


volt ADCInterface::read_control_pilot()
{
    volt data = static_cast<float>(analogRead(_adc_parameters.pinout.teensy_control_pilot_pin)) * _adc_parameters.conversions.control_pilot_conv_factor;
    return data;
}


volt ADCInterface::read_proximity_pilot()
{
    volt data = static_cast<float>(analogRead(_adc_parameters.pinout.teensy_proximity_pilot_pin)) * _adc_parameters.conversions.proximity_pilot_conv_factor;
    return data;
}


bool ADCInterface::read_240_enabled()
{
    bool out = digitalRead(_adc_parameters.pinout.teensy_240_enabled_pin);
    return out;
}


bool ADCInterface::read_240_ok()
{
    bool out = digitalRead(_adc_parameters.pinout.teensy_240_ok_pin);
    return out;
}


volt ADCInterface::read_jumper_out()
{
    volt data = static_cast<float>(analogRead(_adc_parameters.pinout.teensy_jumper_out_pin)) * _adc_parameters.conversions.jumper_out_conv_factor;
    return data;
}

const ADCInterfaceParams_s& ADCInterface::get_adc_params() const
{
    return _adc_parameters;
}