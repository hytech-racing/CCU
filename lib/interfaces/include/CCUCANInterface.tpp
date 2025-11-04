#include "CCUCANInterface.h"

template<size_t num_cells, size_t num_celltemps, size_t num_chips>
void CCUCANInterface::ccu_CAN_recv(CANInterfaces<num_cells, num_celltemps, num_chips> &interfaces, const CAN_message_t &msg, unsigned long millis) {
    switch (msg.id) {
    case BMS_VOLTAGES_CANID: 
    {
        interfaces.acu_interface.receive_voltage_statistics_message(msg, millis);
        break;
    }
    case BMS_STATUS_CANID:
    {
        interfaces.acu_interface.receive_status_message(msg, millis);
        break;
    }
    case CHARGER_DATA_CANID:
    {
        interfaces.charger_interface.receive_charger_data_message(msg, millis);
        break;
    }
    case BMS_ONBOARD_TEMPS_CANID:
    {
        interfaces.acu_interface.receive_temp_statistics_message(msg, millis);
        break;
    }
    case BMS_CHIP_TEMPS_CANID:
    {
        interfaces.acu_interface.receive_cell_group_temps_message(msg, millis);
        break;
    }
    case BMS_ONBOARD_CURRENT_TEMP_CANID:
    {
        interfaces.acu_interface.receive_board_temps(msg, millis);
        break;
    }
    case EM_MEASUREMENT_CANID:
    {
        interfaces.em_interface.receive_energy_meter_message(msg, millis);
        break;
    }
    default:
    {
        break;
    }

    }
}
