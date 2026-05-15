#ifndef DisplayInterface_H
#define DisplayInterface_H

/* External Dependencies */
#include <SPI.h>
#include <DMAChannel.h>
#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#include "SharedFirmwareTypes.h"

/* Local Interface Includes */
#include "ACUInterface.h"
#include "EMInterface.h"

using pin = size_t;

namespace display_default_parameters
{
    constexpr float DISPLAY_UPDATE_INTERVAL_MS = 100.0f;  // ms
};
struct DisplayPinout_s
{
    pin teensy_lcd_cs_pin;
    pin teensy_lcd_sck_pin;
    pin teensy_lcd_miso_pin;
    pin teensy_lcd_mosi_pin;
    pin teensy_lcd_reset_pin;
    pin teensy_lcd_dc_pin;
};

struct DisplayInterfaceParams_s
{
    DisplayPinout_s pinout;
    float display_time;
    float display_update_interval;
};

struct DisplayConfig_s {
    unsigned long display_update_interval_ms;
};

class DisplayInterface {
public:
    DisplayInterface(
        DisplayPinout_s pinout,
        DisplayConfig_s config = {
            .display_update_interval_ms = display_default_parameters::DISPLAY_UPDATE_INTERVAL_MS
        }
    ) :
        Display(
            pinout.teensy_lcd_cs_pin,
            pinout.teensy_lcd_dc_pin,
            pinout.teensy_lcd_mosi_pin,
            pinout.teensy_lcd_sck_pin,
            pinout.teensy_lcd_reset_pin,
            pinout.teensy_lcd_miso_pin
        ),
        _pinout(pinout),
        _config(config),
        _display_time(0.0f)
    {}

    void init();
    void display_data(bool is_120_switched);
    void refresh_display_data(unsigned long curr_millis);

    Adafruit_ILI9341 Display;

    private:
        DisplayPinout_s _pinout;
        DisplayConfig_s _config;
        unsigned long _display_time;

        // DMAChannel dma_spi;
        // uint8_t txBuffer [256];
        // uint8_t rxBuffer [256];
        //= Adafruit_ILI9341(DISPLAY_PINS::LCD_CS, DISPLAY_PINS::LCD_DC, DISPLAY_PINS::LCD_MOSI, DISPLAY_PINS::LCD_SCK, DISPLAY_PINS::LCD_RESET, DISPLAY_PINS::LCD_MISO);
};

using DisplayInterfaceInstance = etl::singleton<DisplayInterface>;

#endif