#ifndef __ETHERNETINTERFACE_H__
#define __ETHERNETINTERFACE_H__


//#include "hytech_msgs.pb.h" - commented out just to pass github checks

//WHAT ETHERERNET INTERFACE NEEDS TO DO
//1. get the protobuf message 2. map the values to a struct 3. send out those values to main charge sys

//1. take CCUOutputValues struct and make into protobuf message or CAN 2. send the values out to ams (I think this can be done through shared firmware interfaces include)

struct CCUInput_s //I think this is correct but i dont know if i need to account for all the values in the protobuf message struct
{
    float max_cell_temperature = 0; //in degress C
    float max_cell_voltage = 0; //in Volts
};

struct CCUOutput_s
//Output values struct (what CCU is sending out)
{
    bool current_flow;
    float current_setpoint;
    bool allow_balance;
};

namespace ethernetInterface{

    void recieve_pb_msg_acu_all_data(hytech_msgs_ACUAllData_s &msg_in, CCUInput_s &inputValues); 
};
#endif