#ifndef __CHARGECYCLE_T__
#define __CHARGECYCLE_T__

#include "MainChargeSystem.h"
#include "EthernetInterface.h"
#include <gtest/gtest.h>
#include <iostream>

MainChargeSystem mainChargeLoop(3.1, 15, 40, 1, 1, 1);
CCUOutput_s testoutputs;

TEST(mainChargeTest, bothTooHigh){  
    CCUInput_s test1inputs;
    test1inputs.max_cell_temperature = 70;
    test1inputs.max_cell_voltage =  4;
    mainChargeLoop.charge_cycle(test1inputs, testoutputs);
    EXPECT_EQ(testoutputs.current_flow, false);
};

TEST(mainChargeTest, TempTooHigh){  
    CCUInput_s test2inputs;
    test2inputs.max_cell_temperature = 70;
    test2inputs.max_cell_voltage=  1.27; //in Volts
    mainChargeLoop.charge_cycle(test2inputs, testoutputs);
    EXPECT_EQ(testoutputs.current_flow, false);
};

TEST(mainChargeTest, VoltsTooHigh){  
    CCUInput_s test3inputs;
    test3inputs.max_cell_temperature = 52.1;
    test3inputs.max_cell_voltage =  4;//in Volts
    mainChargeLoop.charge_cycle(test3inputs, testoutputs);
    EXPECT_EQ(testoutputs.current_flow, false);
};

TEST(mainChargeTest, shouldBeTrue){  
    CCUInput_s test4inputs;
    test4inputs.max_cell_temperature = 30;
    test4inputs.max_cell_voltage =  2.3; //in Volts
    mainChargeLoop.charge_cycle(test4inputs, testoutputs);
    EXPECT_EQ(testoutputs.current_flow, true);
};


#endif