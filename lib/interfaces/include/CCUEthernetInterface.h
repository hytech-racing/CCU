#ifndef __ETHERNETINTERFACE_H__
#define __ETHERNETINTERFACE_H__


#include "hytech_msgs.pb.h"
#include "SharedFirmwareTypes.h"
#include <vector>

//WHAT ETHERERNET INTERFACE NEEDS TO DO
//1. get the protobuf message 2. map the values to a struct 3. send out those values to main charge sys

//1. take CCUOutputValues struct and make into protobuf message or CAN 2. send the values out to ams (I think this can be done through shared firmware interfaces include)
struct CCUOutput_s
//Output values struct (what CCU is sending out)
{
    bool current_flow;
    float current_setpoint;
    bool allow_balance;
};

namespace ethernetInterface{

    void recieve_pb_msg_acu_all_data(const hytech_msgs_ACUAllData_s &msg_in, ACUAllData_s &acu_all_data); 
};
#endif