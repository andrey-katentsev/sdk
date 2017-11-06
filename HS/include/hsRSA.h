/* Алгоритм шифрования DES */
/* Реализация: Катенцев А.А., 2009 год. */
/* ©2009, Катенцев А.А. */

/* Контактная информация: */
/* E-Mail: hyperlink@inbox.ru */
/* UIN: 282757076 */

#ifndef HS_RSA_HEADER
#define HS_RSA_HEADER

#include <windows.h>

#define FLINTPP_ANSI
#include "flintpp.h"

//#include "hsWin32Types.h"

BOOL hsRSAGenerate(LINT &e,LINT &d,LINT &n,UINT Bits); // Генерация ключей для алгоритма RSA.

BYTE* hsRSAEncrypt(const BYTE *Data,UINT DataSize,const LINT &e,const LINT &n); // Шифрование алгоритмом RSA.
BYTE* hsRSADecrypt(const BYTE *Data,UINT DataSize,const LINT &d,const LINT &n); // Дешифрование алгоритмом RSA.

#endif