#include "EthernetInterface.h"
#include <algorithm>
#include <cstddef>



//This is the start of ethernet interface function not implemented yet


//take the values from the protobuf message and update CCUInput_s 

void ethernetInterface::recieve_pb_msg_acu_all_data(hytech_msgs_ACUAllData_s &msg_in, CCUInput_s &inputValues){

    float *ccu_msg_in_max_volts = std::max_element(msg_in.voltages, msg_in.voltages + msg_in.voltages_count);
    inputValues.max_cell_voltage = *ccu_msg_in_max_volts;

    float *ccu_msg_in_max_temp = std::max_element(msg_in.cell_temperatures, msg_in.cell_temperatures + msg_in.cell_temperatures_count);
    inputValues.max_cell_temperature = *ccu_msg_in_max_temp;
}


void ethernetInterface::receive_pb_msg_acu_core_data(const hytech_msgs_ACUCoreData_s &msg_in, CCUInput_s &inputValues)
{
    inputValues.max_cell_voltage = msg_in.min_cell_voltage;
}