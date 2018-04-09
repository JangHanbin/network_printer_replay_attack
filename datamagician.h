#ifndef DATAMAGICIAN_H
#define DATAMAGICIAN_H

#include <netinet/in.h>
#include <tins/tins.h>
#include <map>
#include <vector>

using namespace Tins;

class DataMagician
{
    std::map<IPv4Address, std::vector<EthernetII>> victims;

    PacketSender sender;
    NetworkInterface iface;

    int descriptor;                 //socket File Descriptor
    struct sockaddr_in ser_addr;
    uint8_t buf[1440];              //sub ehter_header & ip header & tcp header size
    char* server_ip=nullptr;
    char* port=nullptr;
    HWAddress<6> local_mac;
    std::vector<EthernetII> vec;


public:
    DataMagician();
    ~DataMagician();
    bool dataParser(PDU &pdu);
    void parserRun();
    void sockInit();
    void initSockAddr();
    void connectToServ();
    void sendToServ(uint8_t* data, int data_len);
    char *getServer_ip() const;
    void setServer_ip(char *value);
    char *getPort() const;
    void setPort(char *value);
};

#endif // DATAMAGICIAN_H
