#ifndef SPOOFER_H
#define SPOOFER_H
#include <tins/tins.h>
#include <map>

using namespace Tins;

class Spoofer
{
    PacketSender sender;
    NetworkInterface iface;

    HWAddress<6> local_mac;
    IPv4Address target_ip;
    bool condition=true;
public:
    Spoofer();
    void infector(std::map<IPv4Address, HWAddress<6>> addresses);
    IPv4Address getLocalIpAddr();
    EthernetII::address_type getMacAddr(IPv4Address unknown);
    void semaphore();

    HWAddress<6> getLocal_mac() const;
    void setLocal_mac(const HWAddress<6> &value);
    IPv4Address getTarget_ip() const;
    void setTarget_ip(const IPv4Address &value);

};

#endif // SPOOFER_H
