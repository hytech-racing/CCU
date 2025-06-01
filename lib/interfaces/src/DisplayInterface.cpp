#include "DisplayInterface.h"

void DisplayInterface::init() {
    Display.begin();
    Display.setRotation(3);
    Display.setTextSize(2);
    Display.fillScreen(ILI9341_BLACK);
}

void DisplayInterface::display_data() {

    Display.setCursor(0,0);
    Display.setRotation(3);
    Display.setTextSize(2);

    Display.println("Charging Status: ");

    if (_ccu_data.balancing_enabled) {
        Display.print("Charging at  ");
        Display.println(_ccu_data.calculated_charge_current);
    } else if (_display_data.high_voltage >= _ccu_data.cutoff_voltage || _display_data.total_pack_voltage >= _ccu_data.max_pack_voltage) {
        Display.println("Done charging!");
    } else {
        Display.println("Not Charging");
    }
    

    Display.print("Cell Voltage max: ");
    Display.println(_display_data.high_voltage, 3);

   
    Display.print("Cell Voltage min: ");
    Display.println(_display_data.low_voltage, 3);
 

    Display.print("Cell Voltage average: ");
    Display.println(_display_data.avg_voltage, 3);


    Display.print("Cell Voltage delta: ");
    Display.println((_display_data.high_voltage - _display_data.low_voltage), 3);


    Display.print("Total pack voltage: ");
    Display.println(_display_data.total_pack_voltage, 3);


    Display.print("Max Board Temp:  ");
    Display.println(_display_data.max_board_temp, 3);

    
    Display.print("Max Cell Temp:  ");
    Display.println(_display_data.max_cell_temp, 3);


    Display.print("Min Cell Temp:  ");
    Display.println(_display_data.min_cell_temp, 3);

}

void DisplayInterface::refresh_display_data(unsigned long curr_millis) {

    if ((curr_millis - display_time) >= display_update_interval) {
        Display.fillScreen(ILI9341_BLACK);
        display_time = curr_millis;
    }
}