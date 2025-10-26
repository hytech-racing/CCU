#include "DataLoggingInterface.h"
#include "ACUInterface.h"
#include "EMInterface.h"
#include "SystemTimeInterface.h"
#include "ChargerStateMachine.h"

bool DataLoggingInterface::init() {
    if (!SD.begin(BUILTIN_SDCARD)) {
        return false;
    }

    data_file = SD.open(file_name, FILE_WRITE);
    if (!data_file) {
        return false;
    }
    if (data_file.size() == 0) {
        data_file.println("timestamp,pack_current,pack_voltage,cell_voltage_avg,cell_voltage_min,cell_voltage_max,cell_temp_min,cell_temp_max,board_temp_max,charging_state");
    }

    data_file.close();

    return true;
}

void DataLoggingInterface::log_data() {
    auto acu_data = ACUInterfaceInstance::instance().get_latest_data();
    auto em_data = EnergyMeterInterfaceInstance::instance().get_latest_em_data();

    data_file = SD.open(file_name, FILE_WRITE);
    if (!data_file) {
        return;
    }

    data_file.print(sys_time::hal_millis());
    data_file.print(",");
    data_file.print(em_data.current_amps);
    data_file.print(",");
    data_file.print(acu_data.total_voltage);
    data_file.print(",");
    data_file.print(acu_data.average_voltage);
    data_file.print(",");
    data_file.print(acu_data.low_voltage);
    data_file.print(",");
    data_file.print(acu_data.high_voltage);
    data_file.print(",");
    data_file.print(acu_data.min_cell_temp);
    data_file.print(",");
    data_file.print(acu_data.max_cell_temp);
    data_file.print(",");
    data_file.print(acu_data.max_board_temp);
    data_file.print(",");
    data_file.print(static_cast<int>(ChargerStateMachineInstance::instance().get_state()));
    data_file.println();

    data_file.close();
}