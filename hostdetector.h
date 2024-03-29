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
    PacketSender sender;
    NetworkInterface iface;
    Sniffer *sniffer;
    IPv4Address local_ip;
    IPv4Range *local_network;

    bool condition=true;

public:
    HostDetector(IPv4Address ipv4);
    ~HostDetector();
    IPv4Address getLocalIpAddr();
    HWAddress<6> getLocalMacAddr();

    void run();
    bool scan(const PDU &pdu);
    void hostPrinter();
    void askHost();
    void semaphore();

    IPv4Range getLocal_network() const;
    void setLocal_network(IPv4Address net_addr);        //This function for C class
    std::map<IPv4Address, HWAddress<6> > getAddresses() const;
};


#endif // HOSTDETECTOR_H
