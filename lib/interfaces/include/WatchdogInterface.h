#ifndef WATCHDOG_INTERFACE_H
#define WATCHDOG_INTERFACE_H

#include <etl/singleton.h>
#include <Arduino.h>

using pin = size_t;

/* Watchdog Constants */
namespace WATCHDOG_PARAMS {

    constexpr const pin WATCHDOG_PIN = 26; //teensy input to watchdog
    constexpr const pin SOFTWARE_OK_PIN = 27; // Watchdog's !RESET pin
    constexpr unsigned long WATCHDOG_KICK_INTERVAL_MS = 10UL;

};


class WatchdogInterface
{
public:
    
    WatchdogInterface(
        pin sw_ok_pin = WATCHDOG_PARAMS::SOFTWARE_OK_PIN,
        pin wd_kick_pin = WATCHDOG_PARAMS::WATCHDOG_PIN,
        const unsigned long kick_interval_ms = 10UL) : 
            teensy_wd_pin(wd_kick_pin),
            teensy_sw_pin(sw_ok_pin),
            _watchdog_time(0), 
            _watchdog_state(false), 
            _watchdog_kick_interval(kick_interval_ms) 
    {};

    void init();

private:

    pin teensy_wd_pin; //needs to kick watchdog at 100 hertz to keep CCU_OK high
    pin teensy_sw_pin;


    /* Watchdog last kicked time */
    unsigned long _watchdog_time;
    bool _watchdog_state;
    unsigned long _watchdog_kick_interval;
    /* Watchdog output state */
    
public:

    /* Get and update watchdog state */
    bool get_watchdog_state(unsigned long curr_millis);

    void set_teensy_sw_high(); //never used
};

using WatchdogInstance = etl::singleton<WatchdogInterface>;

#endif /* WATCHDOG_SYSTEM_H */