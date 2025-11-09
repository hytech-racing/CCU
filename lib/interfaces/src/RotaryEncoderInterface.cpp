#include "RotaryEncoderInterface.h"
#include "CCUData.h"

const int bounce_delay = 50;

void RotaryEncoderInterface::isr1() {
    int dt_value = digitalRead(DT);
    RotaryEncoderInterfaceInstance::instance().set_enc_value(dt_value);
}

void RotaryEncoderInterface::set_enc_value(int dt_value) {
    if (dt_value == HIGH) {
      if (_encoder_data.encoder_value < _encoder_data.max_value) {
        _encoder_data.encoder_value += 1.0;
      }
    } else {
      if (_encoder_data.encoder_value > _encoder_data.min_value) {
        _encoder_data.encoder_value -= 1.0;
      }
    }
}

void RotaryEncoderInterface::setupEncoder() {
    _encoder_data.encoder_value = 0;
    _encoder_data.state = false;
    pinMode(CLK, INPUT_PULLUP);
    pinMode(DT, INPUT_PULLUP);
    pinMode(SW, INPUT_PULLUP);

    attachInterrupt(digitalPinToInterrupt(2), RotaryEncoderInterface::isr1, FALLING);
}

void RotaryEncoderInterface::updateEncoder() {
    int btn_state = digitalRead(SW);

    noInterrupts();
    float current_value = _encoder_data.encoder_value;
    _ccu_data.encoder_value = current_value;
    interrupts();

    if (btn_state == LOW) {
        if (millis() - _encoder_data.last_button_press > bounce_delay) {
            _encoder_data.state = !_encoder_data.state;
        }
        _encoder_data.last_button_press = millis();
    }
}