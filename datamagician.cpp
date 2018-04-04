#include "datamagician.h"
#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>

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


}

DataMagician::~DataMagician()
{
    close(this->descriptor);
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
       std::cout<<"Data send Error!"<<std::endl;
    }


}
