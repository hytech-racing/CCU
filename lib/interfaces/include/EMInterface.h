#ifndef EMINTERFACE
#define EMINTERFACE

#include "FlexCAN_T4.h"

#include "etl/singleton.h"
#include <etl/delegate.h>



struct energy_meter_data_s {
    float voltage;
    float current_amps;
};


class EnergyMeterInterface
{

public:

    EnergyMeterInterface()= default;

    void receive_energy_meter_message(const CAN_message_t& msg, unsigned long curr_millis);


    energy_meter_data_s get_latest_em_data() {return _em_data;};

private:
    energy_meter_data_s _em_data;
    

};

using EnergyMeterInterfaceInstance = etl::singleton<EnergyMeterInterface>;


#endif /* EMINTERFACE */