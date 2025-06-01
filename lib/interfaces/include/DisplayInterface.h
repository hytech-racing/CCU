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

struct DisplayInterface_data_s {
    float high_voltage = ACUInterfaceInstance::instance().get_latest_data().high_voltage;
    float low_voltage = ACUInterfaceInstance::instance().get_latest_data().low_voltage;
    float avg_voltage = ACUInterfaceInstance::instance().get_latest_data().average_voltage;
    float total_pack_voltage = ACUInterfaceInstance::instance().get_latest_data().total_voltage;
    float max_board_temp = ACUInterfaceInstance::instance().get_latest_data().max_board_temp;
    float max_cell_temp = ACUInterfaceInstance::instance().get_latest_data().max_cell_temp;
    float min_cell_temp = ACUInterfaceInstance::instance().get_latest_data().min_cell_temp;
};


class DisplayInterface 
{
    public: 

        DisplayInterface(CCUData ccu_data) :
            Display(DISPLAY_PINS::LCD_CS, DISPLAY_PINS::LCD_DC, DISPLAY_PINS::LCD_MOSI, DISPLAY_PINS::LCD_SCK, DISPLAY_PINS::LCD_RESET, DISPLAY_PINS::LCD_MISO), 
            display_time(0),
            display_update_interval(1000UL) {};

        void init();
        void display_data();
        void refresh_display_data(unsigned long curr_millis);

        Adafruit_ILI9341 Display;


    private:
        CCUData _ccu_data;
        DisplayInterface_data_s _display_data;
        unsigned long display_time;
        unsigned long display_update_interval;

};

using DisplayInterfaceInstance = etl::singleton<DisplayInterface>;

#endif