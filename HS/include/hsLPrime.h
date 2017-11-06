/* Библиотека больших простых чисел (Long prime numbers library) */
/* Designed and Programmed by Hyperlink Software®, 2006-2009 */

/* Contacts: */
/* E-Mail: hyperlink@inbox.ru */
/* UIN: 282757076 */

#ifndef HS_LONG_PRIME_LIBRARY
#define HS_LONG_PRIME_LIBRARY

#include <windows.h>

#define FLINTPP_ANSI
#include "flintpp.h"

#pragma region Модульная арифметика
// Модульное возведение в степень. (a^t mod n)
LINT hsModularExponentLINT(const LINT &Base,const LINT &Power,const LINT &Modulus);
LINT hsModularExponentLINT(const LINT &Base,const LINT &Power,const LINT &Modulus,const int Bits);
#pragma endregion

#pragma region Тест Миллера-Рабина
#define HS_STD_ACCURACY 0.25

//#define COMPOSITE 0
//#define PRIME     1

// Вероятностный тест Миллера-Рабина (проверка числа на простоту)
//BOOL hsMillerRabinPass32(UINT32 uNumber,DOUBLE dAccuracy=0.0009765625);
#pragma endregion

#pragma region Простые числа
#define HS_LPRIME_MILLER_RABIN_TEST 0x04
#define HS_LPRIME_MIHAILESCU_TEST   0x05

#define HS_LPRIME_BITS_MAX 0xFFFFFFFF

#define HS_LPRIME_STD_ACCURACY 0.0009765625
#define HS_LPRIME_STD_N 5

// Генерация n-битного простого числа
//LINT hsGetPrimeLINT(const int nBits,double dAccuracy=HS_LPRIME_STD_ACCURACY);
LINT hsGetPrimeLINT(const int nBits,const UINT32 nN=HS_LPRIME_STD_N);
// РГР 2009
LINT hsGetPrime(const unsigned int Size,const unsigned short Reliability,const unsigned short Test);
LINT hsGetMihailescuPrime(const unsigned int m,const unsigned int B,const double s,const double c,const float e);



BOOL IsPrimeLINT(const LINT &LN,const int nBits,const UINT32 nN=HS_LPRIME_STD_N);
LINT* hsFactorizationLINT(LINT n,UINT64 &count);

#define HS_POLLARDS_RHO_ALGORITHM 0x09
LINT* hsFactorization(const LINT &n,LINT (*f)(const LINT&),UINT64 &fcount,BYTE algorithm=HS_POLLARDS_RHO_ALGORITHM);

LINT* hsPrimitiveRootModuloNLINT(LINT n,UINT64 &rn);
LINT hsGetPrimitiveRootModuloNLINT(LINT n);
//BOOL hsMillerRabinPrimalityTest(UINT64 uNumber,DOUBLE dAccuracy=0.0009765625); // Тест Миллера-Рабина (проверка числа на простоту)
//#define hsMillerRabinTest hsMillerRabinPrimalityTest
#pragma endregion

#endif