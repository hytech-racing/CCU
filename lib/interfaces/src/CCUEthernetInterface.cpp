#include "CCUEthernetInterface.h"
#include <algorithm>
#include <cstddef>



//This is the start of ethernet interface function not implemented yet


//take the values from the protobuf message and update CCUInput_s 

void ethernetInterface::recieve_pb_msg_acu_all_data(hytech_msgs_ACUAllData_s &msg_in, CCUInput_s &inputValues){

    inputValues.max_cell_voltage = *std::max_element(msg_in.voltages, msg_in.voltages + msg_in.voltages_count);

    inputValues.max_cell_temperature = *std::max_element(msg_in.cell_temperatures, msg_in.cell_temperatures + msg_in.cell_temperatures_count);

}