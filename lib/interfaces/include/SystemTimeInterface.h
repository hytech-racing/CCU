#ifndef SYSTEMTIMEINTERFACE_H
#define SYSTEMTIMEINTERFACE_H

#include <Arduino.h>

namespace sys_time
{
    unsigned long hal_millis();
    unsigned long hal_micros();
}

#endif // __SYSTEMTIMEINTERFACE_H__