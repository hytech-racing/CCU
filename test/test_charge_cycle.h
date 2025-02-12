#ifndef __CHARGECYCLE_T__
#define __CHARGECYCLE_T__

#include "MainChargeSystem.h"
#include "EthernetInterface.h"
#include <gtest/gtest.h>

MainChargeSystem mainChargeLoop;


TEST(mainChargeTest, bothTooHigh){  
    //EthernetInterface test1EthernetInterface;
    ethernetInterface.maxCellTemp = 70;
    ethernetInterface.maxCellV =  4;
    mainChargeLoop.charge_cycle();
    EXPECT_EQ(ethernetInterface.currentFlow,  false);
};

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


#endif