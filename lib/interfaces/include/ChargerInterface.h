#ifndef CHARGERINTERFACE_H
#define CHARGERINTERFACE_H

#include "FlexCAN_T4.h"
#include "hytech.h"
#include "SharedFirmwareTypes.h"
#include "etl/singleton.h"

class ChargerInterface
{
    public:
    void receive_charger_data_message(const CAN_message_t& msg, unsigned long curr_millis);

    void send_charger_message();

    private:
    CHARGER_DATA_t _curr_data = {};
};

using ChargerInterfaceInstance = etl::singleton<ChargerInterface>;


#endif /* CHARGERINTERFACE_H */