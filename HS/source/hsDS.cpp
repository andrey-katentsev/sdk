#include "hsDS.h"
#include "hsPrime.h"
#include "hsVector.h"
#include "hsBitwise.h"
#include "hsRNG.h"

#include <math.h>

#pragma message("Digital Signature (version 1.0)")

// СДЕЛАТЬ:
// - возвращать код ошибки (0), если параметры заданы неверно (ElGamal).

#pragma region Digital Signature (RSA)
// Функция проверки 32-х битной ЭЦП.
// Параметры:
// [in] M  - сообщение (значение хэш-функции от сообщения).
// [in] DS - цифровая подпись.
// [in] e  - ключ шифрования RSA.
// [in] n  - основание (модуль) RSA.
// Возвращаемое значение:
// TRUE, если подпись верна. FALSE в противном случае.
// <Контроль качества>
BOOL hsRSA32Verify(DWORD32 M,DWORD32 DS,DWORD32 e,DWORD32 n)
{ return M==hsModularExponent32(DS,e,n)?TRUE:FALSE; }
#pragma endregion

// ElGamal Encryption System (EGES)/ (Taher Elgamal)
#pragma region Digital Signature (ElGamal)
// Получение параметров для ЭЦП Эль-Гамаля.
BOOL hsElGamal32Generate(PDWORD32 x,PDWORD32 k,PDWORD32 h,PDWORD32 g,PDWORD32 p,BYTE Bits)
{
 *p=hsGetPrime32(Bits);
 *g=hsUniform(1,*p-1);  // (?) Должно быть первообразным корнем.
 *x=hsUniform(1,*p-1);
 *h=hsElGamal32GetH(*g,*x,*p);
 do
 { *k=hsUniform(1,*p-1); }
 while(1!=hsGCD(*k,*p-1));
 return TRUE;
}
// Решение сравнения 1-й степени вида ax=1(mod b).
// Параметры:
// [in] a - произвольное число*.
// [in] b - произвольное число*.
// *) НОД(a,b)=1, а<b.
// Возвращаемое значение:
// x - решение сравнения первой степени.
// 0 - если решения не существует.
// <Контроль качества>
DWORD32 hsElGamal32GetXK(DWORD32 a,DWORD32 b)
{
 // Векторы для решения.
 INT64 q,x[3],y[3],t[3];

 // Инициализация.
 x[0]=1;
 x[1]=0;
 x[2]=b;

 y[0]=0;
 y[1]=1;
 y[2]=a;

START:
 // Расширенный алгоритм Евклида.
 if(0==y[2])
 { return 0; }

 if(1==y[2]) // НОД(a,b)=1
 {
  while(y[1]<0)
  { y[1]+=b; }
  return (DWORD32)y[1];
 }

 q=x[2]/y[2];

 // t=x-qy
 hsMult3v(y,q,t);
 hsMinus3v(x,t,t);

 x[0]=y[0];
 x[1]=y[1];
 x[2]=y[2];

 y[0]=t[0];
 y[1]=t[1];
 y[2]=t[2];
 goto START;
}

// Функция вычисляет значение открытого ключа для проверки ЭЦП по алгоритму Эль-Гамаля.
// Параметры:
// [in] g - произвольное число, g<p [открытый ключ].
// [in] x - произвольное число, x<p [секретный ключ].
// [in] p - простое число           [открытый ключ].
// Возвращаемое значение:
// Значение открытого ключа h.
// <Контроль качества>
DWORD32 hsElGamal32GetH(DWORD32 g,DWORD32 x,DWORD32 p)
{ return hsModularExponent32(g,x,p); }

// Функция вычисляет значение первой компоненты ЭЦП по алгоритму Эль-Гамаля.
// Параметры:
// [in] g - произвольное число, g<p               [открытый ключ].
// [in] k - произвольное число, НОД(k,p-1)=1, k<p [секретный ключ].
// [in] p - простое число                         [открытый ключ].
// Возвращаемое значение:
// Первая компонента ЭЦП.
// <Контроль качества>
DWORD32 hsElGamal32GetA(DWORD32 g,DWORD32 k,DWORD32 p)
{ return hsModularExponent32(g,k,p); }

// Функция вычисляет значение второй компоненты ЭЦП по алгоритму Эль-Гамаля.
// Параметры:
// [in] M   - сообщение (значение хэш-функции от сообщения).
// [in] x   - произвольное число, x<p               [секретный ключ].
// [in] k   - произвольное число, НОД(k,p-1)=1, k<p [секретный ключ].
// [in] DSA - первая компонента ЭЦП.
// [in] p   - простое число                         [открытый ключ].
// Возвращаемое значение:
// Вторая компонента ЭЦП.
// <Контроль качества>
DWORD32 hsElGamal32GetB(DWORD32 M,DWORD32 x,DWORD32 k,DWORD32 DSA,DWORD32 p)
{
 INT64 DSB=((INT64)hsElGamal32GetXK(k,p-1)*((INT64)M-(INT64)x*(INT64)DSA))%(INT64)(p-1);
 while(DSB<0)
 { DSB+=(p-1); }
 return (DWORD32)DSB;
}

// Функция для вычисления 32-х битной ЭЦП.
// Параметры:
// [in] M    - сообщение (значение хэш-функции от сообщения).
// [in] x    - произвольное число, x<p               [секретный ключ].
// [in] k    - произвольное число, НОД(k,p-1)=1, k<p [секретный ключ].
// [in] g    - произвольное число, g<p               [открытый ключ].
// [in] p    - простое число [открытый ключ].
// [out] DSA - первая компонента ЭЦП (старшее 32-х битное слово).
// [out] DSB - вторая компонента ЭЦП (младшее 32-х битное слово).
// Возвращаемое значение:
// 64-х битное значение ЭЦП <DSA,DSB>.
// Если значение младшего 32-х битного слова DSB равно нулю, ошибка HS_ERROR_INVALID_PARAMETERS.
// <Контроль качества>
DWORD64 hsElGamal32Sign(DWORD32 M,DWORD32 x,DWORD32 k,DWORD32 g,DWORD32 p,PDWORD32 DSA,PDWORD32 DSB)
{
 *DSA=hsElGamal32GetA(g,k,p);
 *DSB=hsElGamal32GetB(M,x,k,*DSA,p);
 return HS_MAKEDWORD64(*DSA,*DSB);
}

// Функция проверки 32-х битной ЭЦП.
// Параметры:
// [in] M   - сообщение (значение хэш-функции от сообщения).
// [in] DSA - первая компонента ЭЦП (старшее 32-х битное слово).
// [in] DSB - вторая компонента ЭЦП (младшее 32-х битное слово).
// [in] h   - произвольное число      [открытый ключ].
// [in] g   - произвольное число, g<p [открытый ключ].
// [in] p   - простое число           [открытый ключ].
// Возвращаемое значение:
// TRUE, если подпись верна. FALSE в противном случае.
// <Контроль качества>
BOOL hsElGamal32Verify(DWORD32 M,DWORD32 DSA,DWORD32 DSB,DWORD32 h,DWORD32 g,DWORD32 p)
{
 DWORD32 A=hsModularExponent32(h,DSA,p);
 DWORD32 B=hsModularExponent32(DSA,DSB,p);
 return ((DWORD64)A*(DWORD64)B)%p==hsModularExponent32(g,M,p)?TRUE:FALSE;
}
#pragma endregion