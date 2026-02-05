#include "DisplayInterface.h"
#include "CCUData.h"
#include "EMInterface.h"


extern unsigned long button_state = 0;
extern unsigned long last_button_state = 0;
extern unsigned long clicks = 0;

void DisplayInterface::init() {
    Display.begin();
    Display.setRotation(3);
    Display.setTextSize(2);
    Display.fillScreen(ILI9341_BLACK);
}

void DisplayInterface::display_data() {
    Display.fillScreen(ILI9341_BLACK);
    Display.setCursor(0,0);
    Display.setRotation(3);
    Display.setTextSize(2);

    Display.println("Charging Status: ");

    if (_ccu_data.charging_state == ChargingState_e::CHARGING) {
        Display.print("Charging at  ");
        Display.println(_ccu_data.calculated_charge_current);
    } else if (_ccu_data.charging_state == ChargingState_e::DONE_CHARGING) {
        Display.println("Done charging!");
    } else {
        Display.println("Not Charging");
    }
    

    Display.print("Cell Voltage max: ");
    Display.println(ACUInterfaceInstance::instance().get_latest_data().high_voltage, 3);

   
    Display.print("Cell Voltage min: ");
    Display.println(ACUInterfaceInstance::instance().get_latest_data().low_voltage, 3);
 

    Display.print("Cell Voltage avg: ");
    Display.println(ACUInterfaceInstance::instance().get_latest_data().average_voltage, 3);


    Display.print("Cell Voltage delta: ");
    Display.println((ACUInterfaceInstance::instance().get_latest_data().high_voltage - ACUInterfaceInstance::instance().get_latest_data().low_voltage), 3);


    Display.print("Total pack Volts: ");
    Display.println(ACUInterfaceInstance::instance().get_latest_data().total_voltage, 3);


    Display.print("Max Board Temp (C): ");
    Display.println(ACUInterfaceInstance::instance().get_latest_data().max_board_temp, 3);

    
    Display.print("Max Cell Temp (C): ");
    //Display.println(_ccu_data.max_cell_temp, 3); 
    Display.println(ACUInterfaceInstance::instance().get_latest_data().max_cell_temp, 3);


    Display.print("Min Cell Temp (C): ");
    Display.println(ACUInterfaceInstance::instance().get_latest_data().min_cell_temp, 3);

    Display.print("Avg Cell Temp (C): ");
    Display.println((ACUInterfaceInstance::instance().get_latest_data().max_cell_temp + ACUInterfaceInstance::instance().get_latest_data().min_cell_temp)/2, 3);

    Display.print("EM current (A): ");
    Display.println(EnergyMeterInterfaceInstance::instance().get_latest_em_data().current_amps, 3);
    

}
// function that displays cell temps from BMS
void DisplayInterface::display_data_temps() {
    Display.fillScreen(ILI9341_BLACK);
    Display.setCursor(0,0);
    Display.setRotation(3);
    Display.setTextSize(2);
    Display.println("Cell Temps");
   
    for (int ic = 1; ic < 13; ic++){
        Display.print("Cell ");
        Display.print(ic);
        Display.print(": ");
        Display.print(ACUInterfaceInstance::instance().get_latest_data().cell_temps[ic-1][0], 3);
        Display.print(" ");
        Display.print(ACUInterfaceInstance::instance().get_latest_data().cell_temps[ic-1][1], 3);
        Display.print(" ");
        Display.println(ACUInterfaceInstance::instance().get_latest_data().cell_temps[ic-1][2], 3);
    }

}

//function that displays voltage values
void DisplayInterface::display_data_v(){
    Display.fillScreen(ILI9341_BLACK);
    Display.setCursor(0,0);
    Display.setRotation(3);
    Display.setTextSize(2);
    Display.println("Detailed Voltages");
    Display.print("\n");

// may need to be adjusted to fit on display/
// need to be fixed: there are 12 ICs even ones have 12 reading odd have 9; three eahc group has 3 readings
    for(int ic = 1; ic < 4; ic++){
        Display.print("Cell ");
        Display.print(ic);
        Display.print(":");
        for (int i = 0; i < 12; i++){
            Display.print(ACUInterfaceInstance::instance().get_latest_data().voltage_array[ic-1][i], 3);
            Display.print(" ");
        }
        Display.print("\n");
        Display.print("\n"); 
}
}

void DisplayInterface::refresh_display_data(unsigned long curr_millis) {

    if ((curr_millis - display_time) >= display_update_interval) {
        // Display.fillScreen(ILI9341_BLACK);
        display_time = curr_millis;
    }
}

void DisplayInterface::toggle_display_data() 
{

    Display.setCursor(0,0);
    
    if (clicks > 6) 
    {
        clicks = 0;
    }
    
    switch (clicks)
    {
        default:
            //print critical charging data
            Display.fillScreen(ILI9341_BLACK);
            Display.setCursor(0,0);
            Display.setRotation(3);
            Display.setTextSize(2);
            Display.println("Charging Status: ");

            if (_ccu_data.charging_state == ChargingState_e::CHARGING) {
                Display.print("Charging at  ");
                Display.println(_ccu_data.calculated_charge_current);
            } else if (_ccu_data.charging_state == ChargingState_e::DONE_CHARGING) {
                Display.println("Done charging!");
            } else {
                Display.println("Not Charging");
            }
            Display.print("\n");
            Display.print("\n");
            Display.print("Max Board Temp (C): ");
            Display.println(ACUInterfaceInstance::instance().get_latest_data().max_board_temp, 3);

            
            Display.print("Max Cell Temp (C): ");
            //Display.println(_ccu_data.max_cell_temp, 3); 
            Display.println(ACUInterfaceInstance::instance().get_latest_data().max_cell_temp, 3);


            Display.print("Min Cell Temp (C): ");
            Display.println(ACUInterfaceInstance::instance().get_latest_data().min_cell_temp, 3);

            Display.print("Avg Cell Temp (C): ");
            Display.println((ACUInterfaceInstance::instance().get_latest_data().max_cell_temp + ACUInterfaceInstance::instance().get_latest_data().min_cell_temp)/2, 3);

            Display.print("EM current (A): ");
            Display.println(EnergyMeterInterfaceInstance::instance().get_latest_em_data().current_amps, 3);
            break;
        case 1:
            Display.fillScreen(ILI9341_BLACK);
            Display.setCursor(0,0);
            Display.setRotation(3);
            Display.setTextSize(2);
            Display.print("Cell Voltage max: ");
            Display.println(ACUInterfaceInstance::instance().get_latest_data().high_voltage, 3);

        
            Display.print("Cell Voltage min: ");
            Display.println(ACUInterfaceInstance::instance().get_latest_data().low_voltage, 3);
        

            Display.print("Cell Voltage avg: ");
            Display.println(ACUInterfaceInstance::instance().get_latest_data().average_voltage, 3);


            Display.print("Cell Voltage delta: ");
            Display.println((ACUInterfaceInstance::instance().get_latest_data().high_voltage - ACUInterfaceInstance::instance().get_latest_data().low_voltage), 3);


            Display.print("Total pack Volts: ");
            Display.println(ACUInterfaceInstance::instance().get_latest_data().total_voltage, 3);
            break;
        case 2: 
            display_data_temps();
            break;
        case 3:
            display_data_v();
            break;
        case 4: 
            Display.fillScreen(ILI9341_BLACK);
            Display.setCursor(0,0);
            Display.setRotation(3);
            Display.setTextSize(2);
            Display.println("Detailed Voltages");
            Display.print("\n");
            for(int ic = 4; ic < 7; ic++){
                    Display.print("Cell ");
                    Display.print(ic);
                    Display.print(":");
                    for (int i = 0; i < 12; i++){
                        Display.print(ACUInterfaceInstance::instance().get_latest_data().voltage_array[ic-1][i], 3);
                        Display.print(" ");
                    }
                    Display.print("\n");
                    Display.print("\n"); 
            }
        case 5:
            Display.fillScreen(ILI9341_BLACK);
            Display.setCursor(0,0);
            Display.setRotation(3);
            Display.setTextSize(2);
            Display.println("Detailed Voltages");
            Display.print("\n");

        // may need to be adjusted to fit on display/
        // need to be fixed: there are 12 ICs even ones have 12 reading odd have 9; three eahc group has 3 readings
            for(int ic = 7; ic < 10; ic++){
                Display.print("Cell ");
                Display.print(ic);
                Display.print(":");
                for (int i = 0; i < 12; i++){
                    Display.print(ACUInterfaceInstance::instance().get_latest_data().voltage_array[ic-1][i], 3);
                    Display.print(" ");
                }
                Display.print("\n");
                Display.print("\n"); 
        }
        case 6: 
            Display.fillScreen(ILI9341_BLACK);
            Display.setCursor(0,0);
            Display.setRotation(3);
            Display.setTextSize(2);
            Display.println("Detailed Voltages");
            Display.print("\n");

        // may need to be adjusted to fit on display/
        // need to be fixed: there are 12 ICs even ones have 12 reading odd have 9; three eahc group has 3 readings
            for(int ic = 10; ic < 13; ic++){
                Display.print("Cell ");
                Display.print(ic);
                Display.print(":");
                for (int i = 0; i < 12; i++){
                    Display.print(ACUInterfaceInstance::instance().get_latest_data().voltage_array[ic-1][i], 3);
                    Display.print(" ");
                }
                Display.print("\n");
                Display.print("\n"); 
        }

    }
}

