#ifndef SPOOFER_H
#define SPOOFER_H
#include <tins/tins.h>

using namespace Tins;

class Spoofer
{
    PacketSender sender;
    EthernetII::address_type target_mac;
    EthernetII::address_type sender_mac;

    IPv4Address target;
    IPv4Address victim;

public:
    Spoofer();
    IPv4Address getLocalIpAddr();
    EthernetII::address_type getMacAddr(IPv4Address unknown);
    IPv4Address getSender() const;
    void setVictim(const char* value);
    IPv4Address getTarget() const;
    void setTarget(const char* value);
    EthernetII::address_type getSender_mac() const;
    void setSender_mac(const EthernetII::address_type &value);
    EthernetII::address_type getTarget_mac() const;
    void setTarget_mac(const EthernetII::address_type &value);
};

#endif // SPOOFER_H
