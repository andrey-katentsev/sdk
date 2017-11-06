/* Linear Feedback Shift Register */
/* Designed and Programmed by Hyperlink Software®, 2009 */

#include "hsLFSR.h"
#include "hsBitwise.h"
#include "hsConvert.h"

/*
#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
*/

// Генерация очередного бита.
BYTE tagLFSR32::NextBit(void)
{
 BYTE bHiBit=0; // Значение старшего бита.

 // Вычисляем значение старшего бита.
 for(register unsigned int cx=0;cx<nSize;cx++)
 {
  if(bGenerator[cx]==1)
  { bHiBit=bHiBit XOR (bRegister[cx]); }
 }
 
 bRandomBit=bRegister[nSize-1]; // Устанавливаем значение бита на выходе генератора.
 
 // Сдвигаем регистр.
 for(register unsigned int cx=nSize-1;cx>0;cx--)
 { bRegister[cx]=bRegister[cx-1]; }

 bRegister[0]=bHiBit; // Устанавливаем знаение старшего бита.

 return bRandomBit; // Возвращаем значение младшего бита.
}

BYTE tagLFSR32::CurrentBit(void)
{ return bRandomBit; } // Возвращаем значение младшего бита.

// Инициализация генератора.
int tagLFSR32::Set(DWORD dwRegister,DWORD dwGenerator,BYTE nSize)
{
 DWORD nMemSize=nSize*sizeof(BYTE); // Определяем необходимый размер памяти.

 this->dwRegister=dwRegister;
 this->dwGenerator=dwGenerator;
 this->nSize=nSize;

 // Выделяем память.
 bGenerator=(LPBYTE)realloc((LPBYTE)bGenerator,nMemSize);
 bRegister=(LPBYTE)realloc((LPBYTE)bRegister,nMemSize);

 // Инициализируем память.
 memset(bGenerator,0,nMemSize);
 memset(bRegister,0,nMemSize);

 // Преобразуем 32-х разрядные значения регистра и генератора в их двоичное представление.
 hs32ToBin(dwGenerator,bGenerator,nSize);
 hs32ToBin(dwRegister,bRegister,nSize);

 this->bRandomBit=bRegister[nSize-1];

 return 0;
}

int tagLFSR32::Remove(void)
{
 unsigned int nMemSize=nSize*sizeof(unsigned char);

 dwRegister=0;
 dwGenerator=0;
 nSize=0;

 memset(bGenerator,0,nMemSize);
 memset(bRegister,0,nMemSize);

 free(bGenerator);
 free(bRegister);

 bGenerator=NULL;
 bRegister=NULL;

 return 0;
}

tagLFSR32::tagLFSR32()
{
 dwGenerator=0;
 dwRegister=0;
 nSize=0;
 bGenerator=NULL;
 bRegister=NULL;
 bRandomBit=0;
}

tagLFSR32::~tagLFSR32()
{
 free(bGenerator);
 free(bRegister);
}