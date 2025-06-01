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
    }

    return _watchdog_state;

}

void WatchdogInterface::check_AMS_comms_heartbeat(unsigned long curr_millis) {
    if ((curr_millis - ACUInterfaceInstance::instance().get_latest_data().last_recv_status_millis) > ACUInterfaceInstance::instance().get_latest_data()._max_heartbeat_interval_ms) {
        ACUInterfaceInstance::instance().acu_heartbeat_not_ok();
    }
}

