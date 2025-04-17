#ifndef CHARGERINTERFACE_H
#define CHARGERINTERFACE_H

#include "FlexCAN_T4.h"
#include "hytech.h"
#include "SharedFirmwareTypes.h"
#include "CANInterface.h"
#include "etl/singleton.h"
#include <etl/delegate.h>
#include "CCUParams.h"


struct charger_data_s {
    uint8_t output_dc_voltage_high;
    uint8_t output_dc_voltage_low;
    uint8_t output_current_high;
    uint8_t output_current_low;
    uint8_t flags;
    uint8_t input_ac_voltage_high;
    uint8_t input_ac_voltage_low;
};


class ChargerInterface
{

public:

    void receive_charger_data_message(const CAN_message_t& msg, unsigned long curr_millis);

    void send_charger_message();

    void enqueue_charging_data();

    charger_data_s get_latest_charger_data() {return _curr_charger_data;};

private:
    charger_data_s _curr_charger_data;

};

using ChargerInterfaceInstance = etl::singleton<ChargerInterface>;


#endif /* CHARGERINTERFACE_H */