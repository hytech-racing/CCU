#include "CCUCANBuffers.h"
#include "CCUCANInterface.h"
#include <cstdint>

// Include concrete interface definitions for method calls in ccu_CAN_recv
#include "ACUInterface.h"
#include "ChargerInterface.h"
#include "EMInterface.h"

namespace CCUCANInterface {

/* RX buffers */
CANRXBufferType charger_can_rx_buffer;
CANRXBufferType acu_can_rx_buffer;

/* TX buffers */
CANTXBufferType charger_can_tx_buffer;
CANTXBufferType acu_can_tx_buffer;


void ccu_CAN_recv(CANInterfaces &interfaces, const CAN_message_t &msg, unsigned long millis) {
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
void on_acu_can_receive(const CAN_message_t &msg) {
    uint8_t buf[sizeof(CAN_message_t)];
    memmove(buf, &msg, sizeof(msg)); // NOLINT (decay of array to pointer)
    acu_can_rx_buffer.push_back(buf, sizeof(CAN_message_t));
}

void on_charger_can_receive(const CAN_message_t &msg) {
    uint8_t buf[sizeof(CAN_message_t)];
    memmove(buf, &msg, sizeof(msg)); // NOLINT (decay of array to pointer)
    charger_can_rx_buffer.push_back(buf, sizeof(CAN_message_t));
}


void send_all_CAN_msgs(CANTXBufferType &buffer, FlexCAN_T4_Base *can_interface) {
    CAN_message_t msg;
    while (buffer.available()) {
        CAN_message_t msg;
        uint8_t buf[sizeof(CAN_message_t)];
        buffer.pop_front(buf, sizeof(CAN_message_t));
        memmove(&msg, buf, sizeof(msg)); // NOLINT (decay of array to pointer)
        can_interface->write(msg);
    } 
}


} // namespace CCUCANInterface
