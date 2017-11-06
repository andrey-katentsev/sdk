/* Convert Library */
/* Programmed by Hyperlink Software®, 2009 */
/* E-Mail: hyperlink@inbox.ru */
/* UIN: 282757076 */

#ifndef HS_CONVERT_LIBRARY
#define HS_CONVERT_LIBRARY

#include <string>

#include <tchar.h>
#include <windows.h>

// Основания систем сичсления.
#define BASE2 2
#define BIN BASE2
#define BINARY BASE2

#define BASE8 8
#define OCT BASE8
#define OCTAL BASE8

#define BASE10 10
#define DEC BASE10
#define DECIMAL BASE10

#define BASE16 16
#define HEX BASE16
#define HEXADECIMAL BASE16

// Размер типов данных в битах.
#define SIZE_OF_BYTE   8
#define SIZE_OF_WORD  16
#define SIZE_OF_DWORD 32

#define BYTE_CCH_MAX 3
#define WORD_CCH_MAX 5
#define DWORD_CCH_MAX 10
#define QWORD_CCH_MAX 20

#define INT_CCH_MAX 10
#define LONG_CCH_MAX 10

TCHAR hsDecToHex(BYTE Dec);
BYTE hsHexToDec(TCHAR Hex);

// ДОДЕЛАТЬ: Очищать память!

void hsByteToHex(BYTE Dec,TCHAR Hex[2]); // Преобразует число из диапазона 0-255 в его шестнадцатиричное представление 0x00-0xFF
void hsByteToBin(BYTE Dec,CHAR Bin[SIZE_OF_BYTE]); // Преобразует число из диапазона 0-255 в его двоичное представление 00000000-11111111

BYTE hsHexToByte(const TCHAR Hex[2]); // Преобразует число из диапазона 0x00-0xFF в его десятичное представление 0-255
BYTE hsBinToByte(CHAR Bin[SIZE_OF_BYTE]); // Преобразует число из диапазона 00000000-11111111 в его десятичное представление 0-255
//void hsBinToByte(LPCSTR bBin,LPBYTE bDec);

VOID hsWordToBin(WORD nDec,LPSTR bBin);  // Преобразует число из диапазона 0-65535 в его двоичное представление 0000000000000000-1111111111111111
void hsDWordToBin(unsigned int nDec,unsigned char *bBin); // Преобразует число из диапазона 0-4294967296 в его двоичное представление 00000000000000000000000000000000-11111111111111111111111111111111

void hs32ToBin(DWORD nDec,LPSTR bBin,BYTE nBit); // Преобразует число из диапазона 0-(2^nBit - 1) в его двоичное представление (32 бита)
void hs32ToBin(DWORD nDec,LPBYTE bBin,BYTE nBit); // Преобразует число из диапазона 0-(2^nBit - 1) в его двоичное представление (32 бита)

VOID hs64ToBin(UINT64 nDec,LPBYTE bBin);
VOID hs64ToHex(UINT64 nDec,LPSTR bHex);

DWORD32 hsHexTo32(LPSTR Hexadecimal,BYTE nSize);
UINT64 hsHexTo64(LPSTR Hexadecimal,BYTE nSize);

void hs64ToBin(unsigned __int64 nDec,unsigned char *bBin,unsigned int nBit); // Преобразует число из диапазона 0-(2^nBit - 1) в его двоичное представление (64 бита)

void hsBinToDWord(const unsigned char *bBin,unsigned int *nDec); // Преобразует число из диапазона 00000000000000000000000000000000-11111111111111111111111111111111 в его десятичное представление 0-4294967296

void hsBinTo32(const unsigned char *bBin,unsigned __int32 *nDec,unsigned int nBit); // Преобразует число из двоичного представления (максимум 32 бита) в десятичное число из диапазона 0-(2^nBit - 1)

#pragma region 32-х битные преобразования
DWORD32 hsBinTo32(const BYTE Bin[32]);
DWORD32 hsBinTo32(const LPBYTE Bin,BYTE Bits=32);
#pragma endregion

BYTE hsBinTo8(CONST LPBYTE bBin);     // Переводит число из двоичного представления в десятичное
UINT64 hsBinTo64(CONST LPBYTE lpBin); // Переводит число из двоичного представления в десятичное

HRESULT hsIntegerToString(__in const int nInteger, __out std::wstring& wstrText);
#endif