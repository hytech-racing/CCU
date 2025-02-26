#ifndef __ETHERNETINTERFACE_H__
#define __ETHERNETINTERFACE_H__

//WHAT ETHERERNET INTERFACE NEEDS TO DO
//1. get the protobuf message 2. map the values to a struct 3. send out those values to main charge sys

//1. take CCUOutputValues struct and make into protobuf message 2. send the values out to ams

struct CCUInput_s //I think this is correct but i dont know if i need to account for all the values in the protobuf message struct
{
    float max_cell_temperature; //in degress C
    float max_cell_voltage; //in Volts
};

struct CCUOutput_s
//Output values struct (what CCU is sending out)
{
    bool current_flow;
    float current_setpoint;
};

class EthernetInterface{
public:
    EthernetInterface();
    void updating_values(CCUInput_s &msg_in);

private:
    CCUInput_s inputValues;
};
#endif