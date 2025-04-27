#ifndef DISPLAYSYSTEM_H
#define DISPLAYSYSTEM_H

#include <SPI.h>
#include <Arduino.h>
#include <Adafruit_GFX.h>      
#include <Adafruit_ILI9341.h>  
#include "CCUData.h"
#include "SharedFirmwareTypes.h"
#include "ACUInterface.h"

using pin = size_t;

namespace DISPLAY_PINS
{
    constexpr const pin LCD_CS = 36;
    constexpr const pin LCD_SCK = 13;
    constexpr const pin LCD_MISO = 12;
    constexpr const pin LCD_MOSI = 11;
    constexpr const pin LCD_RESET = 40;
    constexpr const pin LCD_DC = 41;
}

class DisplaySystem 
{
    public: 

        DisplaySystem(CCUData &ccu_data) :_ccu_data(ccu_data){};


        void display_data();


    private:
        CCUData &_ccu_data;

};

using DisplaySystemInstance = etl::singleton<DisplaySystem>;

#endif