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

    switch (_display_view)
    {
        case DisplayView_e::VIEW_CHARGE_STATUS:
        {
            Display.setTextSize(2);
            Display.print("Set to "); Display.print(is_120_switched ? "120" : "240"); Display.println("V Charging"); 
            Display.print("CCU in state -> "); Display.println(ChargerStateMachineInstance::instance().get_state_name());
            Display.print("Cell Voltage max: ");
            Display.println(ACUInterfaceInstance::instance().get_latest_data().high_voltage, 3);
            Display.print("Cell Voltage min: ");
            Display.println(ACUInterfaceInstance::instance().get_latest_data().low_voltage, 3);
            Display.print("Cell Voltage avg: ");
            Display.println(ACUInterfaceInstance::instance().get_latest_data().average_voltage, 3);
            Display.print("Cell Voltage delta: ");
            Display.println((ACUInterfaceInstance::instance().get_latest_data().high_voltage - ACUInterfaceInstance::instance().get_latest_data().low_voltage), 3);
            Display.print("Total pack Volts: ");
            Display.println(ACUInterfaceInstance::instance().get_latest_data().pack_voltage, 3);
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

            break;
        }
        case DisplayView_e::VIEW_CHARGER:
        {
            auto charger_data = ChargerInterfaceInstance::instance().get_latest_charger_data();
            auto dc_output_V = (charger_data.output_dc_voltage_high << 8 | charger_data.output_dc_voltage_low) / 10.0F;
            auto ac_input_V = (charger_data.input_ac_voltage_high << 8 | charger_data.input_ac_voltage_low) / 10.0F;
            auto current_output_A = (charger_data.output_current_high << 8 | charger_data.output_current_low) / 10.0F;

            Display.setTextSize(2);

            Display.print("Charger Output Current (A): ");
            Display.println(current_output_A, 2);
            Display.print("Charger DC Output Voltage (V): ");
            Display.println(dc_output_V, 2);
            Display.print("Charger AC Input Voltage (V): ");
            Display.println(ac_input_V, 2);
            Display.print("EM current (A): ");
            Display.println(EnergyMeterInterfaceInstance::instance().get_latest_em_data().current_amps, 3);

            break;
        }
        case DisplayView_e::VIEW_VOLTAGE:
        {
            auto cell_voltages = ACUInterfaceInstance::instance().get_latest_data().cell_voltages;

            Display.setTextSize(1);

            constexpr size_t cells_per_row = 3;
            constexpr size_t rows_per_page = 14;
            constexpr size_t cells_per_page =
                cells_per_row * rows_per_page;

            constexpr size_t total_cells = default_acu_params::NUM_CELLS;

            constexpr size_t total_rows = (total_cells + cells_per_row - 1) / cells_per_row;

            static size_t start_row = 0;

            const size_t start_index = start_row * cells_per_row;

            for (size_t i = 0; i < cells_per_page; i++)
            {
                const size_t idx = start_index + i;

                if (idx >= total_cells)
                {
                    break;
                }

                Display.print("C");
                Display.print(idx);
                Display.print(":");

                if (cell_voltages[idx].has_value())
                {
                    Display.print(cell_voltages[idx].value(), 3);
                }
                else
                {
                    Display.print("----");
                }

                if ((i + 1) % cells_per_row == 0)
                {
                    Display.println();
                }
                else
                {
                    Display.print(" ");
                }
            }

            start_row++;

            if (start_row >= total_rows)
            {
                start_row = 0;
            }

            break;
        }
        case DisplayView_e::VIEW_BOARD_TEMPERATURE:
        {
            auto board_temps = ACUInterfaceInstance::instance().get_latest_data().board_temps;

            Display.setTextSize(1);

            constexpr size_t temps_per_row = 3;

            for (size_t row = 0; row < default_acu_params::NUM_BOARD_TEMPS / temps_per_row; row++)
            {
                for (size_t col = 0; col < temps_per_row; col++)
                {
                    size_t bt_index = (row * temps_per_row) + col;
                    Display.print("BT");
                    Display.print(bt_index);
                    Display.print(": ");
                    if (*board_temps[bt_index])
                    {
                        Display.print(*board_temps[bt_index], 3);
                    }
                    else
                    {
                        Display.print("--.-");
                    }
                }
                Display.println();
            }

            break;
        }
        case DisplayView_e::VIEW_CELL_TEMPERATURE:
        {
            auto cell_temps = ACUInterfaceInstance::instance().get_latest_data().cell_temps;

            Display.setTextSize(1);

            constexpr size_t temps_per_row = 3;

            for (size_t row = 0; row < default_acu_params::NUM_CELL_TEMPS / temps_per_row; row++)
            {
                for (size_t col = 0; col < temps_per_row; col++)
                {
                    size_t ct_index = (row * temps_per_row) + col;
                    Display.print("CT");
                    Display.print(ct_index);
                    Display.print(": ");
                    if (*cell_temps[ct_index])
                    {
                        Display.print(*cell_temps[ct_index], 3);
                    }
                    else
                    {
                        Display.print("--.-");
                    }
                    
                }
                Display.println();
            }

            break;
        }
        default:
        {
            break;
        }
    }
}

void DisplayInterface::refresh_display_data(unsigned long curr_millis) 
{
    if ((curr_millis - _display_time) >= _config.display_update_interval_ms) 
    {
        _display_time = curr_millis;
    }
}

void DisplayInterface::update(unsigned long current_millis)
{
    _cycle_display_view_button.update(current_millis);
    handle_button_events(current_millis);
}

void DisplayInterface::handle_button_events(unsigned long current_millis)
{
    if (_cycle_display_view_button.get_hold_duration_ms(current_millis) > _config._cycle_button_hold_time_reset_ms)
    {
        _display_view = DisplayView_e::VIEW_CHARGE_STATUS;
        return;
    }
    
    if (_cycle_display_view_button.is_pressed())
    {
        cycle_view();
    }
}

void DisplayInterface::cycle_view()
{ 
    _display_view = static_cast<DisplayView_e>((static_cast<size_t>(_display_view) + 1) % DisplayView_e::NUM_VIEWS);
}