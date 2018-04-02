#include <iostream>
#include "jpcaplib.h"
#include "datamagician.h"
#include "printdata.h"

using namespace std;



void usage(){cout<<"rPrinter <Printer ServerIP> <port>"<<endl;}

void checkArgc(int argc)
{
    if(argc != 3)
    {
        usage();
        exit(1);
    }
}

int main(int argc, char* argv[])
{
    checkArgc(argc);

    char errbuf[PCAP_ERRBUF_SIZE];
    DataMagician dataMagician;

    //set Infomation to init sockAddr
    dataMagician.setServer_ip(argv[1]);
    dataMagician.setPort(argv[2]);

    dataMagician.initSockAddr();

    dataMagician.connectToServ();


    pcap_t* pcd = pcap_open_offline("test.pcap",errbuf);
    if(pcd == NULL)
    {
        cout<<"pcd open error!"<<endl;
        cout<<errbuf<<endl;
    }

    uint8_t* recv_data=nullptr;     //This is not same as uint8 **

    int data_len;


    while(recvPacket(pcd,&recv_data,data_len))
    {
        if(parseEther(&recv_data,data_len,ETHERTYPE_IP))
            if(parseIP(&recv_data,data_len,IPPROTO_TCP))
                if(parseTCPData(&recv_data,data_len))
                    dataMagician.sendToServ(recv_data,data_len);
    }

    return 0;
}
