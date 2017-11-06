/* Ethernet */
/* Designed and Programmed by Hyperlink Software®, 2009 */
/* Copyright by © 2009, Hyperlink Software® */

/* Contacts: */
/* E-Mail: hyperlink@inbox.ru */
/* UIN: 282757076 */

#pragma once

#ifndef HS_ETHERNET_HEADER
#define HS_ETHERNET_HEADER
#endif

#include <windows.h>

// Типы кадров Ethernet.
#define HS_FT_ETH_DIX 0x00
#define HS_FT_ETH_V2  HS_FT_ETH_DIX

#define HS_FT_RAW_802_3    0x01
#define HS_FT_NOVELL_802_3 HS_FT_RAW_802_3

#define HS_FT_ETH_SNAP 0x02

#define HS_FT_IEEE_802_3 0x04
#define HS_FT_ETH_LLC    HS_FT_IEEE_802_3

#define HS_ETHERNET_FRAME_DATA_SIZE_MIN 0x002E //   46 bytes

#define HS_ETHERNET_FRAME_SIZE_MAX      0x05F6
#define HS_ETHERNET_FRAME_DATA_SIZE_MAX 0x05DC // 1500 bytes

#define HS_ETHERNET_MAC_ADDRESS_SIZE 6
#define HS_ETHERNET_TYPE_SIZE 2

typedef struct tagMACHeader
{
 BYTE dstMAC[HS_ETHERNET_MAC_ADDRESS_SIZE]; // Destination MAC-address.
 BYTE srcMAC[HS_ETHERNET_MAC_ADDRESS_SIZE]; // Source MAC-address.
 WORD ethType;                              // Ethernet Type/Length. (Тип протокола сетевого уровня или длина кадра (в зависимости от типа кадра)).
} HS_ETHERNET_MAC_HEADER;

// Ethernet Type:
// 0x0800 - Internet Protocol (IP).
// 0x0806 - Address Resolution Protocol (ARP).
// 0x809B - AppleTalk.
// 0x0600 - Xerox Network System (XNS).
// 0x8137 - NetWare IPX/SPX.

typedef struct tagLLCHeader
{
 BYTE DSAP;
 BYTE SSAP;
 BYTE Control;
} HS_ETHERNET_LLC_HEADER;

typedef struct tagLLC2Header
{
 BYTE DSAP;
 BYTE SSAP;
 WORD Control;
} HS_ETHERNET_LLC2_HEADER;

#define HS_ETHERNET_OUI_SIZE 3
// SubNetwork Access Protocol (SNAP)
// Organizationally Unique Identifier (OUI)
typedef struct tagSNAPHeader
{
 BYTE OUI[HS_ETHERNET_OUI_SIZE];
 WORD Type;
} HS_ETHERNET_SNAP_HEADER;

BOOL hsIsFrameCorrect(const HS_ETHERNET_MAC_HEADER &MAC);