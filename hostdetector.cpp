#include "hostdetector.h"
#include <iostream>
#include <functional>

using std::bind;

IPv4Range HostDetector::getLocal_network() const
{
    return *local_network;
}

std::map<IPv4Address, HWAddress<6> > HostDetector::getAddresses() const
{
    return addresses;
}

HostDetector::HostDetector(IPv4Address ipv4)
{
    iface=iface.default_interface();

    local_ip=getLocalIpAddr();
    local_network=new IPv4Range(ipv4 / 24);

    config.set_promisc_mode(true);
    config.set_filter("arp");
    sniffer = new Sniffer(iface.name(), config);

}

HostDetector::~HostDetector()
{
    delete(local_network);
    delete(sniffer);
}

IPv4Address HostDetector::getLocalIpAddr()
{


    return iface.ipv4_address();
}

HWAddress<6> HostDetector::getLocalMacAddr()
{

    return iface.hw_address();
}

void HostDetector::run()
{
    sniffer->sniff_loop(bind(&HostDetector::scan,this,std::placeholders::_1));
}

bool HostDetector::scan(const PDU& pdu)
{
    // Retrieve the ARP layer
    const ARP& arp = pdu.rfind_pdu<ARP>();
    // Is it an ARP reply?
    if (arp.opcode() == ARP::REPLY)
    {
        // Let's check if there's already an entry for this address
        auto iter = addresses.find(arp.sender_ip_addr());

        if (iter == addresses.end())
        {
            // We haven't seen this address. Save it.
            addresses.insert({ arp.sender_ip_addr(), arp.sender_hw_addr()});
        }
        else
        {
            // We've seen this address. If it's not the same HW address, inform it
        }
    }

    //if need to end loop
    if(!condition)
        return condition;

    return true;
}

void HostDetector::hostPrinter()
{

    for(const auto elem : addresses)
    {
        std::cout<< elem.first << " " << elem.second<<std::endl;
    }
}

void HostDetector::askHost()
{

    EthernetII arp_request;
    ARP arp;

    //ask to all clinet in same network
    for (const auto &addr :getLocal_network())
    {

        arp_request=arp.make_arp_request(addr,getLocalIpAddr(),getLocalMacAddr());
        sender.send(arp_request,iface);
    }

}

void HostDetector::semaphore()
{
    condition=!condition;
}


