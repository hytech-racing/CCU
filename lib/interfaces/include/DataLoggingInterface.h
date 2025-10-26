#ifndef DATA_LOGGING_INTERFACE_H
#define DATA_LOGGING_INTERFACE_H

#include <etl/singleton.h>
#include <Arduino.h>
#include "SD.h"

class DataLoggingInterface
{
public:
    DataLoggingInterface() = default;

    bool init();
    void log_data();

private:
    File data_file;
    const char* file_name = "charge_log.csv";
};

using DataLoggingInterfaceInstance = etl::singleton<DataLoggingInterface>;

#endif /* DATA_LOGGING_INTERFACE_H */