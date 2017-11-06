/* Bitwise Operators */
/* Designed and Programmed by Hyperlink Software®, 2006-2009. */
/* Copyright by Hyperlink Software®, 2006-2009. */

/* Contacts: */
/* E-Mail: hyperlink@inbox.ru */
/* UIN: 282757076 */

#pragma once

#ifndef HS_BITWISE_OPERATORS
#define HS_BITWISE_OPERATORS
#endif

#include <windows.h>

#pragma warning(disable:4333) // warning C4333: '>>' right shift by too large amount, data loss
#pragma warning(disable:4293) // warning C4293: '<<' shift count negative or too big, undefined behavior

// Старший бит [HIGH] | 64 63 62 61 60 59 58 57 56 ... 8 7 6 5 4 3 2 1 | Младший бит [LOW]

#define AND & // Bitwise AND

/*
0 AND 0 = 0
0 AND 1 = 0
1 AND 0 = 0
1 AND 1 = 1
*/

#define OR | // Bitwise Inclusive OR

/*
0 OR 0 = 0
0 OR 1 = 1
1 OR 0 = 1
1 OR 1 = 1
*/

#define XOR ^ // Bitwise Exclusive OR

/*
0 XOR 0 = 0
0 XOR 1 = 1
1 XOR 0 = 1
1 XOR 1 = 0
*/

#define and AND
#define or  OR
#define xor XOR

#define SHIFT_LEFT(n) <<(n)  // Bitwise left shift
#define SHIFT_RIGHT(n) >>(n) // Bitwise right shift

#define SWAP_BYTES(W) (WORD)((WORD)W>>8 OR (WORD)W<<8)
#define SWAP_BYTES_ORDER(DW) (DWORD)((DWORD)DW>>24 OR (DWORD)DW<<24 OR ((DWORD)DW>>8 AND 0x0000FF00) OR ((DWORD)DW<<8 AND 0x00FF0000))

#define INVERSE_BYTE(B)       (BYTE)((BYTE)B XOR 0xFF)
#define INVERSE_WORD(W)       (WORD)((WORD)W XOR 0xFFFF)
#define INVERSE_DWORD(D)      (DWORD)((DWORD)D XOR 0xFFFFFFFF)

#define INVERSE_DWORD32(DW32) ((DWORD32)DW32 XOR 0xFFFFFFFF)
#define INVERSE_DWORD64(DW64) ((DWORD64)DW64 XOR 0xFFFFFFFFFFFFFFFF)

#define GET_BYTE_BIT(B,bit)   (((BYTE)B SHIFT_RIGHT(bit-1)) AND 0x01)
#define SET_BYTE_BIT(B,bit)   (((((BYTE)B SHIFT_RIGHT(bit-1)) OR 0x01) SHIFT_LEFT(bit-1)) OR (BYTE)B)
#define CLEAR_BYTE_BIT(B,bit) (((((BYTE)B SHIFT_RIGHT(bit-1)) AND 0xFE) SHIFT_LEFT(bit-1)) OR ((BYTE)((BYTE)B SHIFT_LEFT(8-(bit-1))) SHIFT_RIGHT(8-(bit-1))))

#define SET_BYTE_BIT_VALUE(B,bit,value) if(value){B=SET_BYTE_BIT(B,bit);}else{B=CLEAR_BYTE_BIT(B,bit);}

#define GET_BYTE_HI_BITS(n,byte) ((BYTE)byte>>(8-n))
#define GET_BYTE_LO_BITS(n,byte) ((BYTE)((BYTE)byte<<(8-n))>>(8-n))

#define SET_BYTE_HI_BITS(n,byte,value) (BYTE)byte=((BYTE)((BYTE)((BYTE)byte<<(8-n))>>(8-n)) OR (BYTE)((BYTE)value<<(8-n)))
#define SET_BYTE_LO_BITS(n,byte,value) (BYTE)byte=((BYTE)((BYTE)((BYTE)byte>>(8-n))<<(8-n)) OR (BYTE)((BYTE)value AND (BYTE)(0xFF>>(8-n))))

#pragma region DWORD32
#define GET_DWORD32_BIT(DW32,bit) (((DWORD32)DW32 >> (bit-1)) AND 0x00000001)
#define SET_DWORD32_BIT(DW32,bit) (((((DWORD32)DW32 >> (bit-1)) OR 0x00000001) << (bit-1)) OR (DWORD32)DW32)
#define CLR_DWORD32_BIT(DW32,bit) (((((DWORD32)DW32 >> (bit-1)) AND 0xFFFFFFFE) << (bit-1)) OR (((DWORD32)DW32 << (32-(bit-1))) >> (32-(bit-1))))

#define SET_DWORD32_BIT_VALUE(DW32,bit,value) value?SET_DWORD32_BIT(DW32,bit):CLR_DWORD32_BIT(DW32,bit)
#pragma endregion

#pragma region DWORD64
#define GET_DWORD64_BIT(DW64,bit) (((DWORD64)DW64 >> (bit-1)) AND 0x0000000000000001)
#define SET_DWORD64_BIT(DW64,bit) (((((DWORD64)DW64 >> (bit-1)) OR 0x0000000000000001) << (bit-1)) OR (DWORD64)DW64)
#define CLR_DWORD64_BIT(DW64,bit) (((((DWORD64)DW64 >> (bit-1)) AND 0xFFFFFFFFFFFFFFFE) << (bit-1)) OR (((DWORD64)DW64 << (64-(bit-1))) >> (64-(bit-1))))

#define SET_DWORD64_BIT_VALUE(DW64,bit,value) value?SET_DWORD64_BIT(DW64,bit):CLR_DWORD64_BIT(DW64,bit)
#pragma endregion

#define HS_MAKEWORD(HB,LB)      ((WORD)LB AND 0xFF) OR (((WORD)HB AND 0xFF)<<8)
#define HS_MAKEDWORD(HW,LW)     ((DWORD)LW AND 0xFFFF) OR (((DWORD)HW AND 0xFFFF)<<16)
#define HS_MAKEDWORD32(HW,LW)   ((DWORD32)LW AND 0xFFFF) OR (((DWORD32)HW AND 0xFFFF)<<16)
#define HS_MAKEDWORD64(HDW,LDW) ((DWORD64)LDW AND 0xFFFFFFFF) OR (((DWORD64)HDW AND 0xFFFFFFFF)<<32)

#define HS_LODWORD32(DW64)      (DWORD32)((DWORD64)DW64 AND 0xFFFFFFFF)
#define HS_HIDWORD32(DW64)      (DWORD32)(((DWORD64)DW64 >> 32) AND 0xFFFFFFFF)

DWORD32 hsRCS32(DWORD32 dwData,BYTE nBits); // Циклический сдвиг вправо на nBits
DWORD32 hsLCS32(DWORD32 dwData,BYTE nBits); // Циклический сдвиг влево на nBits

// Инвертирование бита
BYTE hsInverseBit(BYTE bData,BYTE nBit);
DWORD32 hsInverseBit(DWORD32 dwData,BYTE nBit);
DWORD64 hsInverseBit(DWORD64 dwData,BYTE nBit);

VOID hsInverseBit256(BYTE Input[32],BYTE Output[32],DWORD32 dwBit);
VOID hsInverseBit256(DWORD32 dwInput[8],DWORD32 dwOutput[8],DWORD32 dwBit);