/* Windows Types Definitions */
/* Programmed: Hyperlink Software®, 2008-2009 */
/* Copyright: ©2008-2009, Hyperlink Software® */

/* Contacts: */
/* E-Mail: hyperlink@inbox.ru */
/* UIN: 282757076 */

#ifndef HS_WIN32_TYPE_DEFINITIONS
#define HS_WIN32_TYPE_DEFINITIONS

#include <windows.h>

/* This definitions are the same as in WinDef.h */
//#define FALSE 0
//#define TRUE  1

//typedef int            BOOL;  // {FALSE,TRUE}

typedef unsigned char  BIT;   // {0,1}

//typedef unsigned char  BYTE;  // 1 Byte  [0,255] / [0x0,0xFF]
//typedef unsigned short WORD;  // 2 Bytes [0,65 535] / [0x0,0xFFFF]
//typedef unsigned long  DWORD; // 4 Bytes [0,4 294 967 295] / [0x0,0xFFFFFFFF]

//typedef float          FLOAT;
//typedef double         DOUBLE;

typedef BIT            *LPBIT;
//typedef UINT32         *LPUINT32;
typedef DOUBLE         *LPDOUBLE;

typedef DWORD32        *LPDWORD32;
typedef DWORD64        *LPDWORD64;

#endif