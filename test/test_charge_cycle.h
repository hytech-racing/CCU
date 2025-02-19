#ifndef __CHARGECYCLE_T__
#define __CHARGECYCLE_T__

#include "MainChargeSystem.h"
#include "EthernetInterface.h"
#include <gtest/gtest.h>

MainChargeSystem mainChargeLoop;


TEST(mainChargeTest, bothTooHigh){  
    CCUInputValues test1inputs;
    CCUOutputValues test1outputs;
    test1inputs.maxCellTemp = 70;
    test1inputs.maxCellV =  4;
    mainChargeLoop.charge_cycle(test1inputs, test1outputs);
    EXPECT_EQ(test1outputs.currentFlow,  false);
};
/*
TEST(mainChargeTest, TempTooHigh){  
    //EthernetInterface test1EthernetInterface;
    ethernetInterface.maxCellTemp = 70;
    ethernetInterface.maxCellV =  1.27;
    mainChargeLoop.charge_cycle();
    EXPECT_EQ(ethernetInterface.currentFlow,  false);
};

TEST(mainChargeTest, VoltsTooHigh){  
    //EthernetInterface test1EthernetInterface;
    ethernetInterface.maxCellTemp = 52.1;
    ethernetInterface.maxCellV =  4;
    mainChargeLoop.charge_cycle();
    EXPECT_EQ(ethernetInterface.currentFlow,  false);
};

TEST(mainChargeTest, shouldBeTrue){  
    //EthernetInterface test1EthernetInterface;
    ethernetInterface.maxCellTemp = 30;
    ethernetInterface.maxCellV =  2.3;
    mainChargeLoop.charge_cycle();
    EXPECT_EQ(ethernetInterface.currentFlow,  true);
};

*/
#endif