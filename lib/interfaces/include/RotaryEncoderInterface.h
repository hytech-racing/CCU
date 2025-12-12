#ifndef ROTARYENCODERINTERFACE_H
#define ROTARYENCODERINTERFACE_H

#include <Arduino.h>
#include <Encoder.h>
#include "CCUData.h"

#include "etl/singleton.h"
#include <etl/delegate.h>

#define CLK 21 
#define DT 20 
#define SW 19 

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
    _ccu_data(ccu_data) {Serial.begin(9600);};

    void setupEncoder();
    void updateEncoder();
    static void isr1();
    void set_enc_value(int dt_value);

    bool isButtonPressed() const { return _encoder_data.state; };

private:
    rotary_encoder_s _encoder_data;
    CCUData &_ccu_data;
};

using RotaryEncoderInterfaceInstance = etl::singleton<RotaryEncoderInterface>;

#endif