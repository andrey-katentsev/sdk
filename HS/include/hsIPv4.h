/* IP (version 4) */
/* Designed and Programmed by Hyperlink Software®, 2009 */
/* Copyright by © 2009, Hyperlink Software® */

/* Contacts: */
/* E-Mail: hyperlink@inbox.ru */
/* UIN: 282757076 */

#pragma once

#ifndef HS_IPv4_LIB
#define HS_IPv4_LIB
#endif

#include <windows.h>

#pragma region IPv4
typedef struct tagIPv4Header
{
 BYTE Version:4;      // Version. (4 bits)
 BYTE HeaderLength:4; // Internet Header Length. (4 bits)
 BYTE DS;             // Differentiated Services/Type of Services.
 WORD TotalLength;    // Total Length.
 WORD ID;             // Identification.
 WORD Flags:3;        // Flags. (3 bits)
 WORD FragmentOffset:13; // Fragment Offset. (13 bits)
 BYTE TTL;            // Time To Live.
 BYTE Protocol;       // Protocol.
 WORD HeaderChecksum; // Header Checksum.
 DWORD SourceIP;      // Source IP address.
 DWORD DestinationIP; // Destination IP address.
} HS_IPv4_HEADER;

// Protocols:
//  1: Internet Control Message Protocol (ICMP)
//  2: Internet Group Management Protocol (IGMP)
//  6: Transmission Control Protocol (TCP)
// 17: User Datagram Protocol (UDP))

//#define HS_IPv4_GET_VER(VIHL) VIHL>>4
//#define HS_IPv4_GET_IHL(VIHL) VIHL&0x0F

void hsTranslateBytesOrder(HS_IPv4_HEADER &IPv4);
LPCTSTR hsTranslateIPv4(DWORD IP);
#pragma endregion

#pragma region Windows Sockets
PCHAR hsGetPeerIPv4(SOCKET SPeer); // Function retrieves the address of the peer to which a socket is connected.
#pragma endregion