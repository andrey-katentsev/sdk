/* Электронная Цифровая Подпись (ЭЦП) */
/* Digital Signature (DS) */
/* Реализация: Катенцев А.А., 2009 год. */
/* ©2009, Катенцев А.А. */

/* Контактная информация: */
/* E-Mail: hyperlink@inbox.ru */
/* UIN: 282757076 */

#pragma once

#include <windows.h>

BOOL hsRSA32Verify(DWORD32 M,DWORD32 DS,DWORD32 e,DWORD32 n);

BOOL hsElGamal32Generate(PDWORD32 x,PDWORD32 k,PDWORD32 h,PDWORD32 g,PDWORD32 p,BYTE Bits=32);
DWORD32 hsElGamal32GetH(DWORD32 g,DWORD32 x,DWORD32 p);
DWORD64 hsElGamal32Sign(DWORD32 M,DWORD32 x,DWORD32 k,DWORD32 g,DWORD32 p,PDWORD32 DSA,PDWORD32 DSB);
BOOL hsElGamal32Verify(DWORD32 M,DWORD32 DSA,DWORD32 DSB,DWORD32 h,DWORD32 g,DWORD32 p);