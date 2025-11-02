#include "RotaryEncoderInterface.h"
#include "CCUData.h"



static void RotaryEncoderInterface::isr1() {
    int dt_value = digitalRead(DT);
    RotaryEncoderInterfaceInstance::instance().set_enc_value(dt_value);
}

void RotaryEncoderInterface::set_enc_value(int dt_value) {
    if (dt_value == HIGH) {
      if (_encoder_data.encoder_value < _encoder_data.max_value) {
        _encoder_data.encoder_value++;
      }
    } else {
      if (_encoder_data.encoder_value > _encoder_data.min_value) {
        _encoder_data.encoder_value--;
      }
    }
}

void RotaryEncoderInterface::setupEncoder() {
    _encoder_data.encoder_value = 0;
    _encoder_data.state = false;
    Serial.begin(9600);
    pinMode(CLK, INPUT_PULLUP);
    pinMode(DT, INPUT_PULLUP);
    pinMode(SW, INPUT_PULLUP);

    attachInterrupt(digitalPinToInterrupt(2), RotaryEncoderInterface::isr1, FALLING);
}

void RotaryEncoderInterface::updateEncoder() {
    static int prev_value = -1;

    int btn_state = digitalRead(SW);

    noInterrupts();
    int current_value = _encoder_data.encoder_value;
    _ccu_data.encoder_value = current_value;
    interrupts();

    if (current_value != prev_value) {
         Serial.println(current_value);
    }
    prev_value = current_value;

    if (btn_state == LOW) {
        if (millis() - _encoder_data.last_button_press > 50) {
            _encoder_data.state = true; //or = !_encoder_data.state
            Serial.println("Button pressed");
        }
        _encoder_data.last_button_press = millis();
    }
}