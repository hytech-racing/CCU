#ifndef CHARGECYCLE_T
#define CHARGECYCLE_T

#include "MainChargeSystem.h"
#include "ACUInterface.h"
#include "ChargerInterface.h"
#include <gtest/gtest.h>
#include <iostream>

CCUData ccu_data;
MainChargeSystem mainChargeLoop(ccu_data);

TEST(mainChargeTest, ACUShutsDownCharge) // Not Charging b/c acu_state = 1
{
    ACUInterfaceInstance::instance().set_latest_data({
        1,                                 // acu_state
        3.9f,                              // average_voltage
        3.8f,                              // low_voltage
        CCUData::cutoff_voltage - 0.1f,    // high_voltage
        CCUData::max_pack_voltage - 10.0f  // total_voltage
    });

    mainChargeLoop.calculate_charge_current();

    EXPECT_EQ(ccu_data.charging_state, ChargingState_e::NOT_CHARGING);
    EXPECT_FLOAT_EQ(ccu_data.calculated_charge_current, 0.0f);
    EXPECT_EQ(ccu_data.balancing_enabled, false);
}

TEST(mainChargeTest, DoneChargingAtHighVoltage) // Done charging b/c Current Voltage = High Voltage
{
    ACUInterfaceInstance::instance().set_latest_data({
        2,                                 // acu_state
        3.9f,                              // average_voltage
        3.8f,                              // low_voltage
        CCUData::cutoff_voltage,           // high_voltage
        CCUData::max_pack_voltage - 10.0f  // total_voltage
    });

    mainChargeLoop.calculate_charge_current();

    EXPECT_EQ(ccu_data.charging_state, ChargingState_e::DONE_CHARGING);
    EXPECT_FLOAT_EQ(ccu_data.calculated_charge_current, 0.0f);
    EXPECT_EQ(ccu_data.balancing_enabled, false);
}

TEST(mainChargeTest, DoneChargingOverHighVoltage) // Done charging b/c Current Voltage > High Voltage
{
    ACUInterfaceInstance::instance().set_latest_data({
        2,                                 // acu_state
        3.9f,                              // average_voltage
        3.8f,                              // low_voltage
        CCUData::cutoff_voltage + 0.5f,    // high_voltage
        CCUData::max_pack_voltage - 10.0f  // total_voltage
    });

    mainChargeLoop.calculate_charge_current();

    EXPECT_EQ(ccu_data.charging_state, ChargingState_e::DONE_CHARGING);
    EXPECT_FLOAT_EQ(ccu_data.calculated_charge_current, 0.0f);
    EXPECT_EQ(ccu_data.balancing_enabled, false);
}

TEST(mainChargeTest, ContinuesChargingUnderHighVoltage) // Continues Charging b/c Current Voltage < High Voltage
{
    ACUInterfaceInstance::instance().set_latest_data({
        2,                                 // acu_state
        3.9f,                              // average_voltage
        3.8f,                              // low_voltage
        CCUData::cutoff_voltage - 0.001f,  // high_voltage
        CCUData::max_pack_voltage - 10.0f  // total_voltage
    });

    mainChargeLoop.calculate_charge_current();

    EXPECT_EQ(ccu_data.charging_state, ChargingState_e::CHARGING);
    EXPECT_FLOAT_EQ(ccu_data.calculated_charge_current, CCUData::charger_current_max);
}

TEST(MainChargeTest, DoneChargingOverMaxPackVoltage) // Done charging b/c total_voltage > max_pack_voltage
{
    ACUInterfaceInstance::instance().set_latest_data({
        2,                                 // acu_state
        3.9f,                              // average_voltage
        3.8f,                              // low_voltage
        CCUData::cutoff_voltage - 0.1f,    // high_voltage
        CCUData::max_pack_voltage + 0.1f   // total_voltage
    });

    mainChargeLoop.calculate_charge_current();

    EXPECT_EQ(ccu_data.charging_state, ChargingState_e::DONE_CHARGING);
    EXPECT_FLOAT_EQ(ccu_data.calculated_charge_current, 0.0f);
    EXPECT_EQ(ccu_data.balancing_enabled, false);
}

TEST(MainChargeTest, ContinuesChargingAtMaxPackVoltage) // Continues charging b/c total_voltage = max_pack_voltage
{
    ACUInterfaceInstance::instance().set_latest_data({
        2,                                 // acu_state
        3.9f,                              // average_voltage
        3.8f,                              // low_voltage
        CCUData::cutoff_voltage - 0.1f,    // high_voltage
        CCUData::max_pack_voltage          // total_voltage
    });

    mainChargeLoop.calculate_charge_current();

    EXPECT_EQ(ccu_data.charging_state, ChargingState_e::CHARGING);
    EXPECT_FLOAT_EQ(ccu_data.calculated_charge_current, CCUData::charger_current_max);
}

TEST(MainChargeTest, RegularCharging) // Continues charging b/c within legal bounds
{
    ACUInterfaceInstance::instance().set_latest_data({
        2,                                 // acu_state
        3.9f,                              // average_voltage
        3.8f,                              // low_voltage
        CCUData::cutoff_voltage - 0.1f,    // high_voltage
        CCUData::max_pack_voltage - 10.0f  // total_voltage
    });

    mainChargeLoop.calculate_charge_current();

    EXPECT_EQ(ccu_data.charging_state, ChargingState_e::CHARGING);
    EXPECT_FLOAT_EQ(ccu_data.calculated_charge_current, CCUData::charger_current_max);
}

#endif