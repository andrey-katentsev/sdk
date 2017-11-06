/* Ethernet */
/* Designed and Programmed by Hyperlink Software®, 2009 */
/* Copyright by © 2009, Hyperlink Software® */

/* Contacts: */
/* E-Mail: hyperlink@inbox.ru */
/* UIN: 282757076 */

#pragma once

#ifndef HS_ARP_PROTOCOL
#define HS_ARP_PROTOCOL
#endif

#include <windows.h>

// Òèïû êàäðà Ethernet.
#define HS_IPv4_ARP 0x0806 // Address Resolution Protocol (ARP).

typedef struct tagIPv4ARPHeader
{
 WORD HTYPE; // Hardware type. This field specifies the Link Layer protocol type. Example: Ethernet is 1.
 WORD PTYPE; // Protocol type. This field specifies the upper layer protocol for which the ARP request is intended. For example, Internet Protocol (IPv4) is encoded as 0x0800.
 BYTE HLEN;  // Hardware length. Length (in octets) of a hardware address. Ethernet addresses size is 6.
 BYTE PLEN;  // Protocol length. Length (in octets) of a logical address of the specified protocol (cf. PTYPE). IPv4 address size is 4.
 WORD OPER;  // Operation. Specifies the operation that the sender is performing: 1 for request, 2 for reply.
} HS_IPv4_ARP_HEADER;

typedef struct tagIPv4ARPData
{
 BYTE SHA[6]; // Sender hardware address. Hardware (MAC) address of the sender.
 BYTE SPA[4]; // Sender protocol address. Upper layer protocol address of the sender.
 BYTE THA[6]; // Target hardware address. Hardware address of the intended receiver. This field is ignored in requests.
 BYTE TPA[4]; // Target protocol address. Upper layer protocol address of the intended receiver.
} HS_IPv4_ARP_DATA;

typedef struct tahIPv4ARPPacket
{
 HS_IPv4_ARP_HEADER HEADER;
 HS_IPv4_ARP_DATA DATA;
} HS_IPv4_ARP_PACKET;

void hsTranslateBytesOrder(HS_IPv4_ARP_HEADER &ARPHeader);