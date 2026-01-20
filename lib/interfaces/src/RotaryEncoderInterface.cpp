#include "RotaryEncoderInterface.h"
#include "CCUData.h"


const int bounce_delay = 100; //Worked best during testing to minimize switch bouncing
volatile unsigned long last_interrupt_time = 0;

void RotaryEncoderInterface::isr1() {
    unsigned long current_time = millis();
    if (current_time - last_interrupt_time > bounce_delay) {
      int enc_b_value = digitalRead(DT); 
      RotaryEncoderInterfaceInstance::instance().set_enc_value(enc_b_value);
      last_interrupt_time = current_time;
    }
    
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
    attachInterrupt(digitalPinToInterrupt(CLK), RotaryEncoderInterface::isr1, FALLING);
}

void RotaryEncoderInterface::updateEncoder() {
    static float prev_value = -1;
    int btn_state = digitalRead(SW);
    int charger_state = static_cast<int> (_ccu_data.charging_state);

    _ccu_data.encoder_value = _encoder_data.encoder_value;

    if (_encoder_data.encoder_value != prev_value) {
        Serial.print("Current value: ");
        Serial.println(_encoder_data.encoder_value);
        Serial.println(_ccu_data.encoder_value);
        Serial.println(_ccu_data.calculated_charge_current);
        Serial.println(charger_state);
    }
    prev_value = _encoder_data.encoder_value;

    if (btn_state == LOW) {
        if (millis() - _encoder_data.last_button_press > bounce_delay) {
            _encoder_data.state = !_encoder_data.state;
            Serial.println("Button pressed!");
            if (_encoder_data.state == false) {
              _encoder_data.encoder_value = 0;
            } else {
              interrupts();
            }
        }
        _encoder_data.last_button_press = millis();
    }
}