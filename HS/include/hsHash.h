/* Hash functions library [Алгоритмы хеширования] */
/* Programmed by Hyperlink Software®, 2009 */
/* E-Mail: hyperlink@inbox.ru */
/* UIN: 282757076 */

#ifndef HS_HASH_HEADER
#define HS_HASH_HEADER

#include <windows.h>
#include "hsWin32Types.h"

void hsPBGV(const LPBYTE Data,UINT DataSize,DWORD64 IG,DWORD64 IH,LPDWORD64 LHash,LPDWORD64 RHash,DWORD64 (*F)(DWORD64 Data,DWORD64 Key));

#endif