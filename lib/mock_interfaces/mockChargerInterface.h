#ifndef CHARGERINTERFACE_H
#define CHARGERINTERFACE_H

#include "hytech.h"
#include "SharedFirmwareTypes.h"
#include "etl/singleton.h"
#include <etl/delegate.h>
#include "CCUData.h"


struct charger_data_s {
    uint8_t output_current_high;
};


class ChargerInterface
{

public:

    ChargerInterface(CCUData &ccu_data) :  _ccu_data(ccu_data) {};

    void set_charger_latest_data(charger_data_s data) {
        _curr_charger_data = data;
    }

    charger_data_s get_latest_charger_data() {return _curr_charger_data;};

private:
    charger_data_s _curr_charger_data;
    CCUData &_ccu_data;

};

using ChargerInterfaceInstance = etl::singleton<ChargerInterface>;


#endif /* CHARGERINTERFACE_H */