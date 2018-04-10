#include "datamagician.h"
#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

char *DataMagician::getServer_ip() const
{
    return server_ip;
}

void DataMagician::setServer_ip(char *value)
{
    server_ip = value;
}

char *DataMagician::getPort() const
{
    return port;
}

void DataMagician::setPort(char *value)
{
    port = value;
}

DataMagician::DataMagician()
{
    //clear ser_addr datas
    memset(&ser_addr,0,sizeof(ser_addr));

    //init socket File Descriptor
    sockInit();

    //init interface
    iface=iface.default_interface();
    local_mac=iface.hw_address();

}

DataMagician::~DataMagician()
{
    close(this->descriptor);
}

bool DataMagician::dataParser(PDU &pdu)
{
    const EthernetII& etherII = pdu.rfind_pdu<EthernetII>();
    const IP& ip = pdu.rfind_pdu<IP>();
    const TCP& tcp = pdu.rfind_pdu<TCP>();


    //if host not want to network printing parsing next one
    if(tcp.dport()!=atoi(port) || etherII.dst_addr()!= local_mac) return true;


    // Let's check if there's already an entry for this address
    auto iter = victims.find(ip.src_addr());

    if (iter == victims.end())
    {
        // We haven't seen this address. Save it.
        victims.insert({ip.src_addr(), new std::vector<Packet>});

        //set iter location to current
        iter = victims.find(ip.src_addr());
    }

    //if have seen before just add PDUs
    iter->second->push_back(pdu);

    //if last packet
    if(tcp.get_flag(TCP::FIN))
    {
        std::string file_name="./"; //make current dir

        file_name = file_name+iter->first.to_string()+".pcap";
        //write pcap files
        PacketWriter writer(file_name,DataLinkType<EthernetII>());

        for(auto pdu : *(iter->second))
        {
            writer.write(pdu);
        }

        //map, vec erase
        delete iter->second;
        victims.erase(iter);
        std::cout<<"Pcap File Saved at "<<file_name<<std::endl;
    }

    return true;

}

void DataMagician::doReplay(char *pcap_name)
{
    connectToServ();
    FileSniffer file_sniffer(pcap_name);

    file_sniffer.sniff_loop(make_sniffer_handler(this,&DataMagician::readFromFile));
}

bool DataMagician::readFromFile(PDU &pdu)
{
    const RawPDU& rawPDU= pdu.rfind_pdu<RawPDU>();
    if(rawPDU.payload_size()>0)
    {
        sendToServ((uint8_t*)rawPDU.payload().data(),rawPDU.payload_size());
    }

    return true;

}

void DataMagician::parserRun()
{
    SnifferConfiguration config;
    config.set_promisc_mode(true);
    config.set_filter("tcp");

    Sniffer sniffer(iface.name());
    sniffer.sniff_loop(make_sniffer_handler(this,&DataMagician::dataParser));
}

void DataMagician::sockInit()
{
    descriptor = socket(PF_INET,SOCK_STREAM, 0);

    if(descriptor <0)
    {
        std::cout<<"Socket Init Error!"<<std::endl;
        exit(1);
    }
}

void DataMagician::initSockAddr()
{
    if(server_ip==nullptr||port==nullptr)
    {
        std::cout<<"Need to init Server IP & Port First!"<<std::endl;
        std::cout<<"Plz call after set values!"<<std::endl;
    }

    ser_addr.sin_family = PF_INET;
    ser_addr.sin_addr.s_addr = inet_addr(server_ip);
    ser_addr.sin_port = htons(atoi(port));

}

void DataMagician::connectToServ()
{
    if(connect(descriptor,(struct sockaddr*)&ser_addr,sizeof(ser_addr))<0)
    {
        std::cout<<"Server Connect Error! "<<std::endl;
        std::cout<<"Plz check Server IP or Network"<<std::endl;

    }

    std::cout<<"Server Connected!!!"<<std::endl;

}

void DataMagician::sendToServ(uint8_t *data, int data_len)
{

    if(write(descriptor,data,data_len)<0)
    {
        std::cout<<data_len<<std::endl;
        std::cout<<"Data send Error!"<<std::endl;
    }

}
