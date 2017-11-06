/* Convert Library */
/* Programmed by Hyperlink Software�, 2009 */
/* E-Mail: hyperlink@inbox.ru */
/* UIN: 282757076 */

#ifndef HS_CONVERT_LIBRARY
#define HS_CONVERT_LIBRARY

#include <string>

#include <tchar.h>
#include <windows.h>

// ��������� ������ ���������.
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

// ������ ����� ������ � �����.
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

// ��������: ������� ������!

void hsByteToHex(BYTE Dec,TCHAR Hex[2]); // ����������� ����� �� ��������� 0-255 � ��� ����������������� ������������� 0x00-0xFF
void hsByteToBin(BYTE Dec,CHAR Bin[SIZE_OF_BYTE]); // ����������� ����� �� ��������� 0-255 � ��� �������� ������������� 00000000-11111111

BYTE hsHexToByte(const TCHAR Hex[2]); // ����������� ����� �� ��������� 0x00-0xFF � ��� ���������� ������������� 0-255
BYTE hsBinToByte(CHAR Bin[SIZE_OF_BYTE]); // ����������� ����� �� ��������� 00000000-11111111 � ��� ���������� ������������� 0-255
//void hsBinToByte(LPCSTR bBin,LPBYTE bDec);

VOID hsWordToBin(WORD nDec,LPSTR bBin);  // ����������� ����� �� ��������� 0-65535 � ��� �������� ������������� 0000000000000000-1111111111111111
void hsDWordToBin(unsigned int nDec,unsigned char *bBin); // ����������� ����� �� ��������� 0-4294967296 � ��� �������� ������������� 00000000000000000000000000000000-11111111111111111111111111111111

void hs32ToBin(DWORD nDec,LPSTR bBin,BYTE nBit); // ����������� ����� �� ��������� 0-(2^nBit - 1) � ��� �������� ������������� (32 ����)
void hs32ToBin(DWORD nDec,LPBYTE bBin,BYTE nBit); // ����������� ����� �� ��������� 0-(2^nBit - 1) � ��� �������� ������������� (32 ����)

VOID hs64ToBin(UINT64 nDec,LPBYTE bBin);
VOID hs64ToHex(UINT64 nDec,LPSTR bHex);

DWORD32 hsHexTo32(LPSTR Hexadecimal,BYTE nSize);
UINT64 hsHexTo64(LPSTR Hexadecimal,BYTE nSize);

void hs64ToBin(unsigned __int64 nDec,unsigned char *bBin,unsigned int nBit); // ����������� ����� �� ��������� 0-(2^nBit - 1) � ��� �������� ������������� (64 ����)

void hsBinToDWord(const unsigned char *bBin,unsigned int *nDec); // ����������� ����� �� ��������� 00000000000000000000000000000000-11111111111111111111111111111111 � ��� ���������� ������������� 0-4294967296

void hsBinTo32(const unsigned char *bBin,unsigned __int32 *nDec,unsigned int nBit); // ����������� ����� �� ��������� ������������� (�������� 32 ����) � ���������� ����� �� ��������� 0-(2^nBit - 1)

#pragma region 32-� ������ ��������������
DWORD32 hsBinTo32(const BYTE Bin[32]);
DWORD32 hsBinTo32(const LPBYTE Bin,BYTE Bits=32);
#pragma endregion

BYTE hsBinTo8(CONST LPBYTE bBin);     // ��������� ����� �� ��������� ������������� � ����������
UINT64 hsBinTo64(CONST LPBYTE lpBin); // ��������� ����� �� ��������� ������������� � ����������

HRESULT hsIntegerToString(__in const int nInteger, __out std::wstring& wstrText);
#endif