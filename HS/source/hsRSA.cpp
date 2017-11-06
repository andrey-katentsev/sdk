//#include "hsWin32Errors.h"
//#include "hsBitwise.h"
//#include "hsCrypt.h"

#include "hsRSA.h"
#include "hsConvert.h"
#include "hsMemory.h"
#include "hsPrime.h"
#include "hsLPrime.h"

// РАЗРАБОТАТЬ:
// - Параметр функции шифрования/дешифрования длина блока шифрования/дешифрования (по-умолчанию 8 бит).

#pragma region RSA
// Функция вычисления ключей для использования в алгоритме RSA.
// Параметры:
// [in]  bits - длина ключа (в битах).
// [out] e - ключ шифрования.
// [out] d - ключ дешифрования.
// [out] n - основание (модуль).
// Пара (e,n) - открытый ключ.
// Пара (d,n) - закрытый ключ.
// Возвращаемое значение: Нет.
// <Контроль качества>
BOOL hsRSAGenerate(LINT &e,LINT &d,LINT &n,UINT Bits)
{
 int sign_u,sign_v;
 LINT p,q,m,u,v;

 // Генерируем два простых числа.
 p=hsGetPrimeLINT(Bits);
 do
 { q=hsGetPrimeLINT(Bits); }
 while(p==q);

 // Вычисляем модуль.
 n=p*q;
 // Вычисляем функцию Эйлера от модуля.
 //m=hsEuler(n);
 m=(p-1)*(q-1);
 // Выбираем e - взаимно простое с (p-1)(q-1) число. (3<e<n-1)
 do
 //{ e=randl(m/3,m); }   // Линейный конгруэнтный генератор.
 { e=randBBS(m/3,m); } // Генератор Blum Blum Shub.
 while(hsGCD(e,m)!=1);
 // Определяем d.
 // Решаем сравнение 1-й степени e*d=1(mod m), d<m (алгоритм Евклида).
 // ev+mu=НОД(e,m)=1
 xgcd(e,m,v,sign_v,u,sign_u);
 //xgcd(54,1234,u,sign_u,v,sign_v);
 //xgcd(111,322,u,sign_u,v,sign_v);
 d=v;

 // Путём многократного сложения с модулем получаем положительное число.
 if((-1)==sign_v)
 {
  if(v<m)
  { d=m-v; }
  else
  {
   d=v%m;
   d=m-d;
  }
 }
 return TRUE;
}

BYTE* hsRSAEncrypt(const BYTE *Data,UINT DataSize,const LINT &e,const LINT &n)
{
 UINT i,j,TextSize;
 CHAR *Bin,*Block,*CipherText;
 BYTE *EnData;

 LINT m,LCT;

 // Определяем размер блока данных для шифрования.
 const UINT k=ld(n);

 // ВНИМАНИЕ: При шифровании m выбирается таким образом, чтобы 1<m<n

 Block=hsAlloc<CHAR>(k+1);
 Bin=hsAlloc<CHAR>(8*DataSize);
 EnData=hsAlloc<BYTE>(k*DataSize);

 // Переводим сообщение в двоичное представление.
 for(i=0;i<DataSize;i++)
 { hsByteToBin(Data[i],&Bin[8*i]); }

 // Шифруем блоки.
 for(i=0;i<DataSize;i++)
 {
  CopyMemory(Block,&Bin[8*i],8);
  Block[8]=0;
  m=LINT(Block,BIN);
  // Шифрование.
  LCT=hsModularExponentLINT(m,e,n);
  // Формируем результат.
  CipherText=LCT.binstr();
  TextSize=strlen(CipherText);
  FillMemory(Block,k,0x30);
  for(j=0;j<TextSize;j++)
  { Block[(k-1)-j]=CipherText[(TextSize-1)-j]; }
  CopyMemory(&EnData[k*i],Block,k);
 }

 hsFree(Block);
 hsFree(Bin);
 return EnData;
}

BYTE* hsRSADecrypt(const BYTE *Data,UINT Size,const LINT &d,const LINT &n)
{
 UINT i,j,TextSize;
 CHAR *Bin,*Block,*PlainText;
 BYTE *DeData;

 LINT c,LCT;

 // Определяем размер блока данных для шифрования.
 const UINT k=ld(n);

 // Определяем число блоков.
 const UINT p=Size/k;
 //const UINT q=(8*Size)%k;

 Block=hsAlloc<CHAR>(k+1);
 Bin=hsAlloc<CHAR>(8);
 DeData=hsAlloc<BYTE>(p);

 // Дешифруем блоки.
 for(i=0;i<p;i++)
 {
  CopyMemory(Block,&Data[k*i],k);
  Block[k]=0;
  c=LINT(Block,BIN);
  // Дешифрование.
  LCT=hsModularExponentLINT(c,(LINT&)d,(LINT&)n);
  // Формируем результат.
  PlainText=LCT.binstr();
  TextSize=strlen(PlainText);
  FillMemory(Bin,8,0x30);
  for(j=0;j<TextSize && j<8;j++) // <-- Ограничение в 8 бит.
  { Bin[(8-1)-j]=PlainText[(TextSize-1)-j]; }
  DeData[i]=hsBinToByte(Bin);
 }

 hsFree(Block);
 hsFree(Bin);
 return DeData;
}
#pragma endregion