#ifndef __CHARGECYCLE_T__
#define __CHARGECYCLE_T__

#include "MainChargeSystem.h"
#include "EthernetInterface.h"
#include <gtest/gtest.h>
#include <iostream>

MainChargeSystem mainChargeLoop;


TEST(mainChargeTest, bothTooHigh){  
    CCUInputValues test1inputs;
    CCUOutputValues test1outputs;
    test1inputs.maxCellTemp = 70;
    test1inputs.maxCellV =  4;
    mainChargeLoop.charge_cycle(test1inputs, test1outputs);
    EXPECT_EQ(test1outputs.currentFlow, false);
};

TEST(mainChargeTest, TempTooHigh){  
    CCUInputValues test2inputs;
    CCUOutputValues test2outputs;
    test2inputs.maxCellTemp = 70;
    test2inputs.maxCellV =  1.27;
    mainChargeLoop.charge_cycle(test2inputs, test2outputs);
    EXPECT_EQ(test2outputs.currentFlow, false);
};

TEST(mainChargeTest, VoltsTooHigh){  
    CCUInputValues test3inputs;
    CCUOutputValues test3outputs;
    test3inputs.maxCellTemp = 52.1;
    test3inputs.maxCellV =  4;
    mainChargeLoop.charge_cycle(test3inputs, test3outputs);
    EXPECT_EQ(test3outputs.currentFlow, false);
};

TEST(mainChargeTest, shouldBeTrue){  
    CCUInputValues test4inputs;
    CCUOutputValues test4outputs;
    test4inputs.maxCellTemp = 30;
    test4inputs.maxCellV =  2.3;
    mainChargeLoop.charge_cycle(test4inputs, test4outputs);
    EXPECT_EQ(test4outputs.currentFlow, true);
};


#endif