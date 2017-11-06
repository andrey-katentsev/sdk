#include "hsChecksum.h"
#include "hsBitwise.h"

BYTE hsParityByte(CONST LPBYTE lpData,DWORD dwDataSize)
{
 BYTE ParityByte=0;
 for(REGISTER DWORD i=0;i<dwDataSize;i++)
 { ParityByte^=lpData[i]; }
 return ParityByte;
}

BYTE hsLRC(CONST LPBYTE lpData,DWORD dwDataSize)
{
 BYTE LRC=0;
 for(REGISTER DWORD i=0;i<dwDataSize;i++)
 { LRC+=lpData[i]; }
 LRC=0xFF-LRC; // Первое дополнение
 LRC+=0x01;    // Второе дополнение
 return LRC;   // 1) CS = 0xFF - CS; 2) CS = CS + 0x01; Альтернативная операция: CS=-CS;
}

WORD hsCRC16(CONST LPBYTE lpData,DWORD dwDataSize,WORD wPolynomial)
{
 WORD CRC16=0xFFFF;
 for(REGISTER DWORD i=0;i<dwDataSize;i++)
 {
  CRC16^=lpData[i];
  for(REGISTER BYTE j=0;j<8;j++)
  {
   CRC16=(CRC16&0x0001)?(CRC16^wPolynomial):(CRC16);
   CRC16>>=1;
   //CRC16=(CRC16&0x0001)?(CRC16^wPolynomial):(CRC16);
  }
 }
 return CRC16;
}

DWORD hsCRC32(CONST LPBYTE lpData,DWORD dwDataSize,DWORD dwPolynomial)
{
 DWORD CRC32=0xFFFFFFFF;
 for(REGISTER DWORD i=0;i<dwDataSize;i+=2)
 {
  CRC32^=MAKEWORD(lpData[i+1],lpData[i]);
  for(REGISTER BYTE j=0;j<16;j++)
  {
   CRC32=(CRC32&0x00000001)?(CRC32^dwPolynomial):(CRC32);
   CRC32>>=1;
   //CRC32=(CRC32&0x00000001)?(CRC32^dwPolynomial):(CRC32);
  }
 }
 return CRC32;
}