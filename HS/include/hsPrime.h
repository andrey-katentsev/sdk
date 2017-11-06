/* Библиотека простых чисел (Prime Numbers Library) */
/* Реализация: Катенцев А.А., 2009 год. */
/* ©2009, Катенцев А.А. */

/* Контактная информация: */
/* E-Mail: hyperlink@inbox.ru */
/* UIN: 282757076 */

#pragma once

#include <windows.h>

// Функция вычисляет наибольший общий делитель двух чисел a и b.
// НОД(a,b), GCD(a,b) (Greatest Common Divisor)
// Используется алгоритм Евклида.
// <Контроль качества>
template <class T> T hsGCD(T a,T b)
{
 // Вспомогательная переменная.
 T t;

 // Меняем местами значения, если необходимо.
 if(b>a)
 {
  t=a;
  a=b;
  b=t;
 }

 // Алгоритм Евклида
 while(b!=0)
 {
  t=a%b;
  a=b;
  b=t;
 }

 // Возвращаем НОД(a,b)
 return a;
}

// Функция определяет являются ли два числа a и b взаимнопростыми.
// <Контроль качества>
template <class T> bool hsIsCoprime(T a,T b)
{ return hsGCD(a,b)==1?true:false; }

// Вычисляет значение функции Эйлера.
// <Контроль качества>
template <class T> T hsEulerWiki(T n)
{
 T i,p,e=1;
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

// Вычисление функции Эйлера (простая факторизация числа [перебор делителей]).
// <Контроль качества>
template <class T> T hsEuler(T n)
{
	T i,e=n;

 // Факторизация числа методом перебора делителей.
 for(i=2;i*i<=n;++i)
 {
  // Нашли делитель.
  if(n%i==0)
  {
   // Сокращаем число.
   while(n%i==0)
   { n/=i; }
   // Вычисляем значение слагаемого для функции Эйлера.
   e-=e/i;
  }
 }

 // Последнее слагаемое, если оно существует.
 if(n>1)
 { e-=e/n; }

 return e;
}

// Вычисление функции Эйлера (по-определению).
/*template <class T> T hsEuler(T n)
{
 // Значение функции Эйлера
 T e=0;

 // Вычисление значения функции Эйлера (по-определению).
 for(T i=1;i<n;i++)
 {
  if(1==hsGCD(n,i))
  { e++; }
 }

 return e;
}*/

#define hsTotient(n) hsEuler(n)

// Алгоритм быстрого возведения в степень по модулю.
// Источник: Page 244 of Bruce Schneier's "Applied Cryptography", 2e, ISBN 0-471-11709-9
// <Контроль качества>
template <class T> T hsModularExponent(T base,T power,T modulus) 
{
 T result=1;

 while(power>0)
 {
  if((power&1)==1)
  { result=(result*base)%modulus; } // Multiply in this bit's contribution while using modulus to keep result small.
  power>>=1; // Move to the next bit of the exponent, square (and mod) the base accordingly.
  base=(base*base)%modulus;
 }
 return result;
}

#pragma region Алгоритмы факторизации
// Факторизация числа методом перебора делителей.
// <Контроль качества>
template <class T> T* hsFactorization(T n,unsigned int &count)
{
 T i,*p;

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
   p=(T*)realloc(p,count*sizeof(T));
   p[count-1]=i;
  }
 }

 // Добавляем в список последний сомножитель, если он существует.
 if(n>1)
 {
  count++;
  p=(T*)realloc(p,count*sizeof(T));
  p[count-1]=n;
 }

 return p;
}

//#include "hsRNG.h"

// Метод p-Полларда.
// Параметры:
// [in] n      - число, которое необхоимо разложить на простые сомножители.
// [in] f(x,n) - функция генерации псевдослучайных чисел по модулю n.
// Возвращаемое значение:
// Простое число - делитель n, или 0 в случае неуспеха.
// Алгоритм может и не найти простой сомножитель даже для составного n. В этом случае следует взять другую f(x) и попытаться снова.
// <Контроль качества>
template <class T> T hsPollardsRho(const T &n,T (*f)(const T&,const T&))
{
 T x=2,y=2,d=1,t;

 while(1==d)
 {
  x=f(x,n);      // x=f(x);
  y=f(f(y,n),n); // y=f(f(y));

  t=x>y?x-y:y-x; // t=|x-y|;
  d=hsGCD(t,n);  // d=GCD(|x-y|,n);
 }

 if(n==d) // Неуспех.
 { return 0; }

 return d;

 /*T x,y,k,d,i=1;

 // 1) Выбираем случайным образом x(i) из множества {0,1,...,n-1};
 //seedBBS(GetTickCount());
 //x=randBBS(0,n-1);
 //seedl(LINT(GetTickCount()));
 x=hsUniform(0,n-1);
 y=x;
 k=2;

LOOP:
 // 2) Вычисляем следующий элемент последовательности.
 i=i+1;
 x=f(x)%n;

 // 3) Завершился ли цикл?
 d=hsGCD(y-x,n);

 if(1!=d && n!=d)
 { return d; } // d - делитель n, цикл завершён.

 // 4) Следующая итерация
 if(i==k)
 {
  y=x;
  k=2*k;
 }
 goto LOOP;*/
}
#pragma endregion

// Функция находит все первообразные корни для заданного n.
// Алгоритм:
// - Находим значение функции Эйлера от n (e), факторизуем его (p).
// - Перебираем все числа g=2..n
// - (!) Для каждого числа, для которого выполняется НОД(g,n)=1
// - Если g^e=1(mod n), то считаем все величины g^(e/p(i)) mod n
// - Если для текущего g все эти числа оказались отличными от 1, то g является искомым первообразным корнем.
// Параметры:
// [in]  n  - число для которого требуется найти первообразные корни.
// [out] rn - количество первообразных корней.
// Возвращаемое значение:
// Указатель на участок памяти в которой располагаются rn значений первообразных корней.
// После использовавния память следует явно освобождать функцией free().
// <Контроль качества>
template <class T> T* hsPrimitiveRootModuloN(T n,T &rn)
{
 unsigned int pn,i,j=0;
 T e,g,*p,*r;
 bool f;

 // Вычисляем значение функции Эйлера.
 e=hsEuler(n);

 // Вычисляем количество первообразных корней. (Теоретическое)
 rn=hsEuler(e);

 // Выделяем память для размещения первообразных корней.
 r=(T*)malloc(rn*sizeof(T));

 // Факторизуем значение функции Эйлера.
 p=hsFactorization(e,pn);

 // Перебираем все числа g=2..n
 for(g=2;g<n;g++)
 {
  // (!) сначала надо проверить что НОД(g,n)==1 (!) и, если g^e=1(mod n), то g - это и есть первообразный корень (внутренний цикл будет не нужен).
  // ...
  // Если g^e=1(mod n), то...
  if(hsModularExponent(g,e,n)==1) // (?) Нужно ли это действие?
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

 // Действительное число первообразных корней. (?) Зачем, если оно известно?
 rn=j;
 free(p);
 return r;
}

#pragma region Модульная арифметика
DWORD32 hsModularExponent32(DWORD32 Base,DWORD32 Power,DWORD32 Modulus);
#pragma endregion

#pragma region Простые числа
#define HS_PRIME_ACCURACY_DEFAULT 5

DWORD32 hsGetPrime32(BYTE Bits=32,BYTE Accuracy=HS_PRIME_ACCURACY_DEFAULT);

#pragma region Тест Миллера-Рабина
#define COMPOSITE FALSE
#define PRIME     TRUE

BOOL hsMillerRabinPass32(DWORD32 Number,BYTE Accuracy=HS_PRIME_ACCURACY_DEFAULT);
#pragma endregion
#pragma endregion

/*
#pragma region Простые числа
DWORD32 hsGetPrime32(BYTE Bits=32,DOUBLE dAccuracy=0.0009765625); // Генерация n-битного простого числа
BOOL hsMillerRabinPass32(UINT32 uNumber,DOUBLE dAccuracy=0.0009765625); // Тест Миллера-Рабина (проверка числа на простоту)
UINT32* hsPrimitiveRootModuloN32(UINT32 uN,UINT32 &uTotal);
#pragma endregion
*/