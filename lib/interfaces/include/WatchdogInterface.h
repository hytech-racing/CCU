#ifndef WATCHDOG_INTERFACE_H
#define WATCHDOG_INTERFACE_H

#include <etl/singleton.h>
#include <Arduino.h>

using pin = size_t;

/* Watchdog Constants */
namespace Watchdog_Params {

    constexpr const pin WATCHDOG_PIN = 26; //teensy input to watchdog
    constexpr const pin SOFTWARE_OK_PIN = 27; // Watchdog's !RESET pin
    constexpr unsigned long WATCHDOG_KICK_INTERVAL_MS = 10UL;

};


class WatchdogInterface
{
public:

    void init();
    
    WatchdogInterface(const unsigned long kick_interval_ms = 10UL) : _watchdog_time(0), _watchdog_state(false), _watchdog_kick_interval(kick_interval_ms) {};

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
};

using WatchdogInstance = etl::singleton<WatchdogInterface>;

#endif /* WATCHDOG_SYSTEM_H */