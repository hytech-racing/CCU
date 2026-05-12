#ifndef CCUETHERNETINTERFACE_H
#define CCUETHERNETINTERFACE_H

/* External Dependencies*/
#include "hytech_msgs.pb.h"
#include "SharedFirmwareTypes.h"

/**
 * @brief Output values from CCU to ACU.
 */
struct CCUOutput_s
{
    float current_setpoint;
    bool allow_balance;
};

namespace CCUEthernetInterface
{
    void recieve_pb_msg_acu_all_data(const hytech_msgs_ACUAllData_s &msg_in, ACUAllDataType_s &acu_all_data);
};


#endif