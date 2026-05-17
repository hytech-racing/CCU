#include "RotaryEncoderInterface.h"


void RotaryEncoderInterface::init()
{
    pinMode(_pinout.enc_a_pin, INPUT_PULLUP);
    pinMode(_pinout.enc_b_pin, INPUT_PULLUP);

    _state.last_encoded = _read_encoded();
}

void RotaryEncoderInterface::tick(unsigned long current_millis)
{
    _update_encoder();
    _enc_switch_button.update(current_millis);
}

float RotaryEncoderInterface::get_value() const
{
    return _state.encoder_value;
}

void RotaryEncoderInterface::set_value(float value)
{
    _state.encoder_value = _clamp(value);
}

void RotaryEncoderInterface::set_limits(float min_value, float max_value)
{
    _state.min_value = min_value;
    _state.max_value = max_value;
    _state.encoder_value = _clamp(_state.encoder_value);
}

void RotaryEncoderInterface::set_step(float step)
{
    _state.step = step;
}

bool RotaryEncoderInterface::switch_pressed()
{
    return _enc_switch_button.is_pressed();
}

bool RotaryEncoderInterface::switch_released()
{
    return _enc_switch_button.is_released();
}

bool RotaryEncoderInterface::switch_held()
{
    return _enc_switch_button.is_held();
}

uint8_t RotaryEncoderInterface::_read_encoded() const
{
    uint8_t a = digitalRead(_pinout.enc_a_pin);
    uint8_t b = digitalRead(_pinout.enc_b_pin);

    return (a << 1) | b;
}

void RotaryEncoderInterface::_update_encoder()
{
    uint8_t encoded = _read_encoded();

    if (encoded == _state.last_encoded)
    {
        return;
    }

    uint8_t transition = (_state.last_encoded << 2) | encoded;

    switch (transition)
    {
        // Clockwise transitions
        case 0b1101:
        case 0b0100:
        case 0b0010:
        case 0b1011:
            _increment();
            break;

        // Counter-clockwise transitions
        case 0b1110:
        case 0b0111:
        case 0b0001:
        case 0b1000:
            _decrement();
            break;

        default:
            // Invalid transition, likely bounce/noise.
            break;
    }

    _state.last_encoded = encoded;
}

void RotaryEncoderInterface::_increment()
{
    _state.encoder_value = _clamp(_state.encoder_value + _state.step);
}

void RotaryEncoderInterface::_decrement()
{
    _state.encoder_value = _clamp(_state.encoder_value - _state.step);
}

float RotaryEncoderInterface::_clamp(float value) const
{
    if (value > _state.max_value)
    {
        return _state.max_value;
    }

    if (value < _state.min_value)
    {
        return _state.min_value;
    }

    return value;
}