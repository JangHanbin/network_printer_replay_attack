#ifndef HOSTDETECTOR_H
#define HOSTDETECTOR_H

#include <tins/tins.h>
#include <map>

using namespace Tins;

//This class maybe can extend

class HostDetector
{
    std::map<IPv4Address, HWAddress<6>> addresses;

    SnifferConfiguration config;
    Sniffer *sniffer;
    IPv4Address local_ip;
    IPv4Range *local_network;

public:
    HostDetector(IPv4Address ipv4, char *iface);
    ~HostDetector();
    IPv4Address getLocalIpAddr();
    void run();
    bool scan(const PDU &pdu);
    IPv4Range getLocal_network() const;
    void setLocal_network(IPv4Address net_addr);        //This function for C class
};


#endif // HOSTDETECTOR_H
