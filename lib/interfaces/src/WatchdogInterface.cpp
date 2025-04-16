#include "WatchdogInterface.h"


void WatchdogInterface::init() {
    pinMode(Watchdog_Params::WATCHDOG_PIN, OUTPUT);
    digitalWrite(Watchdog_Params::WATCHDOG_PIN, HIGH);
}


bool WatchdogInterface::get_watchdog_state(unsigned long curr_millis) {

    if ((curr_millis - _watchdog_time) > _watchdog_kick_interval) {
        _watchdog_state = !_watchdog_state;
        _watchdog_time = curr_millis;
    }

    return _watchdog_state;

}
