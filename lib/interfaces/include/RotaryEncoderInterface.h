#ifndef ROTARYENCODERINTERFACE_H
#define ROTARYENCODERINTERFACE_H

#include <Arduino.h>
#include <stdint.h>
#include <stddef.h>

#include "ButtonInterface.h"

using pin = size_t;

namespace default_encoder_params
{
    constexpr float INIT_ENCODER_VALUE = 100.F;
    constexpr float MAX_VALUE = 100.F;
    constexpr float MIN_VALUE = 100.F;
    constexpr float STEP_SIZE = 1.F;
    constexpr uint8_t INIT_ENCODING = 0b00;

    // Transition Keys
    constexpr uint8_t CW_1 = 0b1101;
    constexpr uint8_t CW_2 = 0b0100;
    constexpr uint8_t CW_3 = 0b0010;
    constexpr uint8_t CW_4 = 0b1011;
    constexpr uint8_t CCW_1 = 0b1110;
    constexpr uint8_t CCW_2 = 0b0111;
    constexpr uint8_t CCW_3 = 0b0001;
    constexpr uint8_t CCW_4 = 0b1000;
}

struct RotaryEncoderPinout_s
{
    pin enc_switch_pin;
    pin enc_a_pin;
    pin enc_b_pin;
};

struct RotaryEncoderState_s
{
    float encoder_value;
    float max_value;
    float min_value;
    float step;
    uint8_t last_encoded;
};

class RotaryEncoderInterface
{
public:
    RotaryEncoderInterface(
        RotaryEncoderPinout_s pinout,
        RotaryEncoderState_s state = {
            .encoder_value = default_encoder_params::INIT_ENCODER_VALUE,
            .max_value = default_encoder_params::MAX_VALUE,
            .min_value = default_encoder_params::MIN_VALUE,
            .step = default_encoder_params::STEP_SIZE,
            .last_encoded = default_encoder_params::INIT_ENCODING,
        }
    ) :
        _pinout(pinout),
        _state(state),
        _enc_switch_button(pinout.enc_switch_pin)
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