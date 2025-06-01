#ifndef DisplayInterface_H
#define DisplayInterface_H

#include <SPI.h>
#include <DMAChannel.h>
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

class DisplayInterface 
{
    public: 

        DisplayInterface(CCUData &ccu_data) :
            _ccu_data(ccu_data), 
            Display(DISPLAY_PINS::LCD_CS, DISPLAY_PINS::LCD_DC, DISPLAY_PINS::LCD_MOSI, DISPLAY_PINS::LCD_SCK, DISPLAY_PINS::LCD_RESET, DISPLAY_PINS::LCD_MISO) 
            {};

        void init();
        void display_data();

        Adafruit_ILI9341 Display;


    private:
        CCUData &_ccu_data;

};

using DisplayInterfaceInstance = etl::singleton<DisplayInterface>;

#endif