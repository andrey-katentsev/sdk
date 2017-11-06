#include "hsConvert.h"
#include <math.h>

#include <stdlib.h> // _ltow_s(); _itow_s();

#include <vector>

#pragma region 4-х битные преобразования
// Перевод: 0-15 в '0x0'-'0xF'
// <Контроль качества>
TCHAR hsDecToHex(BYTE Dec)
{
	TCHAR Hex=TEXT('0');
	switch(Dec)
	{
	case 1:
		{ Hex=TEXT('1'); } break;
	case 2:
		{ Hex=TEXT('2'); } break;
	case 3:
		{ Hex=TEXT('3'); } break;
	case 4:
		{ Hex=TEXT('4'); } break;
	case 5:
		{ Hex=TEXT('5'); } break;
	case 6:
		{ Hex=TEXT('6'); } break;
	case 7:
		{ Hex=TEXT('7'); } break;
	case 8:
		{ Hex=TEXT('8'); } break;
	case 9:
		{ Hex=TEXT('9'); } break;
	case 10:
		{ Hex=TEXT('A'); } break;
	case 11:
		{ Hex=TEXT('B'); } break;
	case 12:
		{ Hex=TEXT('C'); } break;
	case 13:
		{ Hex=TEXT('D'); } break;
	case 14:
		{ Hex=TEXT('E'); } break;
	case 15:
		{ Hex=TEXT('F'); } break;
	}
	return Hex;
}

// Перевод: '0x0'-'0xF' в 0-15
// <Контроль качества>
BYTE hsHexToDec(TCHAR Hex)
{
	BYTE Dec=0;
	switch(Hex)
	{
	case TEXT('1'):
		{ Dec=1; } break;
	case TEXT('2'):
		{ Dec=2; } break;
	case TEXT('3'):
		{ Dec=3; } break;
	case TEXT('4'):
		{ Dec=4; } break;
	case TEXT('5'):
		{ Dec=5; } break;
	case TEXT('6'):
		{ Dec=6; } break;
	case TEXT('7'):
		{ Dec=7; } break;
	case TEXT('8'):
		{ Dec=8; } break;
	case TEXT('9'):
		{ Dec=9; } break;
	case TEXT('A'):
		{ Dec=10; } break;
	case TEXT('B'):
		{ Dec=11; } break;
	case TEXT('C'):
		{ Dec=12; } break;
	case TEXT('D'):
		{ Dec=13; } break;
	case TEXT('E'):
		{ Dec=14; } break;
	case TEXT('F'):
		{ Dec=15; } break;
	}
	return Dec;
}

// Перевод: '0000'-'1111' в '0x0'-'0xF'
// <Контроль качества>
TCHAR hsBinToHex(const LPBYTE Bin)
{
 BYTE Dec=0;
 for(register BYTE i=0;i<4;i++)
 {
  if(Bin[i])
  { Dec+=(BYTE)pow(2.0,3.0-(DOUBLE)i); }
 }
 return hsDecToHex(Dec);
}
#pragma endregion

// Преобразует число из диапазона 0-255 в его шестнадцатиричное представление 0x00-0xFF
// <Контроль качества>
void hsByteToHex(BYTE Dec,TCHAR Hex[2])
{
	Hex[0]=hsDecToHex(Dec/16); // Старшие 4 бита
	Hex[1]=hsDecToHex(Dec%16); // Младшие 4 бита
 //Hex[0]=hsDecToHex(Dec>>4);
	//Hex[1]=hsDecToHex(Dec&0x0F);
}

// Преобразует число из диапазона 0-255 в его двоичное представление 00000000-11111111
void hsByteToBin(BYTE Dec,CHAR Bin[SIZE_OF_BYTE])
{
	for(register unsigned int cx=SIZE_OF_BYTE;cx>0;cx--)
	{
		Bin[cx-1]=Dec%2;
		Bin[cx-1]+=0x30;
		Dec/=2;
	}
}

// Преобразует число из диапазона 0x00-0xFF в его десятичное представление 0-255
// <Контроль качества>
BYTE hsHexToByte(const TCHAR Hex[2])
{
 BYTE Dec=0;
	Dec=16*hsHexToDec(Hex[0]);
	Dec+=hsHexToDec(Hex[1]);
 return Dec;
}

// Преобразует число из диапазона 00000000-11111111 в его десятичное представление 0-255
BYTE hsBinToByte(CHAR Bin[SIZE_OF_BYTE])
{
 BYTE Dec=0;
	for(register unsigned int cx=0;cx<SIZE_OF_BYTE;cx++)
	{
		if(Bin[cx]==0x31)
		{ Dec+=(BYTE)pow(2.0,7.0-(double)cx); }
	}
 return Dec;
}

// Преобразует число из диапазона 0-65535 в его двоичное представление 0000000000000000-1111111111111111
VOID hsWordToBin(WORD nDec,LPSTR bBin)
{
 for(register BYTE cx=16;cx>0;cx--)
 {
  bBin[cx-1]=nDec%2;
  bBin[cx-1]+=0x30;
  nDec/=2;
 }
}

// Преобразует число из диапазона 0-4294967296 в его двоичное представление 00000000000000000000000000000000-11111111111111111111111111111111
void hsDWordToBin(unsigned int nDec,unsigned char *bBin)
{
	for(register unsigned int cx=32;cx>0;cx--)
	{
		bBin[cx-1]=nDec%2;
		bBin[cx-1]+=0x30;
		nDec/=2;
	}
}

void hs32ToBin(DWORD nDec,LPSTR bBin,BYTE nBit)
{
	for(register unsigned int cx=nBit;cx>0;cx--)
	{
		bBin[cx-1]=(unsigned char)nDec%2;
		bBin[cx-1]+=0x30;
		nDec/=2;
	}
}

// Преобразует число из диапазона 0-(2^nBit - 1) в его двоичное представление (32 бита)
void hs32ToBin(DWORD nDec,BYTE *bBin,BYTE nBit)
{
 for(register unsigned int cx=nBit;cx>0;cx--)
	{
		bBin[cx-1]=(BYTE)nDec%2;
		nDec/=2;
	}
}

VOID hs64ToBin(UINT64 nDec,LPBYTE bBin)
{
	for(register BYTE cx=64;cx>0;cx--)
	{
		bBin[cx-1]=(BYTE)(nDec%2);
		nDec/=2;
	}
}

void hs64ToBin(unsigned __int64 nDec,unsigned char *bBin,unsigned int nBit)
{
	for(register unsigned int cx=nBit;cx>0;cx--)
	{
		bBin[cx-1]=(unsigned char)nDec%2;
		bBin[cx-1]+=0x30;
		nDec/=2;
	}
}

// Переводит шестидесятичетырёхбитное число в шестнадцатитиричную систему счисления
// <Контроль качества>
VOID hs64ToHex(UINT64 Decimal,LPSTR Hexadecimal)
{
 BYTE Binary[64];
 hs64ToBin(Decimal,Binary);
 for(register BYTE i=0;i<16;i++)
 { Hexadecimal[i]=hsBinToHex(&Binary[i*4]); }
}

// Входные параметры:
// [in] Hexadecimal - Число в шестнадцатиричном представлении
// [in] nSize       - Длина строки (Количество шестнадцатирицных разрядов)
// Возвращаемое значение:
// Тридцатидвухбитовое беззнаковое число
// <Контроль качества>
DWORD32 hsHexTo32(LPSTR Hexadecimal,BYTE nSize)
{
 DWORD32 Decimal=0x00000000;
 if(nSize>8)
 { return 0xFFFFFFFF; }
 for(register BYTE i=nSize;i>0;i--)
 { Decimal+=((DWORD32)pow(16.0,(DOUBLE)i-1.0)*(DWORD32)hsHexToDec(Hexadecimal[nSize-i])); }
 return Decimal;
}

// Входные параметры:
// [in] Hexadecimal - Число в шестнадцатиричном представлении
// [in] nSize       - Длина строки (Количество шестнадцатирицных разрядов)
// Возвращаемое значение:
// Шестидесятичетырёхбитное беззнаковое число.
UINT64 hsHexTo64(LPSTR Hexadecimal,BYTE nSize)
{
 UINT64 Decimal=0;
 if(nSize>16)
 { return 0xFFFFFFFFFFFFFFFF; }
 for(register BYTE i=nSize;i>0;i--)
 { Decimal+=((UINT64)pow(16.0,(DOUBLE)i-1.0)*(UINT64)hsHexToDec(Hexadecimal[nSize-i])); }
 return Decimal;
}

// Преобразует число из диапазона 00000000000000000000000000000000-11111111111111111111111111111111 в его десятичное представление 0-4294967296
void hsBinToDWord(const unsigned char *bBin,unsigned int *nDec)
{
	for(register unsigned int cx=0;cx<32;cx++)
	{
		if(bBin[cx]==0x31)
		{ *nDec+=(unsigned int)pow(2.0,31.0-(double)cx); }
	}
}

// Преобразует число из двоичного представления (максимум 32 бита) в десятичное число из диапазона 0-(2^nBit - 1)
void hsBinTo32(const unsigned char *bBin,unsigned __int32 *nDec,unsigned int nBit)
{
	for(register unsigned int cx=0;cx<nBit;cx++)
	{
		if(bBin[cx]==0x31)
		{ *nDec+=(unsigned int)pow(2.0,((double)nBit-1.0)-(double)cx); }
	}
}

#pragma region 32-х битные преобразования
// <Контроль качества>
DWORD32 hsBinTo32(const BYTE Bin[32])
{
 DWORD32 Dec=0;
 for(register BYTE i=0;i<32;i++)
 {
  if(Bin[i])
		{ Dec+=(DWORD32)pow(2.0,31.0-i); }
 }
 return Dec;
}

DWORD32 hsBinTo32(const LPBYTE Bin,BYTE Bits)
{
 DWORD32 Dec=0;

 if(Bits>32)
 { return 0xFFFFFFFF; }

 for(register BYTE i=0;i<Bits;i++)
	{
  if(Bin[i])
		{ Dec+=(DWORD32)pow(2.0,Bits-i-1); }
	}
 return Dec;
}
#pragma endregion

// [in] lpBin - указатель на последовательность из 64 байт со значениями [0,1]
// <Контроль качества>
UINT64 hsBinTo64(CONST LPBYTE lpBin)
{
 UINT64 uDec=0;
 for(register BYTE i=0;i<64;i++)
 { uDec+=lpBin[i]?(UINT64)pow(2.0,63.0-(DOUBLE)i):0; }
 return uDec;
}

// <Контроль качества>
BYTE hsBinTo8(CONST LPBYTE bBin)
{
 BYTE bDec=0;
 for(register BYTE i=0;i<8;i++)
 { bDec+=bBin[i]?(BYTE)pow(2.0,7.0-(DOUBLE)i):0; }
 return bDec;
}

// BEGIN
#define TERMINAL_NULL '\0'

#define STRING2(x) #x
#define STRING(x) STRING2(x)

#pragma message (__FILE__ "(" STRING(__LINE__) ") : WARNING: Move definition to situable header.")

template <typename T>
inline typename std::vector<T>::size_type hsFind(const std::vector<T>& vector, const T& value)
{
	std::vector<T>::size_type index, last = vector.size();
	for(index = 0; index < last; index++)
	{
		if(value == vector[index])
			return index;
	}
	return static_cast<std::vector<T>::size_type>(-1);
}
// END

#define HS_ITS_BUFFER_INITIALIZER 0
HRESULT hsIntegerToString(int const nInteger, std::wstring& wstrText)
{
	HRESULT hResult = E_FAIL;
	std::vector<wchar_t> vecBuffer(INT_CCH_MAX + 1, HS_ITS_BUFFER_INITIALIZER);
	wstrText.clear();
_itow_s(nInteger, &vecBuffer[0], vecBuffer.size(), BASE10);
	wstrText.assign(vecBuffer.begin(), vecBuffer.begin() + hsFind(vecBuffer, TEXT(TERMINAL_NULL))); // unsafe use of hsFind().
	return hResult;
}