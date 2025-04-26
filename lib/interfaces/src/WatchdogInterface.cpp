#include "WatchdogInterface.h"


void WatchdogInterface::init() {
    pinMode(teensy_wd_pin, OUTPUT);
    pinMode(teensy_sw_pin, OUTPUT);
    digitalWrite(teensy_wd_pin, HIGH);
    digitalWrite(teensy_sw_pin, HIGH);
}
 


bool WatchdogInterface::get_watchdog_state(unsigned long curr_millis) {

    if ((curr_millis - _watchdog_time) > _watchdog_kick_interval) {
        _watchdog_state = !_watchdog_state;
        _watchdog_time = curr_millis;
        digitalWrite(teensy_wd_pin, _watchdog_state ? HIGH : LOW);
    }

    return _watchdog_state;

}

void WatchdogInterface::set_teensy_sw_high() {
    digitalWrite(teensy_sw_pin, HIGH);
}