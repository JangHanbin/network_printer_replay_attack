#include "spoofer.h"
#include <iostream>
IPv4Address Spoofer::getSender() const
{
    return victim;
}

void Spoofer::setVictim(const char *value)
{
    victim = value;
}

IPv4Address Spoofer::getTarget() const
{
    return target;
}

void Spoofer::setTarget(const char *value)
{
    target = value;
}

EthernetII::address_type Spoofer::getSender_mac() const
{
    return sender_mac;
}

void Spoofer::setSender_mac(const EthernetII::address_type &value)
{
    sender_mac = value;
}

EthernetII::address_type Spoofer::getTarget_mac() const
{
    return target_mac;
}

void Spoofer::setTarget_mac(const EthernetII::address_type &value)
{
    target_mac = value;
}

Spoofer::Spoofer()
{

}

IPv4Address Spoofer::getLocalIpAddr()
{
    NetworkInterface iface;
    iface=iface.default_interface();

    return iface.ipv4_address();

}

EthernetII::address_type Spoofer::getMacAddr(IPv4Address unknown)
{
    NetworkInterface iface;
    iface=getLocalIpAddr();

    // Why shoud I use try catch?? Am I Coding as java?
    // I want to control myself
    try{
        return Utils::resolve_hwaddr(iface,unknown,sender);
    }catch(...){

        return NULL;
    }

}

