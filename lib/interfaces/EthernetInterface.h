#ifndef __ETHERNETINTERFACE_H__
#define __ETHERNETINTERFACE_H__

struct EthernetInterface
{
    float maxCellTemp; //in degress C
    float maxCellV; //in Volts
    bool currentFlow;
};
#endif