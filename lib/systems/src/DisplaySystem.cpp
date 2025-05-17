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
    Display.println(ACUInterfaceInstance::instance().get_latest_data().high_voltage, 4);

   
    Display.print("Cell Voltage min: ");
    Display.println(ACUInterfaceInstance::instance().get_latest_data().low_voltage, 4);
 

    Display.print("Cell Voltage average: ");
    Display.println(ACUInterfaceInstance::instance().get_latest_data().average_voltage, 4);


    Display.print("Cell Voltage delta: ");
    Display.println(ACUInterfaceInstance::instance().get_latest_data().high_voltage - ACUInterfaceInstance::instance().get_latest_data().low_voltage, 4);


    Display.print("Total pack voltage: ");
    Display.println(ACUInterfaceInstance::instance().get_latest_data().total_voltage, 4);


    Display.print("Max Board Temp:  ");
    Display.println(ACUInterfaceInstance::instance().get_latest_data().max_board_temp);


    //hard-coded method to find max cell temp
    if (ACUInterfaceInstance::instance().get_latest_data().therm_id_0 > _ccu_data.max_cell_temp) {
        _ccu_data.max_cell_temp = ACUInterfaceInstance::instance().get_latest_data().therm_id_0;
    } 
    if (ACUInterfaceInstance::instance().get_latest_data().therm_id_1 > _ccu_data.max_cell_temp) {
        _ccu_data.max_cell_temp = ACUInterfaceInstance::instance().get_latest_data().therm_id_1;
    }
    if (ACUInterfaceInstance::instance().get_latest_data().therm_id_2 > _ccu_data.max_cell_temp) {
        _ccu_data.max_cell_temp = ACUInterfaceInstance::instance().get_latest_data().therm_id_2;
    }

    Display.print("Max Cell Temp:  ");
    Display.println(_ccu_data.max_cell_temp, 4);

    _ccu_data.min_cell_temp = ACUInterfaceInstance::instance().get_latest_data().therm_id_0;
    if (ACUInterfaceInstance::instance().get_latest_data().therm_id_1 < _ccu_data.min_cell_temp) {
        _ccu_data.min_cell_temp = ACUInterfaceInstance::instance().get_latest_data().therm_id_1;
    }
    if (ACUInterfaceInstance::instance().get_latest_data().therm_id_2 < _ccu_data.min_cell_temp) {
        _ccu_data.min_cell_temp = ACUInterfaceInstance::instance().get_latest_data().therm_id_2;
    }

    Display.print("Min Cell Temp:  ");
    Display.println(_ccu_data.min_cell_temp, 4);

}

void DisplaySystem::refresh_display_data(unsigned long curr_millis) {

    if ((curr_millis - display_time) >= display_update_interval) {
        Display.fillScreen(ILI9341_BLACK);
        display_time = curr_millis;
    }
}