#ifndef CCUETHERNETINTERFACE_H
#define CCUETHERNETINTERFACE_H

#include "hytech_msgs.pb.h"
#include "SharedFirmwareTypes.h"

/**
 * Output values from CCU to ACU.
 */
struct CCUOutput_s 
{
    float current_setpoint;
    bool allow_balance;
};


namespace CCUEthernetInterface
{
    void recieve_pb_msg_acu_all_data(const hytech_msgs_ACUAllData_s &msg_in, ACUAllData_s &acu_all_data); 
};
#endif