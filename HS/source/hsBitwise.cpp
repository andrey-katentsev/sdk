/* Bitwise Operators */
/* Designed and Programmed by Hyperlink Software�, 2006-2009. */
/* Copyright by Hyperlink Software�, 2006-2009. */

/* Contacts: */
/* E-Mail: hyperlink@inbox.ru */
/* UIN: 282757076 */

#include "hsBitwise.h"
#include "hsConvert.h"

// ����������� ����� ������ �� ��������� ����� ��� [Right Circular Shift (RCS)]
// ���������:
// [in] dwData - ������ (32 ����)
// [in] nBits  - ���������� ��� ��� ������
// ������������ ��������:
// �������� ����� ������������ ������
// <�������� ��������>
DWORD32 hsRCS32(DWORD32 dwData,BYTE nBits)
{
 nBits&=0x1F;
 return (dwData>>nBits) OR (dwData<<(32-nBits));
}

// ����������� ����� ����� �� ��������� ����� ��� [Left Circular Shift (LCS)]
// ���������:
// [in] dwData - ������ (32 ����)
// [in] nBits  - ���������� ��� ��� ������
// ������������ ��������:
// �������� ����� ������������ ������
// <�������� ��������>
DWORD32 hsLCS32(DWORD32 dwData,BYTE nBits)
{
 nBits&=0x1F;
 return (dwData<<nBits) OR (dwData>>(32-nBits));
}

// �������������� ����
// ���������:
// [in] bData - ������ (8 ����)
// [in] nBit  - ����� ����, ������� ����� �������������
// ������������ ��������:
// �������� ����� �������� ���������������� ����
// <�������� ��������>
// �� �������������� ����� nBit �� ��������� [1,8]
BYTE hsInverseBit(BYTE bData,BYTE nBit)
{
 BYTE bBin[8];
 BYTE bDec=0;
 ZeroMemory(bBin,8*sizeof(BYTE));
 bBin[8-nBit]=1;
 bDec=hsBinTo8(bBin);
 return bData XOR bDec;
}

// �������������� ����
// <�������� ��������>
// �� �������������� ����� nBit �� ��������� [1,32]
DWORD32 hsInverseBit(DWORD32 dwData,BYTE nBit)
{
 BYTE bBin[32];
 DWORD32 dwDec=0;
 ZeroMemory(bBin,32*sizeof(BYTE));
 bBin[32-nBit]=1;
 dwDec=hsBinTo32(bBin);
 return dwData XOR dwDec;
}

// �������������� ����
// <�������� ��������>
// �� �������������� ����� nBit �� ��������� [1,64]
DWORD64 hsInverseBit(DWORD64 dwData,BYTE nBit)
{
 BYTE bBin[64];
 DWORD64 dwDec=0;
 ZeroMemory(bBin,64*sizeof(BYTE));
 bBin[64-nBit]=1;
 dwDec=hsBinTo64(bBin);
 return dwData XOR dwDec;
}


VOID hsInverseBit256(BYTE Input[32],BYTE Output[32],DWORD32 dwBit)
{
 BYTE Index=31;
 CopyMemory(Output,Input,32*sizeof(BYTE));
 while(dwBit>8)
 {
  dwBit-=8;
  Index--;
 }
 Output[Index]=hsInverseBit(Input[Index],(BYTE)dwBit);
}

VOID hsInverseBit256(DWORD32 dwInput[8],DWORD32 dwOutput[8],DWORD32 dwBit)
{
 BYTE Index=7;
 CopyMemory(dwOutput,dwInput,8*sizeof(DWORD32));
 while(dwBit>32)
 {
  dwBit-=32;
  Index--;
 }
 dwOutput[Index]=hsInverseBit(dwInput[Index],(BYTE)dwBit);
}

// �������������� ����
// <�������� ��������>
// �� �������������� ����� nBit �� ��������� [1,256]
/*DWORD32 hsInverseBit(CONST DWORD32 dwIn[8],DWORD32 dwOut[8],BYTE nBit)
{
 BYTE bBin[32];
 DWORD32 dwDec=0;
 ZeroMemory(bBin,32*sizeof(BYTE));
 bBin[32-nBit%32]=1;
 dwDec=hsBinTo32(bBin);
 CopyMemory(dwOut,dwIn,8*sizeof(DWORD32));
 dwOut[8-nBit/32]^=dwDec;
 return dwData XOR dwDec;
}*/