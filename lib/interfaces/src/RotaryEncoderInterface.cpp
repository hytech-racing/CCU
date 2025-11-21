#include "RotaryEncoderInterface.h"
#include "CCUData.h"


const int bounce_delay = 50; //Found based on research, subject to change

void RotaryEncoderInterface::isr1() {
    int enc_b_value = digitalRead(DT); 
    RotaryEncoderInterfaceInstance::instance().set_enc_value(enc_b_value);
}

void RotaryEncoderInterface::set_enc_value(int enc_b_value) {
    if (enc_b_value == HIGH) {
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

    attachInterrupt(digitalPinToInterrupt(DT), RotaryEncoderInterface::isr1, FALLING);
}

void RotaryEncoderInterface::updateEncoder() {
    static float prev_value = -1;
    int btn_state = digitalRead(SW);

    _ccu_data.encoder_value = _encoder_data.encoder_value;

    if (_encoder_data.encoder_value != prev_value) {
        Serial.print("Current value: ");
        Serial.println(_encoder_data.encoder_value);
    }
    prev_value = _encoder_data.encoder_value;

    if (btn_state == LOW) {
        if (millis() - _encoder_data.last_button_press > bounce_delay) {
            _encoder_data.state = !_encoder_data.state;
            Serial.println("Button pressed!");
        }
        _encoder_data.last_button_press = millis();
    }
}