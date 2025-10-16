#include "DisplayInterface.h"
#include "CCUData.h"
#include "EMInterface.h"

//unsigned long buttonState = digitalRead(17);

//void loop() {
//    buttonState = digitalRead(17);

//}

extern int button_state = 0;
extern int last_button_state = 0;
extern int clicks = 0;

void DisplayInterface::init() {
    Display.begin();
    Display.setRotation(3);
    Display.setTextSize(2);
    Display.fillScreen(ILI9341_BLACK);
    //pinMode(17, INPUT_PULLDOWN);
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

void DisplayInterface::refresh_display_data(unsigned long curr_millis) {

    if ((curr_millis - display_time) >= display_update_interval) {
        // Display.fillScreen(ILI9341_BLACK);
        display_time = curr_millis;
    }
}

void DisplayInterface::toggle_display_data() 
{
    //button_state = digitalRead(17);
    //button_state = digitalRead(17);
    Display.fillScreen(ILI9341_BLACK);
    Display.setCursor(0,0);

    if (button_state != last_button_state)
    {

        if (button_state == HIGH) 
        {
            clicks += 1;
        }

        //if (clicks > 20) 
        //{
        //    clicks = 0;
        //}
    }
    last_button_state = button_state;

    switch (clicks)
    {
        default:
            //print critical charging data
            Display.fillScreen(ILI9341_BLACK);
            Display.setCursor(0,0);
            Display.setRotation(3);
            Display.setTextSize(2);
            Display.println(clicks);
            break;
       /*case -1:            
            Display.setCursor(0,0);
            Display.setRotation(3);
            Display.setTextSize(2);
            Display.fillScreen(ILI9341_BLACK);
            Display.println("Cell Temps");
            break;
        case -2:
            Display.fillScreen(ILI9341_BLACK);
            Display.setCursor(0,0);
            Display.setRotation(3);
            Display.setTextSize(2);
            Display.println("Cell Voltages");
            break;*/
        
    }
}

