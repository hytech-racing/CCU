#ifndef ROTARYENCODERINTERFACE_H
#define ROTARYENCODERINTERFACE_H

#include "CCUData.h"
#include "mockArduino.h"

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
    _ccu_data(ccu_data) {};

    void setup_encoder();
    void update_encoder();
    static void isr1();
    void set_enc_value(int dt_value);

    bool is_button_pressed() const { return _encoder_data.state; };

private:
    rotary_encoder_s _encoder_data;
    CCUData &_ccu_data;
};

using RotaryEncoderInterfaceInstance = etl::singleton<RotaryEncoderInterface>;

#endif
