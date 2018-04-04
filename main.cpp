#include <iostream>
#include <tins/tins.h>
#include <glog/logging.h>
#include <thread>
#include "jpcaplib.h"
#include "datamagician.h"
#include "printdata.h"
#include "spoofer.h"
#include "hostdetector.h"

using namespace std;
using namespace Tins;


void usage(){cout<<"rPrinter <interface> <Printer ServerIP> <port>"<<endl;}

void checkArgc(int argc)
{
    if(argc != 4)
    {
        usage();
        exit(1);
    }
}

int main(int argc, char* argv[])
{
    checkArgc(argc);
    google::InitGoogleLogging(argv[0]); //enable glog
    FLAGS_logtostderr =1;               //log print to st

    char errbuf[PCAP_ERRBUF_SIZE];

    /*********** Data reply ************/
    DataMagician dataMagician;

    //set Infomation to init sockAddr
    dataMagician.setServer_ip(argv[2]);
    dataMagician.setPort(argv[3]);

    //Connect to Server
    dataMagician.initSockAddr();
    dataMagician.connectToServ();


    //    pcap_t* pcd = pcap_open_offline("test3.pcap",errbuf);
    //    if(pcd == NULL)
    //    {
    //        cout<<"pcd open error!"<<endl;
    //        cout<<errbuf<<endl;
    //    }

    //    uint8_t* recv_data=nullptr;     //This is not same as uint8 **

    //    int data_len;

    //    while(recvPacket(pcd,&recv_data,data_len))
    //    {
    //        if(parseEther(&recv_data,data_len,ETHERTYPE_IP))
    //            if(parseIP(&recv_data,data_len,IPPROTO_TCP))
    //                if(parseTCPData(&recv_data,data_len))
    //                    dataMagician.sendToServ(recv_data,data_len);
    //    }

    /*********** Data reply ************/

//    Spoofer spoofer;

    HostDetector hostDetector(dataMagician.getServer_ip(),argv[1]);

//       for (const auto &addr : hostDetector.getLocal_network()) {
//           if(spoofer.getMacAddr(addr)!=NULL)
//               cout<<spoofer.getMacAddr(addr)<<endl;
//    }


    return 0;
}
