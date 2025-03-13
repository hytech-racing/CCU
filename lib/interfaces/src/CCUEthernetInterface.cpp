#include "CCUEthernetInterface.h"
#include <algorithm>
#include <cstddef>



//This is the start of ethernet interface function not implemented yet


//take the values from the protobuf message and update CCUInput_s 

void ethernetInterface::recieve_pb_msg_acu_all_data(const hytech_msgs_ACUAllData_s &msg_in, ACUAllData_s &acu_all_data){

    for (uint32_t i = 0; i < msg_in.voltages_count; ++i){
        acu_all_data.voltages[i] = msg_in.voltages[i];
    }
    for (uint32_t i = 0; i < msg_in.cell_temperatures_count; ++i){
        acu_all_data.cell_temperatures[i] = msg_in.cell_temperatures[i];
    }
}