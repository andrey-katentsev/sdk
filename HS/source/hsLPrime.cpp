#include "hsLPrime.h"
#include "hsUtilities.h"

#include <tchar.h>
#include "hsPrime.h"

#pragma region RESERVED PRIMES
#define HS_LPRIME_RESERVED 500
#define HS_LPRIME_RESERVED_MAX 3571

static const LINT hsReservedPrimes[HS_LPRIME_RESERVED]=
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

LINT hsModularExponentLINT(const LINT &Base,const LINT &Power,const LINT &Modulus)
{
 LINT R=1,P=Power,B=Base;

 while(P>0)
 {
  if(P.testbit(0))
  { R=(R*B)%Modulus; }
  P>>=1;
  B=(B*B)%Modulus;
 }
 return R;
}

LINT hsModularExponentLINT(const LINT &Base,const LINT &Power,const LINT &Modulus,const int Bits)
{
 LINT Result=1;
 for(register int i=Bits-1;i>=0;i--)
 {
  Result=(Result*Result)%Modulus;
  if(Power.testbit(i)) //if(Power & (0x1<<i))
  { Result=(Result*Base)%Modulus; }
 }
 return Result;
}

BOOL hsMillerRabinPassLINT(const LINT &LN,const int nBits,double dAccuracy)
{
 // Данные
 LINT A,Z,T=LN-1;
 UINT32 S=0,N=1;

 // Если число чётное, то оно составное.
 if(LN%2==0)
 { return COMPOSITE; }

 // Вычисляем количество итераций алгоритма исходя из заданной точности.
 while(pow(HS_STD_ACCURACY,(DOUBLE)N)>dAccuracy){ N++; }

 // 1) Представляем m-1 в виде (2^s)*t, где t - нечётно.
 while(T%2==0)
 {
  T/=2;
  S++;
 }

 // Основной цикл алгоритма (Поиск N-свидетелей простоты)
LOOP:
 if(N)
 {
  N--;

  // Выбираем случайное число A (1 < A < LN)
  A=randl(LINT(1),LN);

  // a^t mod m
  Z=hsModularExponentLINT(A,T,(LINT&)LN,nBits);

  if(Z==1)       // A является свидетелем простоты.
  { goto LOOP; } // return PRIME

  // Проверяем, является ли A свидетелем простоты.
  for(register UINT32 k=0;k<S-1;k++)
  {
   if(Z==LN-1)   // A является свидетелем простоты.
   { goto LOOP; } // return PRIME

   // a^((2^k)*t) mod m (где 0<=k<s)
   Z=hsModularExponentLINT(Z,LINT(2),(LINT&)LN,nBits);
  }

  if(Z==LN-1)   // A является свидетелем простоты.
  { goto LOOP; } // return PRIME

  // А не является свидетелем простоты, значит число составное.
  return COMPOSITE;
 }

 // Найдено N-свидетелей простоты. Число может быть простым с заданной вероятностью.
 return PRIME;
}

BOOL hsMillerRabinPassLINT(const LINT &LN,const int nBits,UINT32 N)
{
 // Данные
 LINT A,Z,T=LN-1;
 UINT32 S=0;

 // Если число чётное, то оно составное.
 if(LN%2==0)
 { return COMPOSITE; }

 // 1) Представляем m-1 в виде (2^s)*t, где t - нечётно.
 while(T%2==0)
 {
  T/=2;
  S++;
 }

 // Основной цикл алгоритма (Поиск N-свидетелей простоты)
LOOP:
 if(N)
 {
  N--;

  // Выбираем случайное число A (1 < A < LN)
  A=randl(LINT(1),LN);

  // a^t mod m
  Z=hsModularExponentLINT(A,T,(LINT&)LN,nBits);

  if(Z==1)       // A является свидетелем простоты.
  { goto LOOP; } // return PRIME

  // Проверяем, является ли A свидетелем простоты.
  for(register UINT32 k=0;k<S-1;k++)
  {
   if(Z==LN-1)   // A является свидетелем простоты.
   { goto LOOP; } // return PRIME

   // a^((2^k)*t) mod m (где 0<=k<s)
   Z=hsModularExponentLINT(Z,LINT(2),(LINT&)LN,nBits);
  }

  if(Z==LN-1)   // A является свидетелем простоты.
  { goto LOOP; } // return PRIME

  // А не является свидетелем простоты, значит число составное.
  return COMPOSITE;
 }

 // Найдено N-свидетелей простоты. Число может быть простым с заданной вероятностью.
 return PRIME;
}

BOOL IsPrimeLINT(const LINT &LN,const int nBits,const UINT32 nN)
{
 // 3) Проверяем делимость на первые 500 простых чисел.
 for(register int i=0;i<HS_LPRIME_RESERVED;i++)
 {
  if(LN%hsReservedPrimes[i]==0)
  {
   if(LN==hsReservedPrimes[i])
   { return PRIME; }
   return COMPOSITE;
  }
 }

 // 4) Тест Миллера-Рабина
 return hsMillerRabinPassLINT(LN,nBits,nN);
}

LINT hsGetPrimeLINT(const int nBits,double dAccuracy)
{
 LINT LP;

START:
 // 1) Генерация случайного n-битового числа
 LP=randBBS(nBits);

 // 2) Устанавливаеи младший бит
 LP.setbit(0);

 // 3) Проверяем делимость на первые 500 простых чисел.
 for(register int i=0;i<HS_LPRIME_RESERVED;i++)
 {
  if(LP%hsReservedPrimes[i]==0)
  {
   if(LP==hsReservedPrimes[i])
   { goto TEST; }
   goto START;
  }
 }

TEST:
 // 4) Тест Миллера-Рабина
 if(COMPOSITE==hsMillerRabinPassLINT(LP,nBits,dAccuracy))
 { goto START; }
 return LP;
}

LINT hsGetPrimeLINT(const int nBits,const UINT32 nN)
{
 LINT LP;

START:
 // 1) Генерация случайного n-битового числа
 LP=randBBS(nBits);

 // 2) Устанавливаеи младший бит
 LP.setbit(0);

 // 3) Проверка, является-ли число простым.
 if(COMPOSITE==IsPrimeLINT(LP,nBits,nN))
 { goto START; }
 return LP;
}

LINT hsEulerLINT(LINT &n)
{
 LINT i,p,e=1;
 for(i=2;i*i<=n;++i)
 {
  p=1;
  while(n%i==0)
  {
   p*=i;
   n/=i;
  }

  if((p/=i)>=1)
  { e*=p*(i-1); }
 }

 return (--n>0)?n*e:e;
}

// Факторизация числа методом перебора делителей.
// <Контроль качества>
LINT* hsFactorizationLINT(LINT n,UINT64 &count)
{
 LINT i,*p;

 count=0;
 p=NULL;

 // Перебор всех целых(как вариант: простых) чисел от 2 до квадратного корня из факторизуемого числа.
 for(i=2;i*i<=n;++i)
 {
  // Нашли делитель.
  if(n%i==0)
  {
   // Сокращаем число.
   while(n%i==0)
   { n/=i; }

   // Формируем список простых сомножителей.
   count++;
   //p=(LINT*)realloc(p,(size_t)count*sizeof(LINT)); // Найти альтернативу!
   p=hsRealloc(p,(size_t)count);
   p[count-1]=i;
  }
 }

 // Добавляем в список последний сомножитель, если он существует.
 if(n>1)
 {
  count++;
  p=hsRealloc(p,(size_t)count);
  p[count-1]=n;
 }

 return p;
}

#pragma region Алгоритмы факторизации
// Метод p-Полларда.
LINT hsPollardsRho(const LINT &n,LINT (*f)(const LINT&))
{
 LINT x,y,k,d,i=1;

 // 1) Выбираем случайным образом x(i) из множества {0,1,...,n-1};
 //seedBBS(GetTickCount());
 //x=randBBS(0,n-1);
 //seedl(LINT(GetTickCount()));
 x=randl(0,n-1); x.decstr();
 y=x;
 k=2;

LOOP:
 // 2) Вычисляем следующий элемент последовательности.
 i=i+1;
 x=f(x)%n; x.decstr();

 // 3) Завершился ли цикл?
 d=gcd(y-x,n);

 if(1!=d && n!=d)
 { return d; } // d - делитель n, цикл завершён.

 // 4) Следующая итерация
 if(i==k)
 {
  y=x;
  k=2*k;
 }
 goto LOOP;
}
#pragma endregion

// Факторизация
// Параметры:
// [in]  n         - число, которое требуется разложить на множители.
// [in]  f         - функция (требуется в некоторых алгоритмах).
// [out] fcount    - количество множителей.
// [in]  algorithm - алгоритм с помощью которого производить факторизацию.
// Возвращаемое значение:
// Указатель на участок памяти* в которой располагаются fcount значений простых сомножителей.
// *) После использовавния память следует явно освобождать функцией hsFree().
// <Контроль качества>
LINT* hsFactorization(const LINT &n,LINT (*f)(const LINT&),UINT64 &fcount,BYTE algorithm)
{
 LINT N=n,F;
 LINT *p=NULL;

 fcount=0;

 switch(algorithm)
 {
 case HS_POLLARDS_RHO_ALGORITHM:
  {
   F=hsPollardsRho(N,f);
   p=hsRealloc(p,++fcount);
   p[fcount-1]=F;
  } break;
 }

 // Возвращаем результат.
 return p;
}

// Функция находит все первообразные корни для заданного n.
// Алгоритм:
// - Находим значение функции Эйлера от n (e), факторизуем его (p).
// - Перебираем все числа g=2..n
// - Если g^e=1(mod n), то считаем все величины g^(e/p(i)) mod n
// - Если для текущего g все эти числа оказались отличными от 1, то g является искомым первообразным корнем.
// Параметры:
// [in]  n  - число для которого требуется найти первообразные корни.
// [out] rn - количество первообразных корней.
// Возвращаемое значение:
// Указатель на участок памяти в которой располагаются rn значений первообразных корней.
// После использовавния память следует явно освобождать функцией free().
// <Контроль качества>
LINT* hsPrimitiveRootModuloNLINT(LINT n,UINT64 &rn)
{
 UINT64 pn,i,j=0;
 LINT e,g,t,*p,*r;
 bool f;

 // Вычисляем значение функции Эйлера.
 e=hsEuler(n);

 // Вычисляем количество первообразных корней. (Теоретическое)
 t=hsEuler(e);

 // Приведение типов.
 _stscanf_s(t.decstr(),TEXT("%I64d"),&rn);

 // Выделяем память для размещения первообразных корней.
 r=hsAlloc<LINT>((size_t)rn);

 // Факторизуем значение функции Эйлера.
 p=hsFactorizationLINT(e,pn);

 // Перебираем все числа g=2..n
 for(g=2;g<n;g++)
 {
  // Если g^e=1(mod n), то...
  if(hsModularExponent(g,e,n)==1)
  {
   // ...считаем все величины g^(e/p(i)) mod n
   f=true;
   for(i=0;i<pn && f;i++)
   {
    // Если g^(e/p(i))=1(mod n), то g не является первообразным корнем по модулю N.
    if(hsModularExponent(g,e/p[i],n)==1)
    { f=false; }
   }
   // Если для текущего g все сравнения не выполнились, то g является первообразным корнем.
   if(f)
   { r[j++]=g; }
  }
 }

 // Действительное число первообразных корней.
 rn=j;
 hsFree(p);
 return r;
}

// Функция находит минимальный первообразный корень для заданного n.
// Параметры:
// [in]  n  - число для которого требуется найти первообразные корни.
// Возвращаемое значение:
// Минимальный первообразный корень для заданного n.
// <Контроль качества>
LINT hsGetPrimitiveRootModuloNLINT(const LINT n)
{
 UINT64 pn,i;
 LINT e,g,t,*p;
 bool f;

 // Вычисляем значение функции Эйлера.
 e=hsEuler(n);

 // Факторизуем значение функции Эйлера.
 p=hsFactorizationLINT(e,pn);

 // Перебираем все числа g=2..n
 for(g=2;g<n;g++)
 {
  // Если g^e=1(mod n), то...
  if(hsModularExponent(g,e,n)==1)
  {
   // ...считаем все величины g^(e/p(i)) mod n
   f=true;
   for(i=0;i<pn && f;i++)
   {
    // Если g^(e/p(i))=1(mod n), то g не является первообразным корнем по модулю N.
    if(hsModularExponent(g,e/p[i],n)==1)
    { f=false; }
   }
   // Если для текущего g все сравнения не выполнились, то g является первообразным корнем.
   if(f)
   { return g; }
  }
 }

 // Первообразных корней нет.
 return LINT(0);
}

/*
// 3) Проверяем делимость на первые 500 простых чисел.
 for(register int i=0;i<HS_LPRIME_NUMBERS_RESERVED;i++)
 {
  if(LP%hsLPrimeNumber[i]==0)
  {
   if(LP==hsLPrimeNumber[i])
   { goto TEST; }
   goto START;
  }
 }

TEST:
 // 4) Тест Миллера-Рабина
 if(COMPOSITE==hsMillerRabinPassLINT(LP,nBits,nN))
 { goto START; }
 return LP;
*/

// Проверка числа на простоту делением на первые HS_LPRIME_RESERVED простых чисел.
// Параметры:
// [in] n - число которое необхоимо проверить.
// Возвращаемое значение:
//  PRIME, если число прошло проверку. COMPOSITE, иначе.
// <Контроль качества>
BOOL hsReservedTest(const LINT &n)
{
 for(register unsigned int i=0;i<HS_LPRIME_RESERVED;i++)
 {
  if(0==n%hsReservedPrimes[i])
  {
   if(n==hsReservedPrimes[i])
   { return PRIME; }
   return COMPOSITE;
  }
 }
 return PRIME;
}

// Проверка числа на простоту методом пробных делений.
// Параметры:
// [in] n - число которое необхоимо проверить.
// Возвращаемое значение:
// PRIME, если число прошло проверку. COMPOSITE, иначе.
// <Контроль качества>
BOOL hsSimpleTest(const LINT &n)
{
 LINT d(2),N(n.root());
 while(++d<N)
 {
  if(0==n%d)
  { return COMPOSITE; }
 }
 return PRIME;
}

#pragma region LINT
LINT hsPowLINT(const LINT &base,const LINT &power)
{
 LINT R=base;

 for(LINT i=1;i<power;i++)
 { R*=base; }

 return R;
}
#pragma endregion

// Preda Mihailescu.
LINT hsGetMihailescuPrime(const unsigned int m,const unsigned int B,const double s,const double c,const float e)
{
 LINT P,F,t,a,n;

 //B>0;
 //s>0;
 //c>0;

START:
 // 1) Генерация случайного m-битового числа.
 P=randBBS(m);

 // 2) Устанавливаеи старший и младший бит.
 P.setbit(0);
 P.setbit(m-1);

 // Генерация доказуемо простого m-разрядного числа.
 // 1) Если m<B, то алгоритм возвращает случайное простое число с m двоичными разрядами (порожденное с помощью пробных делений).
 if(m<B)
 {
  if(PRIME==hsSimpleTest(P))
  { return P; }
  goto START;
 }

 // 2) Строим с помощью рекурсии целое число F из интервала 2^em < F < 2^cem, факторизация которого полностью известна, е можно положить 1/2 или 1/3 в зависимости от применяемого достаточного условия простоты.
 F=randBBS(LINT((long)pow(2,e*m)),LINT((long)pow(2,c*e*m)));

 // 3) Выбираем случайное число t из диапазона ( 2^(m-2) / F , 2^(m-1) / F - sm).
 t=randBBS(LINT((long)pow(2.0,(double)m-2.0)/F),LINT(((long)pow(2.0,(double)m-1.0)/F)-(long)s*m));

 // 4) Ищем простое число в арифметической прогрессии.
 a=2*F;
 n=t*a+1;
 for(LINT i=0;i<(long)s;i++)
 {
  P=n+i*a;

  // Тест простоты выполняется в два этапа.
  // Этап 1 (Пробные деления на простые числа, не превосходящие A, где A – заданная верхняя граница).
  if(COMPOSITE==hsReservedTest(P))
  { continue; }

  // Этап 2 (Проверка простоты с помощью теста Рабина—Миллера).
  if(COMPOSITE==hsMillerRabinPassLINT(P,m,(UINT32)5))
  { continue; }

  return P;
 }
 return 0;
}

// РГР 2009
// Функция вычисляет простое число заданного размера.
// Параметры:
// [in] Size  - размер простого числа в битах.
// [in] Reliability - число проверок на простоту.
// [in] Test - тест проверки на простоту.
// Возвращаемое значение:
// Простое число указанного размера*.
// *) Простое с большой долей вероятности.
// Пример: При использовании в качестве теста проверки на простоту тест Миллера-Рабина, вероятность, что полученое число будет не простым не превышает (0.25)^Reliability.
// <Контроль качества>
/*LINT hsGetPrime(const unsigned int Size,const unsigned short Reliability,const unsigned short Test)
{
 LINT LP;

START:
 // 1) Генерация случайного n-битового числа
 LP=randBBS(Size);

 // 2) Устанавливаеи старший и младший бит.
 LP.setbit(0);
 LP.setbit(Size-1);

 // 3) Проверка, является-ли число простым.
 switch(Test)
 {
 case HS_LPRIME_MILLER_RABIN_TEST:
  {
  } break;
 case HS_LPRIME_MIHAILESCU_TEST:
  {
  } break;
 }
 
 if(COMPOSITE==IsPrimeLINT(LP,nBits,nN))
 { goto START; }
 return LP;
}*/