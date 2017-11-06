/* Checksum Library [Алгоритмы вычисления контрольной суммы] */
/* Programmed by Hyperlink Software®, 2009 */
/* E-Mail: hyperlink@inbox.ru */
/* UIN: 282757076 */

/*
LRC - Longitudinal Redundancy Check
CRC - Cyclic Redundancy Check
*/

/*
Polynomial functions for common CRC's

Just as a reference the polynomial functions for the most common CRC calculations.
Please remember that the highest order term of the polynomal (x16 or x32) is not present in the binary number representation, but implied by the algorithm itself.

Name - Representations: Normal or Reversed (Reverse of Reciprocal) - Polynomial

CRC-16    -	0x8005 or 0xA001 (0xC002)             - (X^16 + X^15 + X^2 + 1)
CRC-CCITT	- 0x1021 or 0x8408 (0x8810)             - (X^16 + X^12 + X^5 + 1)
CRC-DNP	  - 0x3D65 or 0xA6BC (0x9EB2)             - (X^16 + X^13 + X^12 + X^11 + X^10 + X^8 + X^6 + X^5 +X^2 + 1)
CRC-32    -	0x04C11DB7 or 0xEDB88320 (0x82608EDB) - (X^32 + X^26 + X^23 + X^22 + X^16 + X^12 + X^11 + X^10 + X^8 + X^7 + X^5 + X^4 + X^2 + 1)
*/

#ifndef HS_CHECKSUM_LIBRARY
#define HS_CHECKSUM_LIBRARY

#define HS_CHECKSUM_VERSION 1.0

#include "hsWin32.h"

BYTE hsParityByte(CONST LPBYTE lpData,DWORD dwDataSize);                // Простая контрольная сумма
BYTE hsLRC(CONST LPBYTE lpData,DWORD dwDataSize);                       // Контрольная сумма LRC
WORD hsCRC16(CONST LPBYTE lpData,DWORD dwDataSize,WORD wPolynomial);    // Контрольная сумма CRC16
DWORD hsCRC32(CONST LPBYTE lpData,DWORD dwDataSize,DWORD dwPolynomial); // Контрольная сумма CRC32

#endif