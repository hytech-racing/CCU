#ifndef CCUCANINTERFACE
#define CCUCANINTERFACE

#include "CANInterface.h"
#include "CCUCANBuffers.h"
#include "ChargerInterface.h"
#include "EMInterface.h"
#include "ACUInterface.h"
#include "etl/singleton.h"
#include <etl/delegate.h>
#include "FlexCAN_T4.h"

#include "hytech.h" // generated CAN library

// Provide a convenient alias for FlexCAN types used across the project
template <CAN_DEV_TABLE CAN_DEV> using FlexCAN_Type = FlexCAN_T4<CAN_DEV, RX_SIZE_256, TX_SIZE_16>;

struct CANInterfaces
{
    explicit CANInterfaces(ACUInterface &acu_int, ChargerInterface &charger_int, EnergyMeterInterface & em_int) :
        acu_interface(acu_int),
        charger_interface(charger_int),
        em_interface(em_int) {}

    ACUInterface & acu_interface;
    ChargerInterface & charger_interface;
    EnergyMeterInterface & em_interface;
};

using CANInterfacesInstance = etl::singleton<CANInterfaces>;

extern FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> CHARGER_CAN; // gets defined in main as of right now
extern FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> ACU_CAN;     // gets defined in main as of right now

namespace CCUCANInterface
{
    // Buffer externs are declared in CCUCANBuffers.h

    void on_acu_can_receive(const CAN_message_t &msg);
    void on_charger_can_receive(const CAN_message_t &msg);

    void ccu_CAN_recv(CANInterfaces &interfaces, const CAN_message_t &msg, unsigned long millis);

    void send_all_CAN_msgs(CANTXBufferType &buffer, FlexCAN_T4_Base *can_interface);
    
}; // namespace CCUCANInterface

#endif // CCUCANINTERFACE
