#ifndef LEVEL2INTERFACE_H
#define LEVEL2INTERFACE_H

/* External Dependencies */
#include <etl/singleton.h>
#include <Arduino.h>
#include <cstddef>
#include <cstdint>

using pin = size_t;


struct Level2Pinout_s
{
    const pin teensy_control_pwm_sense_pin;
    const pin teensy_start_charge_pin;
};

struct Level2_Data_s
{
    uint16_t control_pwm;
    float control_pwm_duty_cycle;
};

class Level2Interface
{
public:
    Level2Interface(
        Level2Pinout_s pinout = {}
    ) :
        _pinout(pinout)
    {}

    void init();

    /**
     * Function to determine pwm dutycycle
     */
    bool _is_pwm_duty_cycle_valid();

    /**
     * Setter for START_CHARGE signal
     */
    void set_start_charge(bool state);


    Level2_Data_s getLevel2Data() const;

private:

    Level2Pinout_s _pinout;
    Level2_Data_s _readings;
};

using Level2InterfaceInstance = etl::singleton<Level2Interface>;

#endif