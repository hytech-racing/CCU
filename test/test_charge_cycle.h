#ifndef CHARGECYCLE_T
#define CHARGECYCLE_T

#include "MainChargeSystem.h"
#include <gtest/gtest.h>
#include <iostream>


namespace fake_data
{
    float volts_too_much[126] = {
        4.723f, 4.152f, 4.891f, 4.346f, 4.678f, 4.234f, 4.567f, 4.912f, 4.389f, 4.745f,
        4.198f, 4.623f, 4.456f, 4.879f, 4.301f, 4.734f, 4.167f, 4.590f, 4.923f, 4.278f,
        4.645f, 4.412f, 4.789f, 4.334f, 4.701f, 4.256f, 4.578f, 4.945f, 4.389f, 4.812f,
        4.167f, 4.534f, 4.890f, 4.223f, 4.667f, 4.401f, 4.778f, 4.345f, 4.690f, 4.256f,
        4.589f, 4.934f, 4.312f, 4.756f, 4.189f, 4.623f, 4.467f, 4.801f, 4.334f, 4.678f,
        4.245f, 4.590f, 4.923f, 4.378f, 4.745f, 4.201f, 4.556f, 4.889f, 4.434f, 4.767f,
        4.312f, 4.645f, 4.978f, 4.223f, 4.590f, 4.156f, 4.523f, 4.867f, 4.401f, 4.734f,
        4.289f, 4.612f, 4.945f, 4.378f, 4.701f, 4.234f, 4.567f, 4.890f, 4.323f, 4.656f,
        4.189f, 4.534f, 4.867f, 4.412f, 4.745f, 4.278f, 4.601f, 4.934f, 4.367f, 4.789f,
        4.223f, 4.556f, 4.890f, 4.345f, 4.678f, 4.201f, 4.534f, 4.867f, 4.389f, 4.723f,
        4.256f, 4.590f, 4.923f, 4.367f, 4.701f, 4.234f, 4.567f, 4.890f, 4.323f, 4.656f,
        4.189f, 4.523f, 4.856f, 4.401f, 4.734f, 4.267f, 4.601f, 4.934f, 4.378f, 4.712f,
        4.245f, 4.578f, 4.912f, 4.356f, 4.689f, 4.223f
    };
    float more_volts_too_much[126] = {
        4.834f, 4.267f, 4.956f, 4.401f, 4.723f, 4.189f, 4.612f, 4.978f, 4.345f, 4.790f,
        4.234f, 4.678f, 4.512f, 4.845f, 4.378f, 4.701f, 4.256f, 4.623f, 4.967f, 4.312f,
        4.734f, 4.467f, 4.812f, 4.389f, 4.656f, 4.201f, 4.545f, 4.890f, 4.434f, 4.767f,
        4.289f, 4.612f, 4.945f, 4.378f, 4.701f, 4.256f, 4.578f, 4.923f, 4.367f, 4.734f,
        4.189f, 4.534f, 4.867f, 4.401f, 4.756f, 4.312f, 4.645f, 4.978f, 4.345f, 4.689f,
        4.223f, 4.567f, 4.901f, 4.434f, 4.778f, 4.267f, 4.601f, 4.934f, 4.389f, 4.723f,
        4.256f, 4.590f, 4.923f, 4.367f, 4.701f, 4.234f, 4.567f, 4.890f, 4.323f, 4.656f,
        4.189f, 4.523f, 4.856f, 4.401f, 4.734f, 4.267f, 4.601f, 4.934f, 4.378f, 4.712f,
        4.245f, 4.578f, 4.912f, 4.356f, 4.689f, 4.223f, 4.556f, 4.890f, 4.345f, 4.678f,
        4.201f, 4.534f, 4.867f, 4.389f, 4.723f, 4.256f, 4.590f, 4.923f, 4.367f, 4.701f,
        4.234f, 4.567f, 4.890f, 4.323f, 4.656f, 4.189f, 4.523f, 4.856f, 4.401f, 4.734f,
        4.267f, 4.601f, 4.934f, 4.378f, 4.712f, 4.245f, 4.578f, 4.912f, 4.356f, 4.689f,
        4.223f, 4.556f, 4.890f, 4.345f, 4.678f, 4.201f
    };

    float good_volts_low[126] = {
        2.234f, 2.156f, 2.378f, 2.201f, 2.323f, 2.189f, 2.267f, 2.389f, 2.245f, 2.312f,
        2.167f, 2.298f, 2.356f, 2.223f, 2.278f, 2.201f, 2.334f, 2.389f, 2.256f, 2.312f,
        2.178f, 2.245f, 2.367f, 2.201f, 2.289f, 2.234f, 2.312f, 2.378f, 2.256f, 2.323f,
        2.189f, 2.267f, 2.345f, 2.223f, 2.298f, 2.167f, 2.334f, 2.389f, 2.245f, 2.312f,
        2.201f, 2.278f, 2.356f, 2.234f, 2.289f, 2.167f, 2.323f, 2.378f, 2.256f, 2.312f,
        2.189f, 2.267f, 2.345f, 2.223f, 2.298f, 2.178f, 2.334f, 2.389f, 2.245f, 2.312f,
        2.201f, 2.278f, 2.356f, 2.234f, 2.289f, 2.167f, 2.323f, 2.378f, 2.256f, 2.312f,
        2.189f, 2.267f, 2.345f, 2.223f, 2.298f, 2.178f, 2.334f, 2.389f, 2.245f, 2.312f,
        2.201f, 2.278f, 2.356f, 2.234f, 2.289f, 2.167f, 2.323f, 2.378f, 2.256f, 2.312f,
        2.189f, 2.267f, 2.345f, 2.223f, 2.298f, 2.178f, 2.334f, 2.389f, 2.245f, 2.312f,
        2.201f, 2.278f, 2.356f, 2.234f, 2.289f, 2.167f, 2.323f, 2.378f, 2.256f, 2.312f,
        2.189f, 2.267f, 2.345f, 2.223f, 2.298f, 2.178f, 2.334f, 2.389f, 2.245f, 2.312f,
        2.201f, 2.278f, 2.356f, 2.234f, 2.289f, 2.167f
    };
    
    float good_volts_high[126] = {
        2.856f, 2.734f, 2.978f, 2.812f, 2.923f, 2.789f, 2.867f, 2.945f, 2.801f, 2.889f,
        2.756f, 2.834f, 2.912f, 2.978f, 2.845f, 2.723f, 2.901f, 2.867f, 2.789f, 2.956f,
        2.834f, 2.712f, 2.890f, 2.945f, 2.801f, 2.878f, 2.756f, 2.923f, 2.867f, 2.789f,
        2.934f, 2.812f, 2.890f, 2.978f, 2.845f, 2.723f, 2.901f, 2.856f, 2.789f, 2.967f,
        2.834f, 2.712f, 2.890f, 2.945f, 2.801f, 2.878f, 2.756f, 2.923f, 2.867f, 2.789f,
        2.934f, 2.812f, 2.890f, 2.978f, 2.845f, 2.723f, 2.901f, 2.856f, 2.789f, 2.967f,
        2.834f, 2.712f, 2.890f, 2.945f, 2.801f, 2.878f, 2.756f, 2.923f, 2.867f, 2.789f,
        2.934f, 2.812f, 2.890f, 2.978f, 2.845f, 2.723f, 2.901f, 2.856f, 2.789f, 2.967f,
        2.834f, 2.712f, 2.890f, 2.945f, 2.801f, 2.878f, 2.756f, 2.923f, 2.867f, 2.789f,
        2.934f, 2.812f, 2.890f, 2.978f, 2.845f, 2.723f, 2.901f, 2.856f, 2.789f, 2.967f,
        2.834f, 2.712f, 2.890f, 2.945f, 2.801f, 2.878f, 2.756f, 2.923f, 2.867f, 2.789f,
        2.934f, 2.812f, 2.890f, 2.978f, 2.845f, 2.723f, 2.901f, 2.856f, 2.789f, 2.967f,
        2.834f, 2.712f, 2.890f, 2.945f, 2.801f, 2.878f
    };

    float all_temp_high[48] = {
        72.34f, 78.12f, 75.89f, 71.56f, 79.23f, 73.45f, 77.89f, 70.67f, 76.12f, 74.98f,
        71.23f, 78.56f, 75.34f, 79.89f, 72.67f, 77.01f, 73.89f, 76.45f, 70.12f, 78.23f,
        74.56f, 79.67f, 71.89f, 77.34f, 75.12f, 72.78f, 78.45f, 76.89f, 70.56f, 79.01f,
        73.23f, 77.67f, 74.89f, 71.45f, 78.12f, 76.34f, 79.56f, 72.89f, 75.67f, 70.23f,
        77.12f, 73.56f, 78.89f, 71.67f, 76.23f, 74.01f, 79.34f, 72.45f
    };
    
    float some_temp_high[48] = {
        66.78f, 69.12f, 67.45f, 65.89f, 68.23f, 66.01f, 69.56f, 67.89f, 65.34f, 68.67f,
        66.12f, 69.23f, 67.56f, 65.78f, 68.45f, 66.89f, 69.01f, 67.23f, 65.56f, 68.12f,
        66.34f, 69.67f, 67.89f, 65.23f, 68.56f, 66.78f, 69.45f, 67.01f, 65.89f, 68.23f,
        66.45f, 69.12f, 67.67f, 65.34f, 68.89f, 66.56f, 70.18f, 67.23f, 65.67f, 68.01f,
        66.12f, 69.56f, 67.45f, 65.89f, 68.34f, 66.78f, 69.23f, 67.56f
    };
    
    float good_temp[48] = {
        52.34f, 54.12f, 51.89f, 53.56f, 50.78f, 54.45f, 52.67f, 51.23f, 53.89f, 50.56f,
        54.01f, 52.78f, 51.45f, 53.12f, 50.89f, 54.34f, 52.56f, 51.67f, 53.23f, 50.45f,
        54.78f, 52.12f, 51.89f, 53.56f, 50.23f, 54.45f, 52.67f, 51.01f, 53.34f, 50.78f,
        54.12f, 52.89f, 51.56f, 53.23f, 50.45f, 54.67f, 52.34f, 51.78f, 53.89f, 50.12f,
        54.56f, 52.23f, 51.67f, 53.45f, 50.89f, 54.01f, 52.78f, 51.34f
    };

 
} // namespace fake_ACUAllData_s

namespace MockCCUInterface
{
    ACUAllData_s mock_receive_message(float volt_array[126], float temp_array[48]){
        
        ACUAllData_s out;

        for (int i = 0; i < 126; i++)
        {
            out.voltages[i] = volt_array[i];
        }
        for (int i = 0; i < 48; i++)
        {
            out.cell_temperatures[i] = temp_array[i];
        }
        return out;
    }
}
CCUParams chargeparams;
MainChargeSystem mainChargeLoop(chargeparams.target_voltage_per_cell, chargeparams.max_allowable_cell_temperature);

TEST(mainChargeTest, bothTooHigh){ 
    EXPECT_EQ(mainChargeLoop.calculate_charge_current(MockCCUInterface::mock_receive_message(fake_data::volts_too_much, fake_data::all_temp_high)),0);
};

TEST(mainChargeTest, TempTooHigh){  
    EXPECT_EQ(mainChargeLoop.calculate_charge_current(MockCCUInterface::mock_receive_message(fake_data::good_volts_low, fake_data::some_temp_high)),0);
};

TEST(mainChargeTest, VoltsTooHigh){  
    EXPECT_EQ(mainChargeLoop.calculate_charge_current(MockCCUInterface::mock_receive_message(fake_data::more_volts_too_much, fake_data::good_temp)),0);
};

TEST(mainChargeTest, shouldBeTrue){  
    EXPECT_NE(mainChargeLoop.calculate_charge_current(MockCCUInterface::mock_receive_message(fake_data::good_volts_high, fake_data::good_temp)),0);
};


#endif