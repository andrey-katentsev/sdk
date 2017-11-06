#include "hsIPv4.h"
#include "hsMemory.h"
#include "hsBitwise.h"

#include <stdio.h>
#include <tchar.h>

#define IP_ADDRESS_FORMAT "%hu.%hu.%hu.%hu"

#pragma region IPv4
void hsTranslateBytesOrder(HS_IPv4_HEADER &IPv4)
{
 BYTE Temp;
 Temp=IPv4.Version;
 IPv4.Version=IPv4.HeaderLength;
 IPv4.HeaderLength=Temp;
 IPv4.TotalLength=SWAP_BYTES(IPv4.TotalLength);
 IPv4.DestinationIP=SWAP_BYTES_ORDER(IPv4.DestinationIP);
 IPv4.SourceIP=SWAP_BYTES_ORDER(IPv4.SourceIP);
}

LPCTSTR hsTranslateIPv4(DWORD IP)
{
 BYTE A=IP>>24;
 BYTE B=IP>>16 & 0xFF;
 BYTE C=IP>>8 & 0xFF;
 BYTE D=IP & 0xFF;

 BYTE TextLength=(BYTE)_sctprintf(TEXT(IP_ADDRESS_FORMAT),A,B,C,D);
 PTCHAR Text=hsAlloc<TCHAR>(++TextLength);

 _stprintf_s(Text,TextLength,TEXT(IP_ADDRESS_FORMAT),A,B,C,D);
 return Text;
}
#pragma endregion

#pragma region Windows Sockets
// <-- ќформить!
PCHAR hsGetPeerIPv4(SOCKET SPeer)
{
 SOCKADDR_IN SAPeer;
 INT nSize=sizeof(SAPeer);
 PCHAR pIPv4=NULL;
 getpeername(SPeer,(SOCKADDR*)&SAPeer,&nSize);
 pIPv4=inet_ntoa(SAPeer.sin_addr);
 return pIPv4;
}
#pragma endregion