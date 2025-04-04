#ifndef CCUCANINTERFACEIMPL
#define CCUCANINTERFACEIMPL

#include "CANInterface.h"

#include "ACUInterface.h"
#include "ChargerInterface.h"

#include "etl/singleton.h"
#include "FlexCAN_T4.h"

#include "hytech.h" // generated CAN library

using CANRXBufferType = Circular_Buffer<uint8_t, (uint32_t)16, sizeof(CAN_message_t)>;
using CANTXBufferType = Circular_Buffer<uint8_t, (uint32_t)128, sizeof(CAN_message_t)>;

template <CAN_DEV_TABLE CAN_DEV> using FlexCAN_Type = FlexCAN_T4<CAN_DEV, RX_SIZE_256, TX_SIZE_16>;

struct CANInterfaces
{
    explicit CANInterfaces(ACUInterface &acu_int, ChargerInterface &charger_int) :
        acu_interface(acu_int), 
        charger_interface(charger_int) {}

    ACUInterface & acu_interface;
    ChargerInterface & charger_interface;
};

using CANInterfacesInstance = etl::singleton<CANInterfaces>;

namespace CCUCANInterfaceImpl
{
    extern CANRXBufferType charger_can_rx_buffer;
    extern CANRXBufferType acu_can_rx_buffer;

    /* TX buffer for Charger CAN */
    extern CANTXBufferType charger_can_tx_buffer;
    /* TX buffer for ACU CAN */
    extern CANTXBufferType acu_can_tx_buffer;

    extern FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> CHARGER_CAN; // gets defined in main as of right now
    extern FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> ACU_CAN; // gets defined in main as of right now       

    void on_acu_can_receive(const CAN_message_t &msg);
    void on_charger_can_receive(const CAN_message_t &msg);

    void ccu_CAN_recv(CANInterfaces &interfaces, const CAN_message_t &msg, unsigned long millis);

    void send_all_CAN_msgs(CANTXBufferType &buffer, FlexCAN_T4_Base *can_interface);
    
}; // namespace CCUCANInterfaceImpl

#endif // CCUCANINTERFACEIMPL