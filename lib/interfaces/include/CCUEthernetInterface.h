#ifndef __ETHERNETINTERFACE_H__
#define __ETHERNETINTERFACE_H__


#include "hytech_msgs.pb.h"
#include "SharedFirmwareTypes.h"
#include <vector>

struct CCUOutput_s 
//Output values struct (what CCU is sending out)
{
    bool current_flow;
    float current_setpoint;
    bool allow_balance;
};


namespace CCUEthernetInterface
{
    void recieve_pb_msg_acu_all_data(const hytech_msgs_ACUAllData_s &msg_in, ACUAllData_s &acu_all_data); 
};
#endif