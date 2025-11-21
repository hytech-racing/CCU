#ifndef ROTARYENCODERINTERFACE_H
#define ROTARYENCODERINTERFACE_H

#include "CCUData.h"
#include "mockArduino.h"

#include "etl/singleton.h"
#include <etl/delegate.h>

#define CLK 2 //change based on actual pin used
#define DT 3 //change based on actual pin used
#define SW 4 //change based on actual pin used

struct rotary_encoder_s {
    volatile bool state = false;
    volatile float encoder_value = 0;
    unsigned long last_button_press = 0;
    const float max_value = 120;
    const float min_value = 0;
};

class RotaryEncoderInterface 
{
public:
    RotaryEncoderInterface(CCUData &ccu_data) :
    _ccu_data(ccu_data) {};

    inline void setupEncoder() {
        _encoder_data.encoder_value = 0;
        _encoder_data.state = false;
    }

    inline void updateEncoder() {
        // Sync internal encoder value to CCUData (matching real implementation)
        _ccu_data.encoder_value = _encoder_data.encoder_value;
    }

    inline void set_enc_value(int dt_value) {
        if (dt_value == HIGH) {
            if (_encoder_data.encoder_value < _encoder_data.max_value) {
                _encoder_data.encoder_value += 1.0f;
            }
        } else {
            if (_encoder_data.encoder_value > _encoder_data.min_value) {
                _encoder_data.encoder_value -= 1.0f;
            }
        }
    }

    bool isButtonPressed() const { return _encoder_data.state; };

private:
    rotary_encoder_s _encoder_data;
    CCUData &_ccu_data;
};

using RotaryEncoderInterfaceInstance = etl::singleton<RotaryEncoderInterface>;

#endif
