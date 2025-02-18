#ifndef __ETHERNETINTERFACE_H__
#define __ETHERNETINTERFACE_H__

//WHAT ETHERERNET INTERFACE NEEDS TO DO
//1. get the protobuf message 2. map the values to a struct 3. send out those values to main charge sys   

struct CCUInputValues //I think this is correct but i dont know if i need to account for all the values in the protobuf message struct
{
    float maxCellTemp; //in degress C
    float maxCellV; //in Volts
};

struct CCUOutputValues
{
    bool currentFlow;
};

class EthernetInterface{
public:
    EthernetInterface();
    CCUInputValues UpdatingValues();

private:
    CCUInputValues inputValues;
    CCUInputValues val;
};
#endif