#include "CCUEthernetInterface.h"
#include <algorithm>
#include <cstddef>



//take the values from the protobuf message and update CCUInput_s 

void CCUEthernetInterface::recieve_pb_msg_acu_all_data(const hytech_msgs_ACUAllData_s &msg_in, ACUAllData_s &acu_all_data)
{
    for (uint32_t i = 0; i < msg_in.voltages_count; ++i) //NOLINT protoc struct is an array of floats
    { 
        acu_all_data.voltages[i] = msg_in.voltages[i]; //NOLINT should be passed in as normal voltage based on vcr
    }
    for (uint32_t i = 0; i < msg_in.cell_temperatures_count; ++i) //NOLINT
    {
        acu_all_data.cell_temperatures[i] = msg_in.cell_temperatures[i]; //NOLINT
    }
}