/* Win32 Definitions */
/* Programmed: Hyperlink Software®, 2008-2009 */
/* Copyright: ©2008-2009, Hyperlink Software® */

/* Contacts: */
/* E-Mail: hyperlink@inbox.ru */
/* UIN: 282757076 */

#pragma once

#define ISOLATION_AWARE_ENABLED 1
#define MANIFEST_RESOURCE_ID    2


//#define _WIN32_WINNT_WINXP                  0x0501
//#define _WIN32_WINNT_WS03                   0x0502
//#define _WIN32_WINNT_LONGHORN               0x0600

//#define _WIN32_WINNT_WINBLUE                0x0602 // Windows 8.1
//#define _WIN32_WINNT_WIN8                   0x0602 // Windows 8
//#define _WIN32_WINNT_WIN7                   0x0601 // Windows 7
//#define _WIN32_WINNT_WS08                   0x0600 // Windows Server 2008
//#define _WIN32_WINNT_VISTA                  0x0600 // Windows Vista
//#define _WIN32_WINNT_WS03                   0x0502 // Windows Server 2003 with SP1, Windows XP with SP2	
//#define _WIN32_WINNT_WINXP                  0x0501 // Windows Server 2003, Windows XP	
//#define _WIN32_WINNT_WIN2K                  0x0500
//#define _WIN32_WINNT_NT4                    0x0400

//#include <sdkddkver.h>

#if WINVER <= 0x0500
#undef WINVER
#define WINVER _WIN32_WINNT_WINXP
#endif

#if _WIN32_WINNT <= 0x0500
#undef _WIN32_WINNT
#define _WIN32_WINNT _WIN32_WINNT_WINXP
#endif

#ifdef HS_WIN32_CONSOLE
#include <stdio.h>
#include <conio.h>
#include <string.h>
#endif

#include <tchar.h>

//#include <basetsd.h>
//#include <windef.h>
//#include <winnt.h>
//#include <wtypes.h>

#include <windows.h>
#include <strsafe.h>

//comctl32.lib
#include <commctrl.h>

#ifdef HS_WINSOCK
//wsock32.lib
//wsock32.dll
#include <winsock.h>
#endif

#ifdef HS_WINSOCK2
//ws2_32.lib
//ws2_32.dll
#include <winsock2.h>
#endif

#ifdef HS_WINCRYPT
//advapi32.lib
//advapi32.dll
#include <wincrypt.h>
#endif

#define NULL 0
#define INVALID_POINTER_VALUE NULL

// Структура "Приложение Win32"
//#include "hsWin32Application.h"

// Определения для диалоговых окон Windows
//#include "hsWin32Definitions.h"
#include "hsDefinitions.h"

// Определения типов данных
//#include "hsWin32Types.h"
#include "hsTypes.h"

// Определения кодов ошибок
//#include "hsWin32Errors.h"
#include "hsErrors.h"

// Windows Messages
#define HS_WM_VIRTUAL_KEYBOARD 0x10000

// Control Symbols
#define LF 0xA
#define CR 0xD

// Основания систем счисления.
//#include "hsConvert.h"

/*

- Datatype Prefixes -

b  - byte
w  - word
dw - double word

d - double
n - int
u - unsigned int

p  - pointer
lp - long pointer

c  - char
wc - wide-char
tc - template-char

sz - null terminated string

*/