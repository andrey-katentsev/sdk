/* Алгоритм шифрования DES (Data Encryption Standard) */
/* Реализация: Катенцев А.А., 2009 год. */
/* ©2009, Катенцев А.А. */

/* Контактная информация: */
/* E-Mail: hyperlink@inbox.ru */
/* UIN: 282757076 */

#ifndef HS_DES_HEADER
#define HS_DES_HEADER

#include <windows.h>
#include "hsCrypt.h"

#define DES_KEY_SIZE   64
#define DES_BLOCK_SIZE 64

DWORD64 hsDESEncrypt(DWORD64 Data,DWORD64 Key);
DWORD64 hsDESDecrypt(DWORD64 Data,DWORD64 Key);

DWORD64 hsDES(DWORD64 Data,DWORD64 Key,HS_CIPHER_MODE Mode);

#endif