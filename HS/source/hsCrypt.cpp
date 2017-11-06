#include "hsCrypt.h"
//#include "hsWin32Errors.h"
#include "hsErrors.h"
#include "hsBitwise.h"

#include "hsMath.h"

// Шифрование путём наложениея гамма-последовательности на открытый текст.
// Параметры:
// [in]  PlainText   - данные для шифрования (открытый текст).
// [out] ChipherText - зашифрованные данные (зашифрованный текст).
// [in]  Key         - ключ шифрования (гамма-последовательность).
// [in]  DataSize    - размер данных для шифрования/размер ключа.
// <Контроль качества>
void hsGammaXOR(const LPBYTE Data,LPBYTE EncryptedData,const LPBYTE Key,DWORD32 DataSize)
{
 // Побайтовое сложение по модулю два данных и ключа шифрования.
 for(register DWORD32 i=0;i<DataSize;i++)
 { EncryptedData[i]=Data[i] XOR Key[i]; }
}

// S-block (Substitution - замена [подстановка])
// Шифр замены — шифр, для получения шифротекста последовательно заменяющий символы сообщения на другие (того-же, или другого набора) согласно некоторому закону соответствия, оставляя их на своих местах.

BYTE S(BYTE bByte)
{ return INVERSE_BYTE(bByte); }

// 4-х битный S-блок
// Таблица замены:
// 0000 ~ 0010 [0x0,0x2]
// 0001 ~ 0100 [0x1,0x4]
// 0010 ~ 1100 [0x2,0xC]
// 0011 ~ 1110 [0x3,0xE]
// 0100 ~ 0111 [0x4,0x7]
// 0101 ~ 1011 [0x5,0xB]
// 0110 ~ 1000 [0x6,0x8]
// 0111 ~ 0011 [0x7,0x3]
// 1000 ~ 0001 [0x8,0x1]
// 1001 ~ 1001 [0x9,0x9]
// 1010 ~ 0110 [0xA,0x6]
// 1011 ~ 0000 [0xB,0x0]
// 1100 ~ 0101 [0xC,0x5]
// 1101 ~ 1111 [0xD,0xF]
// 1110 ~ 1101 [0xE,0xD]
// 1111 ~ 1010 [0xF,0xA]
// <Контроль качества>
BYTE S4(BYTE bBlock)
{
 // Старшие 4 бита
 switch(GET_BYTE_HI_BITS(4,bBlock))
 {
 case 0x0:
  { SET_BYTE_HI_BITS(4,bBlock,0x2); } break;
 case 0x1:
  { SET_BYTE_HI_BITS(4,bBlock,0x4); } break;
 case 0x2:
  { SET_BYTE_HI_BITS(4,bBlock,0xC); } break;
 case 0x3:
  { SET_BYTE_HI_BITS(4,bBlock,0xE); } break;
 case 0x4:
  { SET_BYTE_HI_BITS(4,bBlock,0x7); } break;
 case 0x5:
  { SET_BYTE_HI_BITS(4,bBlock,0xB); } break;
 case 0x6:
  { SET_BYTE_HI_BITS(4,bBlock,0x8); } break;
 case 0x7:
  { SET_BYTE_HI_BITS(4,bBlock,0x3); } break;
 case 0x8:
  { SET_BYTE_HI_BITS(4,bBlock,0x1); } break;
 case 0x9:
  { SET_BYTE_HI_BITS(4,bBlock,0x9); } break;
 case 0xA:
  { SET_BYTE_HI_BITS(4,bBlock,0x6); } break;
 case 0xB:
  { SET_BYTE_HI_BITS(4,bBlock,0x0); } break;
 case 0xC:
  { SET_BYTE_HI_BITS(4,bBlock,0x5); } break;
 case 0xD:
  { SET_BYTE_HI_BITS(4,bBlock,0xF); } break;
 case 0xE:
  { SET_BYTE_HI_BITS(4,bBlock,0xD); } break;
 case 0xF:
  { SET_BYTE_HI_BITS(4,bBlock,0xA); } break;
 }
 // Младшие 4 бита
 switch(GET_BYTE_LO_BITS(4,bBlock))
 {
 case 0x0:
  { SET_BYTE_LO_BITS(4,bBlock,0x2); } break;
 case 0x1:
  { SET_BYTE_LO_BITS(4,bBlock,0x4); } break;
 case 0x2:
  { SET_BYTE_LO_BITS(4,bBlock,0xC); } break;
 case 0x3:
  { SET_BYTE_LO_BITS(4,bBlock,0xE); } break;
 case 0x4:
  { SET_BYTE_LO_BITS(4,bBlock,0x7); } break;
 case 0x5:
  { SET_BYTE_LO_BITS(4,bBlock,0xB); } break;
 case 0x6:
  { SET_BYTE_LO_BITS(4,bBlock,0x8); } break;
 case 0x7:
  { SET_BYTE_LO_BITS(4,bBlock,0x3); } break;
 case 0x8:
  { SET_BYTE_LO_BITS(4,bBlock,0x1); } break;
 case 0x9:
  { SET_BYTE_LO_BITS(4,bBlock,0x9); } break;
 case 0xA:
  { SET_BYTE_LO_BITS(4,bBlock,0x6); } break;
 case 0xB:
  { SET_BYTE_LO_BITS(4,bBlock,0x0); } break;
 case 0xC:
  { SET_BYTE_LO_BITS(4,bBlock,0x5); } break;
 case 0xD:
  { SET_BYTE_LO_BITS(4,bBlock,0xF); } break;
 case 0xE:
  { SET_BYTE_LO_BITS(4,bBlock,0xD); } break;
 case 0xF:
  { SET_BYTE_LO_BITS(4,bBlock,0xA); } break;
 }
 return bBlock;
}

//BYTE S8(BYTE bBlock);     // 8-ми битный S-блок
//WORD S16(WORD wBlock);    // 16-ти битный S-блок
//DWORD S32(DWORD dwBlock); // 32-х битный S-блок

// Доделать (не учитывать пробелы)
//DWORD hsCaesarChipher(LPBYTE lpPlainText,LPBYTE lpChipherText,DWORD dwTextSize,BYTE bKey,CONST LPBYTE lpAlphabet,BYTE bAlphabetSize,BOOL bDecode); // Шифр Цезаря

/*
- Шифр Атбаш
- Шифр Кодовое слово
- Шифр Вернама
*/

// P-block (Permutation - перестановка) [Частный случай S-блока, к P-блоку сводится циклический сдвиг]
// Шифр перестановки — шифр, переставляющий символы сообщения между собой для получения шифротекста, так что символы, оставаясь сами собой меняют свою позицию в сообщении.

WORD P(WORD wWord)
{
 BYTE LB=0,HB=0;
 BYTE LoByte=LOBYTE(wWord);
 BYTE HiByte=HIBYTE(wWord);

 SET_BYTE_BIT_VALUE(HB,8,GET_BYTE_BIT(HiByte,8));
 SET_BYTE_BIT_VALUE(HB,4,GET_BYTE_BIT(HiByte,7));
 SET_BYTE_BIT_VALUE(LB,8,GET_BYTE_BIT(HiByte,6));
 SET_BYTE_BIT_VALUE(LB,4,GET_BYTE_BIT(HiByte,5));
 SET_BYTE_BIT_VALUE(HB,7,GET_BYTE_BIT(HiByte,4));
 SET_BYTE_BIT_VALUE(HB,3,GET_BYTE_BIT(HiByte,3));
 SET_BYTE_BIT_VALUE(LB,7,GET_BYTE_BIT(HiByte,2));
 SET_BYTE_BIT_VALUE(LB,3,GET_BYTE_BIT(HiByte,1));

 SET_BYTE_BIT_VALUE(HB,6,GET_BYTE_BIT(LoByte,8));
 SET_BYTE_BIT_VALUE(HB,2,GET_BYTE_BIT(LoByte,7));
 SET_BYTE_BIT_VALUE(LB,6,GET_BYTE_BIT(LoByte,6));
 SET_BYTE_BIT_VALUE(LB,2,GET_BYTE_BIT(LoByte,5));
 SET_BYTE_BIT_VALUE(HB,5,GET_BYTE_BIT(LoByte,4));
 SET_BYTE_BIT_VALUE(HB,1,GET_BYTE_BIT(LoByte,3));
 SET_BYTE_BIT_VALUE(LB,5,GET_BYTE_BIT(LoByte,2));
 SET_BYTE_BIT_VALUE(LB,1,GET_BYTE_BIT(LoByte,1));

 return MAKEWORD(LB,HB);
}

// 16-ти битный P-блок
// Таблица перестановок:
// 16 -> 10
// 15 -> 3
// 14 -> 12
// 13 -> 14
// 12 -> 11
// 11 -> 16
// 10 -> 2
//  9 -> 8
//  8 -> 15
//  7 -> 9
//  6 -> 7
//  5 -> 1
//  4 -> 13
//  3 -> 5
//  2 -> 4
//  1 -> 6
WORD P16(WORD wBlock)
{
 BYTE LB=0,HB=0;
 BYTE LoByte=LOBYTE(wBlock);
 BYTE HiByte=HIBYTE(wBlock);

 SET_BYTE_BIT_VALUE(HB,2,GET_BYTE_BIT(HiByte,8));
 SET_BYTE_BIT_VALUE(LB,3,GET_BYTE_BIT(HiByte,7));
 SET_BYTE_BIT_VALUE(HB,4,GET_BYTE_BIT(HiByte,6));
 SET_BYTE_BIT_VALUE(HB,6,GET_BYTE_BIT(HiByte,5));
 SET_BYTE_BIT_VALUE(HB,3,GET_BYTE_BIT(HiByte,4));
 SET_BYTE_BIT_VALUE(HB,8,GET_BYTE_BIT(HiByte,3));
 SET_BYTE_BIT_VALUE(LB,2,GET_BYTE_BIT(HiByte,2));
 SET_BYTE_BIT_VALUE(LB,8,GET_BYTE_BIT(HiByte,1));

 SET_BYTE_BIT_VALUE(HB,7,GET_BYTE_BIT(LoByte,8));
 SET_BYTE_BIT_VALUE(HB,1,GET_BYTE_BIT(LoByte,7));
 SET_BYTE_BIT_VALUE(LB,7,GET_BYTE_BIT(LoByte,6));
 SET_BYTE_BIT_VALUE(LB,1,GET_BYTE_BIT(LoByte,5));
 SET_BYTE_BIT_VALUE(HB,5,GET_BYTE_BIT(LoByte,4));
 SET_BYTE_BIT_VALUE(LB,5,GET_BYTE_BIT(LoByte,3));
 SET_BYTE_BIT_VALUE(LB,4,GET_BYTE_BIT(LoByte,2));
 SET_BYTE_BIT_VALUE(LB,6,GET_BYTE_BIT(LoByte,1));

 return MAKEWORD(LB,HB);
}

// 32-х битный P-блок
DWORD P32(DWORD dwBlock)
{ return dwBlock; }

// 16-ти битное SP-преобразование
// S - функция замены
// P - функция перестановки
// <Контроль качества>
WORD hsSP16(WORD wBlock,BYTE (*S)(BYTE),WORD (*P)(WORD))
{ return P(MAKEWORD(S(LOBYTE(wBlock)),S(HIBYTE(wBlock)))); }

DWORD hsSPN16(CONST LPBYTE bPlainText,DWORD dwTextLength,LPBYTE bChipherText,DWORD dwRounds,BYTE (*S)(BYTE),WORD (*P)(WORD))
{
 WORD W=0;
 //BYTE LB=0,HB=0;
 LPBYTE SRC=bPlainText;
 LPBYTE DST=bChipherText;

 if(dwTextLength MOD 2)
 { return (DWORD)(-1); }

 for(register DWORD i=0;i<dwRounds;i++)
 {
  for(register DWORD j=0;j<dwTextLength;j+=2)
  {
   //HB=S(SRC[j]);
   //LB=S(SRC[j+1]);
   //W=P(MAKEWORD(LB,HB));
   W=hsSP16(MAKEWORD(SRC[j+1],SRC[j]),S,P);
   DST[j]=HIBYTE(W);
   DST[j+1]=LOBYTE(W);
  }
  SRC=DST;
 }
 return 0;
}

// Простое итерационное шифрование
/*DWORD hsSPC16(CONST LPBYTE bPlainText,DWORD dwTextLength,LPBYTE bChipherText,WORD wKey,DWORD dwRounds,BYTE (*S)(BYTE),WORD (*P)(WORD))
{
 WORD wBlock=0;
 return wBlock;
}*/

DWORD hsCaesarChipher(LPBYTE lpPlainText,LPBYTE lpChipherText,DWORD dwTextSize,BYTE bKey,CONST LPBYTE lpAlphabet,BYTE bAlphabetSize,BOOL bDecode)
{
 BOOL bFound=FALSE;
 LPBYTE M=NULL;   // Сообщение для шифрования/дешифрования (нумерованое)
 LPBYTE In=NULL;  // Сообщение для шифрования/дешифрования (исходное)
 LPBYTE Out=NULL; // Зашифрованное/Расшифрованное сообщение

 M=new BYTE[dwTextSize];
 ZeroMemory(M,dwTextSize*sizeof(BYTE));

 switch(bDecode)
 {
 case FALSE: // Кодируем
  {
   In=lpPlainText;
   Out=lpChipherText;
  } break;
 case TRUE:  // Декодируем
  {
   In=lpChipherText;
   Out=lpPlainText;
  } break;
 default:
  { return -1; }
 }

 // Нумеруем символы в соответствии с порядковым номером в алфавите
 for(register DWORD i=0;i<dwTextSize;i++)
 {
  bFound=FALSE;
  for(register BYTE j=0;j<bAlphabetSize && !bFound;j++)
  {
   if(lpAlphabet[j]==In[i])
   {
    M[i]=j;
    bFound=TRUE;
   }
  }
 }

 // Шифр Цезаря
 switch(bDecode)
 {
 case FALSE: // Кодируем
  {
   for(register DWORD i=0;i<dwTextSize;i++)
   { Out[i]=(M[i]+bKey>0xFF)?(M[i] MOD 0x100):((M[i]+bKey) MOD bAlphabetSize); }
  } break;
 case TRUE: // Декодируем
  {
   for(register DWORD i=0;i<dwTextSize;i++)
   { Out[i]=(bKey>M[i])?(bAlphabetSize-bKey+M[i]):((M[i]-bKey) MOD bAlphabetSize); }
  } break;
 }

 // Сопоставляем порядковым номерам символы алфавита
 for(register DWORD i=0;i<dwTextSize;i++)
 { Out[i]=lpAlphabet[Out[i] MOD bAlphabetSize]; }

 delete [] M;
 return 0;
}

#pragma region Сеть Фейстеля [Feistel Network]
// 64-х битное преобразование Фейстеля
// Параметры:
// [in] dwData - блок данных
// [in] dwKey  - ключ
// [in] F      - образующая функция
// Возвращаемое значение:
// Зашифрованный блок данных
// <Контроль качества>
DWORD64 hsFeistel64(DWORD64 dwData,DWORD32 dwKey,DWORD32 (*F)(DWORD32 dwData,DWORD32 dwKey))
{
 DWORD32 dwL=HS_HIDWORD32(dwData); // Левый блок
 DWORD32 dwR=HS_LODWORD32(dwData); // Правый блок
 DWORD32 dwF=F(dwL,dwKey);         // Вычисляем значение образующующей функции
 dwR^=dwF;                         // Складываем значение образующеё функции с правым блоком суммой по модулю 2
 return HS_MAKEDWORD64(dwR,dwL);   // Обмен блоков
}

// Обмен 32-х битных блоков
// <Контроль качества>
DWORD64 hsExchange(DWORD64 dwData)
{
 DWORD32 dwL=HS_HIDWORD32(dwData); // Старшие 32 бита (левый блок)
 DWORD32 dwR=HS_LODWORD32(dwData); // Младшие 32 бита (правый блок)
 return HS_MAKEDWORD64(dwR,dwL);   // Обмен блоков
}

/*DWORD32 hsFeistelNetwork(CONST LPDWORD64 dwData,DWORD32 (*K)(DWORD64 dwKey,BYTE bRound),DWORD32 (*F)(DWORD32 dwData,DWORD32 dwKey),DWORD64 dwKey,DWORD32 dwRounds,LPDWORD64 dwChipherText,HS_CIPHER_MODE hsMode)
{
 UINT64 C64;
 switch(hsMode)
 {
 case HS_ENCRYPTION_MODE:
  {
   C64=hsFeistel64(*dwData,K(dwKey,dwRounds),F);
   for(register __int32 i=dwRounds-1;i>=0;i--)
   { C64=hsFeistel64(C64,K(dwKey,i),F); }
  } break;
 case HS_DECRYPTION_MODE:
  {
   C64=hsFeistel64(*dwData,K(dwKey,0),F);
   for(register DWORD32 i=1;i<=dwRounds;i++)
   { C64=hsFeistel64(C64,K(dwKey,i),F); }
  } break;
 }
 C64=hsExchange(C64);
 *dwChipherText=C64;
 return 0;
}*/
#pragma endregion

#pragma region Block Cipher Modes of Operation
// Шифрование в режиме сцепления блоков шифротекста с распространением ошибки
// Propagating Cipher-Block Chaining (PCBC)
// Параметры:
// [in/out] lpPlaintext  - открытый текст
// [in]     dwSize       - длина открытого текста (в байтах)
// [in]     dwKey        - ключ (64 бита)
// [in]     dwIV         - вектор инициализации (InitializationVector)
// [in]     BC           - функция шифрования (Block Cipher)
// [in]     hsMode       - режим (шифрование, дешифрование)
// [in/out] lpCiphertext - зашифрованный текст
// Возвращаемое значение:
// Количество зашифрованных/расшифрованных блоков
// <Контроль качества>
// ! Если dwSize не кратно 8, последний блок открытого текста не шифруется
DWORD64 hsPCBC(LPDWORD64 lpPlaintext,DWORD64 dwSize,DWORD64 dwKey,DWORD64 dwIV,LPDWORD64 lpCiphertext,DWORD64 (*BC)(DWORD64 dwPlaintext,DWORD64 dwKey,HS_CIPHER_MODE hsMode),HS_CIPHER_MODE hsMode)
{
 DWORD64 dwBlocksCount=dwSize/8;
 switch(hsMode)
 {
 case HS_ENCRYPTION_MODE:
  {
   for(DWORD64 i=0;i<dwBlocksCount;i++)
   {
    lpCiphertext[i]=BC(lpPlaintext[i] XOR dwIV,dwKey,hsMode);
    dwIV=lpPlaintext[i] XOR lpCiphertext[i];
   }
  } break;
 case HS_DECRYPTION_MODE:
  {
   for(DWORD64 i=0;i<dwBlocksCount;i++)
   {
    lpPlaintext[i]=BC(lpCiphertext[i],dwKey,hsMode) XOR dwIV;
    dwIV=lpCiphertext[i] XOR lpPlaintext[i];
   }
  } break;
 default:
  { return HS_ERROR_UNKNOWN_MODE; }
 }
 return dwBlocksCount;
}

// Тройное шифрование
// Triple Data Encryption Algorithm (TDEA)
// Параметры:
// [in/out] lpPlaintext  - открытый текст
// [in]     dwSize       - длина открытого/зашифрованного текста (в байтах)
// [in]     dwKeyA       - ключ №1 (64 бита)
// [in]     dwKeyB       - ключ №2 (64 бита)
// [in]     dwKeyC       - ключ №3 (64 бита)
// [in]     BC           - функция шифрования (Block Cipher)
// [in]     hsMode       - режим (шифрование, дешифрование)
// [in/out] lpCiphertext - зашифрованный текст
// Возвращаемое значение:
// Количество зашифрованных/расшифрованных блоков
// <Контроль качества>
// ! Если dwSize не кратно 8, последний блок открытого текста не шифруется
DWORD64 hsTDEA(LPDWORD64 lpPlaintext,DWORD64 dwSize,DWORD64 dwKeyA,DWORD64 dwKeyB,DWORD64 dwKeyC,LPDWORD64 lpCiphertext,DWORD64 (*BC)(DWORD64 dwPlaintext,DWORD64 dwKey,HS_CIPHER_MODE hsMode),HS_CIPHER_MODE hsMode)
{
 DWORD64 dwBlocksCount=dwSize/8;
 switch(hsMode)
 {
 case HS_ENCRYPTION_MODE:
  {
   for(DWORD64 i=0;i<dwBlocksCount;i++)
   { lpCiphertext[i]=BC(BC(BC(lpPlaintext[i],dwKeyA,HS_ENCRYPTION_MODE),dwKeyB,HS_DECRYPTION_MODE),dwKeyC,HS_ENCRYPTION_MODE); }
  } break;
 case HS_DECRYPTION_MODE:
  {
   for(DWORD64 i=0;i<dwBlocksCount;i++)
   { lpPlaintext[i]=BC(BC(BC(lpCiphertext[i],dwKeyC,HS_DECRYPTION_MODE),dwKeyB,HS_ENCRYPTION_MODE),dwKeyA,HS_DECRYPTION_MODE); }
  } break;
 default:
  { return HS_ERROR_UNKNOWN_MODE; }
 }
 return dwBlocksCount;
}
#pragma endregion