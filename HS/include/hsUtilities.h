/* Utilities Library */
/* Designed and Programmed by Hyperlink Software®, 2009 */
/* Copyright by © 2009, Hyperlink Software® */

/* Contacts: */
/* E-Mail: hyperlink@inbox.ru */
/* UIN: 282757076 */

#pragma once

#ifndef HS_UTILITIES_LIBRARY
#define HS_UTILITIES_LIBRARY
#endif

#include <string>
#include <windows.h>

#pragma region Data Conversion
#ifndef UNICODE
#define hsStringToDouble(String) atof(String)
#else
#define hsStringToDouble(String) _wtof(String)
#endif
#pragma endregion

#pragma region Dialog Utilities
#define HS_DOUBLE_PRECISION 15

double hsGetDialogItemDouble(HWND hWnd,int IDC); // Translates the text of a specified control in dialog box into a floating-point value.
void hsLoadMessageBoxInfoW(__in HINSTANCE hInstance, __in UINT uCaptionID, __in UINT uTextID, __out std::wstring& strCaption, __out std::wstring& strText, __in DWORD dwBufferSize);
#pragma endregion

template <class T> void hsSwap(T &V1,T &V2)
{
 T Buffer=V1;
 V1=V2;
 V2=Buffer;
}

#include "hsMemory.h"

//#include "hsWin32.h"
//#include <windows.h>
//#include <wtypes.h>
/*
DWORD32 hsMismatchCount(CONST LPBYTE lpDataSetA,CONST LPBYTE lpDataSetB,DWORD32 dwDataSize);          // Подсчёт числа несовпадений в двух наборах данных
BYTE hsSolveQuadraticEquation(CONST DOUBLE dA,CONST DOUBLE dB,CONST DOUBLE dC,DOUBLE& X1,DOUBLE& X2); // Решение квадратного уравнения

#pragma region Windows Sockets
PCHAR hsGetPeerIPv4(SOCKET SPeer); // Function retrieves the address of the peer to which a socket is connected.
#pragma endregion
*/

// Функция подсчитывает сумму элементов указанного масива данных.
template <class T> T hsSum(T *MemoryBlock,size_t ObjectsCount)
{
 T s=0;
 for(register size_t i=0;i<ObjectsCount;i++)
 { s+=MemoryBlock[i]; }
 return s;
}