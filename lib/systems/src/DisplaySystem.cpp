#include "DisplaySystem.h"

void DisplaySystem::init() {
    Display.begin();
    //Display.fillScreen(ILI9341_WHITE);
    Display.setRotation(3);
    Display.setTextSize(2);
    Display.fillScreen(ILI9341_BLACK);
}

void DisplaySystem::display_data() {

    //Adafruit_ILI9341 Display = Adafruit_ILI9341(DISPLAY_PINS::LCD_CS, DISPLAY_PINS::LCD_DC, DISPLAY_PINS::LCD_MOSI, DISPLAY_PINS::LCD_SCK, DISPLAY_PINS::LCD_RESET, DISPLAY_PINS::LCD_MISO);
    Display.setCursor(0,0);
    Display.setRotation(3);
    Display.setTextSize(2);

    Display.println("Charging Status: ");
    if (_ccu_data.balancing_enabled) {
        Display.println("Charging");
    } else {
        Display.println("Not Charging");
    }
    //Display.println();

    Display.print("Cell Voltage max: ");
    Display.println(ACUInterfaceInstance::instance().get_latest_data().high_voltage);

   
    Display.print("Cell Voltage min: ");
    Display.println(ACUInterfaceInstance::instance().get_latest_data().low_voltage);
    //Display.println();

    Display.print("Cell Voltage average: ");
    Display.println(ACUInterfaceInstance::instance().get_latest_data().average_voltage);
    //Display.println();

    Display.print("Cell Voltage delta: ");
    Display.println(ACUInterfaceInstance::instance().get_latest_data().high_voltage - ACUInterfaceInstance::instance().get_latest_data().low_voltage);
    //Display.println();

    Display.print("Total pack voltage: ");
    Display.print(ACUInterfaceInstance::instance().get_latest_data().total_voltage);

    Display.print("Cell temp max:  ");
    Display.print(ACUInterfaceInstance::instance().get_latest_data().high_temp);

    Display.print("Cell temp min:  ");
    Display.print(ACUInterfaceInstance::instance().get_latest_data().low_temp);

    Display.print("Cell temp avg:  ");
    Display.print(ACUInterfaceInstance::instance().get_latest_data().average_temp);


}

void DisplaySystem::refresh_display_data(unsigned long curr_millis) {

    if ((curr_millis - display_time) >= display_update_interval) {
        Display.fillScreen(ILI9341_BLACK);
        display_time = curr_millis;
    }
}