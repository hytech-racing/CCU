#include "CCUEthernetInterface.h"

/* External Dependencies */
#include <algorithm>
#include <cstddef>


//take the values from the protobuf message and update CCUInput_s

void CCUEthernetInterface::recieve_pb_msg_acu_all_data(const hytech_msgs_ACUAllData_s &msg_in, ACUAllDataType_s &acu_all_data)
{
    for (uint32_t i = 0; i < msg_in.voltages_count; ++i) //NOLINT protoc struct is an array of floats
    {
        acu_all_data.cell_voltages[i] = msg_in.voltages[i]; //NOLINT should be passed in as normal voltage based on vcr // is this correct?? called voltages before
    }
    for (uint32_t i = 0; i < msg_in.cell_temperatures_count; ++i) //NOLINT vcr said so
    {
        acu_all_data.cell_temps[i] = msg_in.cell_temperatures[i]; //NOLINT vcr said so
    }
}