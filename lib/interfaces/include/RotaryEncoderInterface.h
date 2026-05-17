#ifndef ROTARYENCODERINTERFACE_H
#define ROTARYENCODERINTERFACE_H

#include <Arduino.h>
#include <stdint.h>
#include <stddef.h>

#include "ButtonInterface.h"

using pin = size_t;

namespace default_encoder_params
{
    constexpr uint8_t ENCODER_VALUE = 100;
    constexpr uint8_t MAX_VALUE = 100;
    constexpr uint8_t MIN_VALUE = 100;
    constexpr uint8_t STEP_SIZE = 1;
    constexpr uint8_t INIT_ENCODING = 0b00;
}

struct RotaryEncoderPinout_s
{
    pin enc_switch_pin;
    pin enc_a_pin;
    pin enc_b_pin;
};

struct RotaryEncoderState_s
{
    uint8_t encoder_value;
    uint8_t max_value;
    uint8_t min_value;
    uint8_t step;
    uint8_t last_encoded;
};

class RotaryEncoderInterface
{
public:
    RotaryEncoderInterface(
        RotaryEncoderPinout_s pinout,
        RotaryEncoderState_s state = {
            .encoder_value = default_encoder_params::ENCODER_VALUE,
            .max_value = default_encoder_params::MAX_VALUE,
            .min_value = default_encoder_params::MIN_VALUE,
            .step = default_encoder_params::STEP_SIZE,
            .last_encoded = default_encoder_params::INIT_ENCODING,
        }
    ) : 
        _pinout(pinout),
        _state(state),
        _enc_switch_button(_pinout.enc_switch_pin)
    {}

    void init();

    void tick(unsigned long current_millis);

    float get_value() const;

    void set_value(float value);

    void set_limits(float min_value, float max_value);

    void set_step(float step);

    bool switch_pressed();

    bool switch_released();

    bool switch_held();
    
private:
    RotaryEncoderPinout_s _pinout;
    RotaryEncoderState_s _state;
    ButtonInterface _enc_switch_button;

    uint8_t _read_encoded() const;

    void _update_encoder();

    void _increment();

    void _decrement();

    float _clamp(float value) const;
};

using RotaryEncoderInterfaceInstance = etl::singleton<RotaryEncoderInterface>;

#endif