#ifndef DATAMAGICIAN_H
#define DATAMAGICIAN_H

#include <netinet/in.h>


class DataMagician
{
    int descriptor;                 //socket File Descriptor

    struct sockaddr_in ser_addr;
    uint8_t buf[1440];              //sub ehter_header & ip header & tcp header size
    char* server_ip=nullptr;
    char* port=nullptr;

public:
    DataMagician();
    ~DataMagician();
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
