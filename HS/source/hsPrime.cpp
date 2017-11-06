#include "hsPrime.h"
#include "hsLFSR.h"
#include "hsConvert.h"
#include "hsMemory.h"
#include "hsRNG.h"

#pragma region Первые 500 простых чисел.
#define HS_PRIME_NUMBERS_RESERVED 500
static const unsigned short hsPrimeNumber[HS_PRIME_NUMBERS_RESERVED]=
{
 2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,
 73,79,83,89,97,101,103,107,109,113,127,131,137,139,149,151,157,163,167,173,
 179,181,191,193,197,199,211,223,227,229,233,239,241,251,257,263,269,271,277,281,
 283,293,307,311,313,317,331,337,347,349,353,359,367,373,379,383,389,397,401,409,
 419,421,431,433,439,443,449,457,461,463,467,479,487,491,499,503,509,521,523,541,
 547,557,563,569,571,577,587,593,599,601,607,613,617,619,631,641,643,647,653,659,
 661,673,677,683,691,701,709,719,727,733,739,743,751,757,761,769,773,787,797,809,
 811,821,823,827,829,839,853,857,859,863,877,881,883,887,907,911,919,929,937,941,
 947,953,967,971,977,983,991,997,1009,1013,1019,1021,1031,1033,1039,1049,1051,1061,1063,1069,
 1087,1091,1093,1097,1103,1109,1117,1123,1129,1151,1153,1163,1171,1181,1187,1193,1201,1213,1217,1223,
 1229,1231,1237,1249,1259,1277,1279,1283,1289,1291,1297,1301,1303,1307,1319,1321,1327,1361,1367,1373,
 1381,1399,1409,1423,1427,1429,1433,1439,1447,1451,1453,1459,1471,1481,1483,1487,1489,1493,1499,1511,
 1523,1531,1543,1549,1553,1559,1567,1571,1579,1583,1597,1601,1607,1609,1613,1619,1621,1627,1637,1657,
 1663,1667,1669,1693,1697,1699,1709,1721,1723,1733,1741,1747,1753,1759,1777,1783,1787,1789,1801,1811,
 1823,1831,1847,1861,1867,1871,1873,1877,1879,1889,1901,1907,1913,1931,1933,1949,1951,1973,1979,1987,
 1993,1997,1999,2003,2011,2017,2027,2029,2039,2053,2063,2069,2081,2083,2087,2089,2099,2111,2113,2129,
 2131,2137,2141,2143,2153,2161,2179,2203,2207,2213,2221,2237,2239,2243,2251,2267,2269,2273,2281,2287,
 2293,2297,2309,2311,2333,2339,2341,2347,2351,2357,2371,2377,2381,2383,2389,2393,2399,2411,2417,2423,
 2437,2441,2447,2459,2467,2473,2477,2503,2521,2531,2539,2543,2549,2551,2557,2579,2591,2593,2609,2617,
 2621,2633,2647,2657,2659,2663,2671,2677,2683,2687,2689,2693,2699,2707,2711,2713,2719,2729,2731,2741,
 2749,2753,2767,2777,2789,2791,2797,2801,2803,2819,2833,2837,2843,2851,2857,2861,2879,2887,2897,2903,
 2909,2917,2927,2939,2953,2957,2963,2969,2971,2999,3001,3011,3019,3023,3037,3041,3049,3061,3067,3079,
 3083,3089,3109,3119,3121,3137,3163,3167,3169,3181,3187,3191,3203,3209,3217,3221,3229,3251,3253,3257,
 3259,3271,3299,3301,3307,3313,3319,3323,3329,3331,3343,3347,3359,3361,3371,3373,3389,3391,3407,3413,
 3433,3449,3457,3461,3463,3467,3469,3491,3499,3511,3517,3527,3529,3533,3539,3541,3547,3557,3559,3571
};
#pragma endregion

#pragma region Модульная арифметика
// <Контроль качества>
UINT32 hsModularExponent32(UINT32 Base,UINT32 Power,UINT32 Modulus)
{
 UINT32 Result=1;

 while(Power>0)
 {
  if(Power&1)
  { Result=((UINT64)Result*(UINT64)Base)%Modulus; }
  Power>>=1;
  Base=((UINT64)Base*(UINT64)Base)%Modulus;
 }
 return Result;
 /*UINT64 uResult=1;
 for(register int i=31;i>=0;i--)
 {
  uResult=(uResult*uResult)%uModulus;
  if(uPower&(0x1<<i))
  { uResult=(uResult*uBase)%uModulus; }
 }
 return (UINT32)uResult;*/
}
#pragma endregion

#pragma region Простые числа
// Генерация простого n-битного числа.
// Параметры:
// [in] Bits     - длина числа в битах, n<=32.
// [in] Accuracy - строгость проверки числа на простоту. Вероятность, что полученое число будет не простым не превышает (0.25)^Accuracy.
// Возвращаемое значение: Простое число*.
// *) Вероятность, что полученое число будет не простым не превышает (0.25)^Accuracy.
// <Контроль качества>
DWORD32 hsGetPrime32(BYTE Bits,BYTE Accuracy)
{
 // Данные
 DWORD32 Result=0;
 DWORD32 Register=0;
 DWORD32 Generator=CRC32_IEEE_NORMAL;

 BYTE Index=32-Bits;
 PBYTE BinaryData=NULL;

 LFSR32 LFSR;

 HCRYPTPROV hCSP; // Cryptographic Service Provider.

 // Тело функции.
 if(Bits>32)
 { return 0; }

 if(FALSE==CryptAcquireContext(&hCSP,NULL,MS_DEF_PROV,PROV_RSA_FULL,0))
 { return 0; }

 BinaryData=hsAlloc<BYTE>(Bits);

START:
 // Инициализация LFSR.
 if(FALSE==CryptGenRandom(hCSP,sizeof(Register),(BYTE*)&Register))
 { Result=0; goto END; }

 LFSR.Set(Register,Generator,32);

 // 1) Генерация случайного n-битного числа.
 for(register BYTE i=0;i<Bits;i++)
 { BinaryData[i]=LFSR.NextBit(); }

 // 2) Старший и младший бит устанавливается в 1.
 //BinaryData[Index]=1;
 //BinaryData[32-1]=1;
 BinaryData[0]=1;
 BinaryData[Bits-1]=1;

 Result=hsBinTo32(BinaryData,Bits);

#if USHRT_MAX < HS_PRIME_NUMBERS_RESERVED
#error Datatype range exceeded.
#endif

 // 3) Тест №1 (Проверка на делимость [первые 500 простых чисел]) <-- Может быть много?
 for(register USHORT i=0;i<HS_PRIME_NUMBERS_RESERVED;i++)
 {
  if(0==Result%hsPrimeNumber[i])
  {
   if(hsPrimeNumber[i]==Result)
   { goto TEST; }
   LFSR.Remove();
   goto START;
  }
 }

TEST:
 // 4) Тест №2 (Тест Рабина-Миллера)
 if(COMPOSITE==hsMillerRabinPass32(Result,Accuracy))
 { goto START; }

END:
 CryptReleaseContext(hCSP,0);
 hsFree(BinaryData);
 return Result;
}

#pragma region Тест Миллера-Рабина
// Вероятностный тест Миллера-Рабина (проверка числа на простоту)
// Параметры:
// [in] N        - произвольное [нечётное] число, N>2.
// [in] Accuracy - строгость проверки числа на простоту. Вероятность, что полученое число будет не простым не превышает (0.25)^Accuracy.
// Возращаемое значение:
// - PRIME(TRUE), если число проходит тест.
// - COMPOSITE(FALSE) в противном случае.
// <Контроль качества>
BOOL hsMillerRabinPass32(DWORD32 N,BYTE Accuracy)
{
 // Данные
 DWORD32 A,Z,S=0,T=N-1;

 // Если число чётное, то оно составное.
 if(N%2==0)
 { return COMPOSITE; }

 // 1) Представляем m-1 в виде (2^s)*t, где t - нечётно.
 while(T%2==0)
 {
  T/=2;
  S++;
 }

 // Основной цикл алгоритма (Поиск N-свидетелей простоты)
LOOP:
 if(Accuracy)
 {
  Accuracy--;

  // Выбираем случайное число A (1 < A < uM)
  A=hsUniform((DWORD32)1,N);

  // a^t mod m
  Z=hsModularExponent32(A,T,N);

  if(Z==1)      // A является свидетелем простоты.
  { goto LOOP; } // return PRIME

  // Проверяем, является ли A свидетелем простоты.
  for(register DWORD32 k=0;k<S-1;k++)
  {
   if(Z==N-1)   // A является свидетелем простоты.
   { goto LOOP; } // return PRIME

   // a^((2^k)*t) mod m (где 0<=k<s)
   Z=hsModularExponent32(Z,2,N);
  }

  if(Z==N-1)   // A является свидетелем простоты.
  { goto LOOP; } // return PRIME

  // А не является свидетелем простоты, значит число составное.
  return COMPOSITE;
 }

 // Найдено N-свидетелей простоты. Число может быть простым с заданной вероятностью.
 return PRIME;
}
#pragma endregion
#pragma endregion

/*
// <Контроль качества>
UINT32* hsPrimitiveRootModuloN32(UINT32 n,UINT32 &rn)
{
 UINT32 pn,i,j=0;
 UINT32 e,g,*p,*r;
 BOOL f;

 // Вычисляем значение функции Эйлера.
 e=hsEuler(n);

 // Вычисляем количество первообразных корней. (Теоретическое)
 rn=hsEuler(e);

 // Выделяем память для размещения первообразных корней.
 r=(UINT32*)malloc(rn*sizeof(UINT32));

 // Факторизуем значение функции Эйлера.
 p=hsFactorization(e,pn);

 for(g=2;g<n;g++)
 {
  if(hsModularExponent32(g,e,n)==1)
  {
   f=true;
   for(i=0;i<pn && f;i++)
   {
    if(hsModularExponent32(g,e/p[i],n)==1)
    { f=false; }
   }
   if(f)
   { r[j++]=g; }
  }
 }

 // Действительное число первообразных корней.
 rn=j;
 free(p);
 return r;
}
*/

/*
#pragma region Тест Миллера-Рабина
// Вероятностный тест Миллера-Рабина (проверка числа на простоту)
// Параметры:
// [in] uM - [Нечётное] число (>2)
// [in] dAccuracy - Вероятность принять составное число за простое (<=1)
// Возращаемое значение:
// - PRIME(TRUE), если число проходит тест.
// - COMPOSITE(FALSE) в противном случае.
// <Контроль качества>
BOOL hsMillerRabinPass32(UINT32 uM,DOUBLE dAccuracy)
{
 // Данные
 UINT32 uA,uZ,uS=0,uT=uM-1,N=1;

 // Если число чётное, то оно составное.
 if(uM%2==0)
 { return COMPOSITE; }

 // Вычисляем количество итераций алгоритма исходя из заданной точности.
 while(pow(HS_STD_ACCURACY,(DOUBLE)N)>dAccuracy){ N++; }

 // 1) Представляем m-1 в виде (2^s)*t, где t - нечётно.
 while(uT%2==0)
 {
  uT/=2;
  uS++;
 }

 // Основной цикл алгоритма (Поиск N-свидетелей простоты)
LOOP:
 if(N)
 {
  N--;

  // Выбираем случайное число A (1 < A < uM)
  uA=hsUniform((UINT32)1,(UINT32)uM);

  // a^t mod m
  uZ=hsModularExponent32(uA,uT,uM);

  if(uZ==1)      // A является свидетелем простоты.
  { goto LOOP; } // return PRIME

  // Проверяем, является ли A свидетелем простоты.
  for(register UINT32 k=0;k<uS-1;k++)
  {
   if(uZ==uM-1)   // A является свидетелем простоты.
   { goto LOOP; } // return PRIME

   // a^((2^k)*t) mod m (где 0<=k<s)
   uZ=hsModularExponent32(uZ,2,uM);
  }

  if(uZ==uM-1)   // A является свидетелем простоты.
  { goto LOOP; } // return PRIME

  // А не является свидетелем простоты, значит число составное.
  return COMPOSITE;
 }

 // Найдено N-свидетелей простоты. Число может быть простым с заданной вероятностью.
 return PRIME;
}
#pragma endregion

UINT32 hsGetPrime32(BYTE nBits,DOUBLE dAccuracy)
{
 // Данные
 UINT32 uResult=0;
 DWORD dwRegister=0;
 DWORD dwGenerator=CRC32_IEEE_NORMAL;

 BYTE BinaryData[HS_PRIME_BITS_MAX];
 BYTE nIndex=HS_PRIME_BITS_MAX-nBits;

 LFSR32 LFSR;

 HCRYPTPROV hCSP; // Cryptographic Service Provider

 // Тело функции
 if(nBits>32)
 { return HS_ERROR_INVALID_PARAMETER; }

START:
 ZeroMemory(&BinaryData,sizeof(BinaryData));

 CryptAcquireContext(&hCSP,NULL,NULL,PROV_RSA_FULL,0);
 CryptGenRandom(hCSP,sizeof(uResult),(BYTE*)&uResult);
 CryptGenRandom(hCSP,sizeof(dwRegister),(BYTE*)&dwRegister);
 CryptReleaseContext(hCSP,0);

 LFSR.Set(dwRegister,dwGenerator,32);

 // 1) Генерация случайного n-битового числа
 for(REGISTER BYTE i=0;i<nBits;i++)
 { BinaryData[nIndex+i]=LFSR.NextBit(); }

 // 2) Старший и младший бит устанавливается в 1
 BinaryData[nIndex]=1;
 BinaryData[HS_PRIME_BITS_MAX-1]=1;

 uResult=hsBinTo32(BinaryData);

#if USHRT_MAX < HS_PRIME_NUMBERS_RESERVED
#error Datatype range exceeded.
#endif

 // 3) Тест №1 (Проверка на делимость [первые 500 простых чисел]) <-- Может быть много?
 for(REGISTER USHORT i=0;i<HS_PRIME_NUMBERS_RESERVED;i++)
 {
  if(uResult%hsPrimeNumber[i]==0)
  {
   if(uResult==hsPrimeNumber[i])
   { goto TEST; }
   LFSR.Remove();
   goto START;
  }
 }

TEST:
 // 4) Тест №2 (Тест Рабина-Миллера)
 if(COMPOSITE==hsMillerRabinPass32(uResult,dAccuracy))
 { goto START; }
 return uResult;
}
*/