#include "WatchdogInterface.h"


void WatchdogInterface::init() {
    pinMode(WATCHDOG_PARAMS::WATCHDOG_PIN, OUTPUT);
    digitalWrite(WATCHDOG_PARAMS::WATCHDOG_PIN, HIGH);
}


bool WatchdogInterface::get_watchdog_state(unsigned long curr_millis) {

    if ((curr_millis - _watchdog_time) > _watchdog_kick_interval) {
        _watchdog_state = !_watchdog_state;
        _watchdog_time = curr_millis;
    }
    return _watchdog_state;

}

void WatchdogInterface::set_teensy_sw_high() {
    digitalWrite(teensy_sw_pin, HIGH);
}