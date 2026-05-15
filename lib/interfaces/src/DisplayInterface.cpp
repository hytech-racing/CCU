#include "DisplayInterface.h"

void DisplayInterface::init() 
{
    Display.begin();
    Display.setRotation(3);
    Display.setTextSize(2);
    Display.fillScreen(ILI9341_BLACK);
}

void DisplayInterface::display_data(bool is_120_switched) 
{
    Display.fillScreen(ILI9341_BLACK);
    Display.setCursor(0,0);
    Display.setRotation(3);
    Display.setTextSize(2);

    // Display.println("Charging Status: ");

    // if (_ccu_data.charging_state == ChargingState_e::CHARGING) { // logic with voltage
    //     Display.print("Charging at  ");
    //     Display.println(_ccu_data.calculated_charge_current);
    // } else if (_ccu_data.charging_state == ChargingState_e::DONE_CHARGING) {
    //     Display.println("Done charging!");
    // } else {
    //     Display.println("Not Charging");
    // }

    Display.print("Set to "); Display.print(is_120_switched ? "120" : "240"); Display.println("V Charging"); 

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
    Display.println(ACUInterfaceInstance::instance().get_latest_data().max_cell_temp, 3);

    Display.print("Min Cell Temp (C): ");
    Display.println(ACUInterfaceInstance::instance().get_latest_data().min_cell_temp, 3);

    Display.print("Avg Cell Temp (C): ");
    Display.println((ACUInterfaceInstance::instance().get_latest_data().max_cell_temp + ACUInterfaceInstance::instance().get_latest_data().min_cell_temp)/2, 3);

    Display.print("EM current (A): ");
    Display.println(EnergyMeterInterfaceInstance::instance().get_latest_em_data().current_amps, 3);
}

void DisplayInterface::refresh_display_data(unsigned long curr_millis) 
{
    if ((curr_millis - _display_time) >= _config.display_update_interval_ms) 
    {
        _display_time = curr_millis;
    }
}
// function that displays data depending on the count of clicks
void DisplayInterface::toggle_display_data() 
{

    Display.setCursor(0,0);
    
    if (clicks > 4) 
    {
        clicks = 0;
    }
    
    switch (clicks)
    {
        default:
            display_data();
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
        // same content as display_data_v function but modified to show ICs 7-12
            Display.fillScreen(ILI9341_BLACK);
            Display.setCursor(0,0);
            Display.setRotation(3);
            Display.setTextSize(1);
            Display.println("Detailed Voltages");
            Display.print("\n");
            for(int ic = MAX_ICS_Voltage_Screen1; ic < MAX_ICS_Voltage_Screen2; ic++){
                    Display.print("Cell ");
                    Display.print(ic+1);
                    Display.print(":    ");
                    for (int i = 0; i < MAX_IC_INDEX; i++){
                        Display.print(ACUInterfaceInstance::instance().get_latest_data().voltage_array[ic][i], 3);
                        Display.print(" ");
                    }
                    Display.print("\n");
                    Display.print("\n"); 
            }
            break;

    }
}

void DisplayInterface::setup_button_pin(uint8_t pin) {
    pinMode(pin, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(pin), DisplayInterface::button_func, FALLING);
}

void DisplayInterface::button_func() {
    static unsigned long last_interrupt_time = 0;
    unsigned long interrupt_time = millis();
    if (interrupt_time - last_interrupt_time > debounce_time) {
        DisplayInterfaceInstance::instance().clicks++;
        last_interrupt_time = interrupt_time;
    }
}
