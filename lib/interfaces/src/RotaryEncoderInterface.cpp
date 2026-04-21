#include "RotaryEncoderInterface.h"
#include "CCUData.h"

// Encoder myEncoder(21, 20);
// instantiate new_pos as a long in the struct?
// instantiate position as a long in the struct?


const int bounce_delay = 100; //Worked best during testing to minimize switch bouncing
unsigned long last_interrupt_time = 0;

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

void RotaryEncoderInterface::setup_encoder() {
    _encoder_data.encoder_value = 0;
    // static float position = 0;
    _encoder_data.state = false;
    pinMode(CLK, INPUT_PULLUP);
    pinMode(DT, INPUT_PULLUP);
    pinMode(SW, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(CLK), RotaryEncoderInterface::isr1, FALLING);
}

void RotaryEncoderInterface::update_encoder() {
    static float prev_value = -1;
    int btn_state = digitalRead(SW);
    int charger_state = static_cast<int> (_ccu_data.charging_state);

    _ccu_data.encoder_value = _encoder_data.encoder_value;

    // new_pos = myEncoder.read();
    if ((_encoder_data.state == true) && (_encoder_data.encoder_value != prev_value)) {
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
            Serial.println(_encoder_data.state);

            if (_encoder_data.state == false) {
              _encoder_data.encoder_value = 0;
              //myEncoder.write(0);
            } else {
              interrupts();
            }
        }
        _encoder_data.last_button_press = millis();
  }

  // if ((_encoder_data.state == true) && (position != new_pos) && (new_pos >= 0) && (new_pos <= 120)) {
  //      Serial.print("Current value: ");
  //      Serial.println(_encoder_data.encoder_value);
  //      Serial.println(_ccu_data.encoder_value);
  //      Serial.println(_ccu_data.calculated_charge_current);
  //      Serial.println(charger_state);
  //      _encoder_data.encoder_value = new_pos;
  //      _ccu_data.encoder_value = new_pos;
  //      position = new_pos;
  // } else if ((_encoder_data.state == true) && (position != new_pos) && (new_pos < 0)) {
  //      myEncoder.write(0);
  //      _encoder_data.encoder_value = 0;
  //      _ccu_data.encoder_value = 0;
  //      position = 0;
  //      Serial.print("Current value: ");
  //      Serial.println(_encoder_data.encoder_value);
  //      Serial.println(_ccu_data.encoder_value);
  //      Serial.println(_ccu_data.calculated_charge_current);
  //      Serial.println(charger_state);
  // } else if ((_encoder_data.state == true) && (position != new_pos) && (new_pos > 120)) {
  //      myEncoder.write(120);
  //      _encoder_data.encoder_value = 120;
  //      _ccu_data.encoder_value = 120;
  //      position = 120;
  //      Serial.print("Current value: ");
  //      Serial.println(_encoder_data.encoder_value);
  //      Serial.println(_ccu_data.encoder_value);
  //      Serial.println(_ccu_data.calculated_charge_current);
  //      Serial.println(charger_state);
  // }
}