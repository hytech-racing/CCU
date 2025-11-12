#include "MainChargeSystem.h"
#include <algorithm>
#include <cmath>

constexpr const int SHUTDOWN_LOW = 1;

void MainChargeSystem::calculate_charge_current() {
    float average_voltage = ACUInterfaceInstance::instance().get_latest_data().average_voltage; //NOLINT
    float low_voltage = ACUInterfaceInstance::instance().get_latest_data().low_voltage; //NOLINT
    float high_voltage = ACUInterfaceInstance::instance().get_latest_data().high_voltage; //NOLINT
    float total_voltage = ACUInterfaceInstance::instance().get_latest_data().total_voltage; //NOLINT
}
