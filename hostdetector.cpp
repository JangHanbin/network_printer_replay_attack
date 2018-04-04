#include "hostdetector.h"
#include <iostream>
#include <functional>

using std::bind;

IPv4Range HostDetector::getLocal_network() const
{
    return *local_network;
}

HostDetector::HostDetector(IPv4Address ipv4, char* iface)
{
    local_ip=getLocalIpAddr();
    local_network=new IPv4Range(ipv4 / 24);

    config.set_promisc_mode(true);
    config.set_filter("arp");
    sniffer = new Sniffer(iface, config);

}

HostDetector::~HostDetector()
{
    delete(local_network);
    delete(sniffer);
}

IPv4Address HostDetector::getLocalIpAddr()
{
    NetworkInterface iface;
    iface=iface.default_interface();

    return iface.ipv4_address();
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
            if (arp.sender_hw_addr() != iter->second)
            {
//                cout << "[WARNING] " << arp.sender_ip_addr() << " is at "
//                     << iter->second << " but also at " << arp.sender_hw_addr()
//                     << endl;
            }
        }
    }

    return true;
}


