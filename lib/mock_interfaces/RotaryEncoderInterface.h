#ifndef ROTARYENCODERINTERFACE_H
#define ROTARYENCODERINTERFACE_H

// #include <Encoder.h> //LOOK INTO INCLUDE MORE
#include "CCUData.h"

#include "etl/singleton.h"
#include <etl/delegate.h>

#define CLK 2 //change based on actual pin used
#define DT 3 //change based on actual pin used
#define SW 4 //change based on actual pin used

struct rotary_encoder_s {
    volatile bool state = false;
    volatile int encoder_value = 0;
    unsigned long last_button_press = 0;
    const int max_value = 120;
    const int min_value = 0;
};

class RotaryEncoderInterface 
{
public:
    RotaryEncoderInterface(CCUData &ccu_data) :
    _ccu_data(ccu_data) {};

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