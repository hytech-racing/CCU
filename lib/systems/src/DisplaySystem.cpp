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
        Display.print("Charging at  ");
        Display.println(_ccu_data.calculated_charge_current);
    } else if (ACUInterfaceInstance::instance().get_latest_data().high_voltage >= _ccu_data.cutoff_voltage || ACUInterfaceInstance::instance().get_latest_data().total_voltage >= _ccu_data.max_pack_voltage) {
        Display.println("Done charging!");
    } else {
        Display.println("Not Charging");
    }
    

    Display.print("Cell Voltage max: ");
    Display.println(ACUInterfaceInstance::instance().get_latest_data().high_voltage, 3);

   
    Display.print("Cell Voltage min: ");
    Display.println(ACUInterfaceInstance::instance().get_latest_data().low_voltage, 3);
 

    Display.print("Cell Voltage average: ");
    Display.println(ACUInterfaceInstance::instance().get_latest_data().average_voltage, 3);


    Display.print("Cell Voltage delta: ");
    Display.println(ACUInterfaceInstance::instance().get_latest_data().high_voltage - ACUInterfaceInstance::instance().get_latest_data().low_voltage, 3);


    Display.print("Total pack voltage: ");
    Display.println(ACUInterfaceInstance::instance().get_latest_data().total_voltage, 3);


    Display.print("Max Board Temp:  ");
    Display.println(ACUInterfaceInstance::instance().get_latest_data().max_board_temp, 3);


    //hard-coded to find max and min cell temps based on BMS_DETAILED_TEMPS
    // if (ACUInterfaceInstance::instance().get_latest_data().therm_id_0 > _ccu_data.max_cell_temp) {
    //     _ccu_data.max_cell_temp = ACUInterfaceInstance::instance().get_latest_data().therm_id_0;
    // } 
    // if (ACUInterfaceInstance::instance().get_latest_data().therm_id_1 > _ccu_data.max_cell_temp) {
    //     _ccu_data.max_cell_temp = ACUInterfaceInstance::instance().get_latest_data().therm_id_1;
    // }
    // if (ACUInterfaceInstance::instance().get_latest_data().therm_id_2 > _ccu_data.max_cell_temp) {
    //     _ccu_data.max_cell_temp = ACUInterfaceInstance::instance().get_latest_data().therm_id_2;
    // }

    Display.print("Max Cell Temp:  ");
    Display.println(ACUInterfaceInstance::instance().get_latest_data().max_cell_temp, 3);


    // _ccu_data.min_cell_temp = ACUInterfaceInstance::instance().get_latest_data().therm_id_0;
    // if (ACUInterfaceInstance::instance().get_latest_data().therm_id_1 < _ccu_data.min_cell_temp) {
    //     _ccu_data.min_cell_temp = ACUInterfaceInstance::instance().get_latest_data().therm_id_1;
    // }
    // if (ACUInterfaceInstance::instance().get_latest_data().therm_id_2 < _ccu_data.min_cell_temp) {
    //     _ccu_data.min_cell_temp = ACUInterfaceInstance::instance().get_latest_data().therm_id_2;
    // }

    Display.print("Min Cell Temp:  ");
    Display.println(ACUInterfaceInstance::instance().get_latest_data().min_cell_temp, 3);

}

void DisplaySystem::refresh_display_data(unsigned long curr_millis) {

    if ((curr_millis - display_time) >= display_update_interval) {
        Display.fillScreen(ILI9341_BLACK);
        display_time = curr_millis;
    }
}