#ifndef JPCAPLIB_H
#define JPCAPLIB_H

#include <iostream>
#include <pcap.h>
#include <netinet/in.h>
#include <netinet/ether.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>

using namespace std;

#define NONPROMISCUOUS 0
#define PROMISCUOUS 1


bool recvPacket(pcap_t *pcd, uint8_t **packetData, int &dataLen);   //recv data & save data point packetData
bool parseEther(uint8_t **data, int& dataLen, int type);            //parse Ethernet header & cmp type if type is right move pointer to type header
bool parseIP(uint8_t** data,int& dataLen, int type);                //parse IP header & cmp type if type is right move pointer to type header
bool parseTCPData(uint8_t** data,int& dataLen);                     //parse TCP header & move pointer to TCP Data
void packetSend(pcap_t* pcd, uint8_t* data, int dataLen);           //packet Send Don't need to
#endif // JPCAPLIB_H
