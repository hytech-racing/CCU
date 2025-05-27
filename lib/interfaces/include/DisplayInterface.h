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
            Display(DISPLAY_PINS::LCD_CS, DISPLAY_PINS::LCD_DC, DISPLAY_PINS::LCD_MOSI, DISPLAY_PINS::LCD_SCK, DISPLAY_PINS::LCD_RESET, DISPLAY_PINS::LCD_MISO), 
            display_time(0),
            display_update_interval(1000UL) {};

        void init();
        void display_data();
        void refresh_display_data(unsigned long curr_millis);

        Adafruit_ILI9341 Display;


    private:
        CCUData &_ccu_data;
        unsigned long display_time;
        unsigned long display_update_interval;

        // DMAChannel dma_spi;
        // uint8_t txBuffer [256];
        // uint8_t rxBuffer [256];
         //= Adafruit_ILI9341(DISPLAY_PINS::LCD_CS, DISPLAY_PINS::LCD_DC, DISPLAY_PINS::LCD_MOSI, DISPLAY_PINS::LCD_SCK, DISPLAY_PINS::LCD_RESET, DISPLAY_PINS::LCD_MISO);


};

using DisplayInterfaceInstance = etl::singleton<DisplayInterface>;

#endif