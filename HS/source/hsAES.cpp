#pragma region Advanced Encryption Standard (AES)
/*
 STATE BOX:
 {(0,0),(0,1),(0,2),(0,3)}
 {(1,0),(1,1),(1,2),(1,3)}
 {(2,0),(2,1),(2,2),(2,3)}
 {(3,0),(3,1),(3,2),(3,3)}

 INPUT ORDER: {(0,0),(1,0),(2,0),(3,0),(0,1),(1,1),(2,1),(3,1),(0,2),(1,2),(2,2),(3,2),(0,3),(1,3),(2,3),(3,3)}
*/

CONST BYTE S_BOX_AES[256]={
//0     1    2      3     4    5     6     7      8    9     A      B    C     D     E     F
0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76, //0
0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0, //1
0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15, //2
0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75, //3
0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84, //4
0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf, //5
0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8, //6
0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2, //7
0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73, //8
0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb, //9
0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79, //A
0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08, //B
0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a, //C
0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e, //D
0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf, //E
0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16};//F

CONST BYTE IS_BOX_AES[256]={
 0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb,
 0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87, 0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb,
 0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e,
 0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25,
 0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92,
 0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84,
 0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06,
 0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02, 0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b,
 0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73,
 0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e,
 0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89, 0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b,
 0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4,
 0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f,
 0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d, 0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef,
 0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61,
 0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d};

CONST BYTE RCON_AES[255]={
 0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8,
 0xab, 0x4d, 0x9a, 0x2f, 0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3,
 0x7d, 0xfa, 0xef, 0xc5, 0x91, 0x39, 0x72, 0xe4, 0xd3, 0xbd, 0x61, 0xc2, 0x9f,
 0x25, 0x4a, 0x94, 0x33, 0x66, 0xcc, 0x83, 0x1d, 0x3a, 0x74, 0xe8, 0xcb, 0x8d,
 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8, 0xab,
 0x4d, 0x9a, 0x2f, 0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3, 0x7d,
 0xfa, 0xef, 0xc5, 0x91, 0x39, 0x72, 0xe4, 0xd3, 0xbd, 0x61, 0xc2, 0x9f, 0x25,
 0x4a, 0x94, 0x33, 0x66, 0xcc, 0x83, 0x1d, 0x3a, 0x74, 0xe8, 0xcb, 0x8d, 0x01,
 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8, 0xab, 0x4d,
 0x9a, 0x2f, 0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3, 0x7d, 0xfa,
 0xef, 0xc5, 0x91, 0x39, 0x72, 0xe4, 0xd3, 0xbd, 0x61, 0xc2, 0x9f, 0x25, 0x4a,
 0x94, 0x33, 0x66, 0xcc, 0x83, 0x1d, 0x3a, 0x74, 0xe8, 0xcb, 0x8d, 0x01, 0x02,
 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8, 0xab, 0x4d, 0x9a,
 0x2f, 0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3, 0x7d, 0xfa, 0xef,
 0xc5, 0x91, 0x39, 0x72, 0xe4, 0xd3, 0xbd, 0x61, 0xc2, 0x9f, 0x25, 0x4a, 0x94,
 0x33, 0x66, 0xcc, 0x83, 0x1d, 0x3a, 0x74, 0xe8, 0xcb, 0x8d, 0x01, 0x02, 0x04,
 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8, 0xab, 0x4d, 0x9a, 0x2f,
 0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3, 0x7d, 0xfa, 0xef, 0xc5,
 0x91, 0x39, 0x72, 0xe4, 0xd3, 0xbd, 0x61, 0xc2, 0x9f, 0x25, 0x4a, 0x94, 0x33,
 0x66, 0xcc, 0x83, 0x1d, 0x3a, 0x74, 0xe8, 0xcb};

/*CONST BYTE GFM[4][4]={
 {0x02, 0x01, 0x01, 0x03},
 {0x03, 0x02, 0x01, 0x01},
 {0x01, 0x03, 0x02, 0x01},
 {0x01, 0x01, 0x03, 0x02}};*/

/*
 02 03 01 01
 01 02 03 01
 01 01 02 03
 03 01 01 02
*/

CONST BYTE GFM[4][4]={
 {0x02, 0x03, 0x01, 0x01},
 {0x01, 0x02, 0x03, 0x01},
 {0x01, 0x01, 0x02, 0x03},
 {0x03, 0x01, 0x01, 0x02}};

/*CONST BYTE IGFM[4][4]={
 {0x0e, 0x09, 0x0d, 0x0b},
 {0x0b, 0x0e, 0x09, 0x0d},
 {0x0d, 0x0b, 0x0e, 0x09},
 {0x09, 0x0d, 0x0b, 0x0e}};*/

/*
 14 11 13 09
 09 14 11 13
 13 09 14 11
 11 13 09 14
*/

CONST BYTE IGFM[4][4]={
 {0x0e, 0x0b, 0x0d, 0x09},
 {0x09, 0x0e, 0x0b, 0x0d},
 {0x0d, 0x09, 0x0e, 0x0b},
 {0x0b, 0x0d, 0x09, 0x0e}};

CONST BYTE RCON_AES_128[4][10]={
 {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36},
 {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
 {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
 {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}};

// <Контроль качества>
VOID hsAddRoundKeyAES(LPBYTE lpState,LPBYTE lpRoundKey)
{
 for(register BYTE i=0;i<16;i++)
 { lpState[i]^=lpRoundKey[i]; }
}

// Substitute all the values from the state with the value in the SBox using the state value as index for the SBox
// <Контроль качества>
VOID hsSubBytesAES(LPBYTE lpState)
{
 for(register BYTE i=0;i<16;i++)
 { lpState[i]=S_BOX_AES[lpState[i]]; }
}

// <Контроль качества>
VOID hsShiftRowAES(LPBYTE lpState,BYTE nBytesToRotate)
{
 BYTE Temp;
 /* Each iteration shifts the row to the left by 1 byte */
 for(register BYTE i=0;i<nBytesToRotate;i++)
 {
  Temp=lpState[0];
  for(register BYTE j=0;j<3;j++)
  { lpState[j]=lpState[j+1]; }
  lpState[3]=Temp;
 }
}

// <Контроль качества>
VOID hsShiftRowsAES(LPBYTE lpState)
{
 /* Iterate over the 4 rows and call hsShiftRowAES() with that row */
 for (register BYTE i=0;i<4;i++)
 { hsShiftRowAES(&lpState[i*4],i); }
}

// GFM x Column = MixColumn
// <Контроль качества>
VOID hsMixColumnAES(LPBYTE lpColumn)
{
 BYTE Temp[4];
	CopyMemory(Temp,lpColumn,4);
 SecureZeroMemory(lpColumn,4);
 for(register BYTE i=0;i<4;i++)
 {
  for(register BYTE j=0;j<4;j++)
  { lpColumn[i]^=hsGaloisMultiplication(GFM[i][j],Temp[j]); }
 }
 SecureZeroMemory(Temp,4);
}

// <Контроль качества>
VOID hsMixColumnsAES(LPBYTE lpState)
{
 BYTE Temp[4];

 /* Iterate over the 4 columns */
 for(register BYTE i=0;i<4;i++)
 {
  /* Construct one column by iterating over the 4 rows */
  for(register BYTE j=0;j<4;j++)
  { Temp[j]=lpState[(j*4)+i]; }

  /* Apply the hsMixColumnAES on one column */
  hsMixColumnAES(Temp);

  /* Put the values back into the state */
  for(register BYTE j=0;j<4;j++)
  { lpState[(j*4)+i]=Temp[j]; }
 }
}

/*
 * Rijndael's key schedule rotate operation
 * rotate the word eight bits to the left
 * word is an char array of size 4 (32 bit)
 */
// hsRotateWordAES(0x01,0x02,0x03,0x04) -> {0x02,0x03,0x04,0x01}
// <Контроль качества>
VOID hsRotateWordAES(LPBYTE lpWord)
{
 BYTE Temp=lpWord[0];
 lpWord[0]=lpWord[1];
 lpWord[1]=lpWord[2];
 lpWord[2]=lpWord[3];
 lpWord[3]=Temp;
}

// <Контроль качества>
VOID hsKeySchedureCoreAES(LPBYTE lpWord,BYTE nRound)
{
 /* Rotate the 32-bit word 8 bits to the left */
 hsRotateWordAES(lpWord);

 /* Apply S-Box substitution on all 4 parts of the 32-bit word */
 for(register BYTE i=0;i<4;++i)
 { lpWord[i]=S_BOX_AES[lpWord[i]]; }

 /* XOR the output of the Rcon operation with i to the first part (leftmost) only */
 lpWord[0]=lpWord[0] XOR RCON_AES[nRound];
}

// <Контроль качества>
LPBYTE* hsKeyScheduleAES128(LPBYTE lpCipherKey)
{
 BYTE TempKey[16],Temp[4];
 BYTE Round;
 LPBYTE *lpRoundKey;

 lpRoundKey=(LPBYTE*)new LPBYTE[10];
 for(register BYTE i=0;i<10;i++)
 { lpRoundKey[i]=(LPBYTE)new BYTE[16]; }

 CopyMemory(TempKey,lpCipherKey,16*sizeof(BYTE));
 CopyMemory(Temp,&TempKey[12],4*sizeof(BYTE));

 for(Round=0;Round<10;Round++)
 {
  hsRotateWordAES(Temp);
  for(register BYTE i=0;i<4;i++)
  { Temp[i]=S_BOX_AES[Temp[i]]; }

  for(register BYTE i=0;i<4;i++)
  { lpRoundKey[Round][i]=TempKey[i] XOR Temp[i] XOR RCON_AES_128[i][Round]; }

  for(register BYTE i=4;i<16;i++)
  { lpRoundKey[Round][i]=TempKey[i] XOR lpRoundKey[Round][i-4]; }

  SecureZeroMemory(TempKey,16*sizeof(BYTE));
  SecureZeroMemory(Temp,4*sizeof(BYTE));
  CopyMemory(TempKey,lpRoundKey[Round],16*sizeof(BYTE));
  CopyMemory(Temp,&TempKey[12],4*sizeof(BYTE));
 }
 SecureZeroMemory(TempKey,16*sizeof(BYTE));
 SecureZeroMemory(Temp,4*sizeof(BYTE));
 return lpRoundKey;
}

/* Rijndael's key expansion
 * expands an 128,192,256 key into an 176,208,240 bytes key.
 * expandedKey is a pointer to an char array of large enough size
 * key is a pointer to a non-expanded key.
 */
VOID hsExpandKeyAES(LPBYTE lpExpandedKey,LPBYTE lpCipherKey,HS_AES_KEY_SIZE hsKeySize,BYTE nExpandedKeySize)
{
 /* current expanded HS_AES_KEY_SIZE, in bytes */
 BYTE nCurrentSize=0;
 BYTE nRound=1;
 BYTE Temp[4];

 ZeroMemory(Temp,4);

 /* Set the 16,24,32 bytes of the expanded key to the input key */
 for (register BYTE i=0;i<hsKeySize;i++)
 { lpExpandedKey[i]=lpCipherKey[i]; }
 nCurrentSize += hsKeySize;

 while(nCurrentSize<nExpandedKeySize)
 {
  /* Assign the previous 4 bytes to the temporary value t */
  for (register BYTE i=0;i<4;i++)
  { Temp[i]=lpExpandedKey[(nCurrentSize-4)+i]; }

  /* Every 16,24,32 bytes we apply the core schedule to t
  * and increment rconIteration afterwards
  */
  if(nCurrentSize%hsKeySize==0)
  { hsKeySchedureCoreAES(Temp,nRound++); }

  /* For 256-bit keys, we add an extra sbox to the calculation */
  if(nExpandedKeySize==HS_AES_256_BIT && ((nCurrentSize%hsKeySize)==16))
  {
   for(register BYTE i=0;i<4;i++)
   { Temp[i] = S_BOX_AES[Temp[i]]; }
  }

  /* We XOR t with the four-byte block 16,24,32 bytes before the new expanded key.
  * This becomes the next four bytes in the expanded key.
  */
  for(register BYTE i=0;i<4;i++)
  {
   lpExpandedKey[nCurrentSize]=lpExpandedKey[nCurrentSize-hsKeySize] XOR Temp[i];
   nCurrentSize++;
  }
 }
}

VOID hsGetRoundKeyAES(LPBYTE lpExpandedKey,LPBYTE lpRoundKey)
{
 /* Iterate over the columns */
 for(register BYTE i=0;i<4;i++)
 {
  /* Iterate over the rows */
  for(register BYTE j=0;j<4;j++)
  { lpRoundKey[(i+(j*4))]=lpExpandedKey[(i*4)+j]; }
 }
}

VOID hsMainAES(LPBYTE lpState,LPBYTE lpExpandedKey,BYTE nRounds)
{
 BYTE RoundKey[16];

 hsGetRoundKeyAES(lpExpandedKey,RoundKey);
 hsAddRoundKeyAES(lpState,RoundKey);
 for(register BYTE i=1;i<nRounds;i++)
 {
  hsGetRoundKeyAES(&lpExpandedKey[16*i],RoundKey);
  hsSubBytesAES(lpState);
  hsShiftRowsAES(lpState);
  hsMixColumnsAES(lpState);
  hsAddRoundKeyAES(lpState,RoundKey);
 }
 hsGetRoundKeyAES(&lpExpandedKey[16*nRounds],RoundKey);
 hsSubBytesAES(lpState);
 hsShiftRowsAES(lpState);
 hsAddRoundKeyAES(lpState,RoundKey);
}

DWORD32 hsEncryptionAES(LPBYTE lpState,LPBYTE lpCipherText,LPBYTE lpCipherKey,HS_AES_KEY_SIZE hsKeySize)
{
 BYTE Buffer[16];       // The 128 bit block to encode
 BYTE nExpandedKeySize; // The expanded key size
 BYTE nRounds;          // The number of rounds
 LPBYTE lpExpandedKey;  // The expanded key

 /* Set the number of rounds */
 switch (hsKeySize)
 {
 case HS_AES_128_BIT:
  { nRounds=10; } break;
 case HS_AES_192_BIT:
  { nRounds=12; } break;
 case HS_AES_256_BIT:
  { nRounds=14; } break;
 default:
  { return HS_AES_UNKNOWN_KEY_SIZE; }
 }

 nExpandedKeySize=(16*(nRounds+1));

 lpExpandedKey=(LPBYTE)malloc(nExpandedKeySize*sizeof(BYTE));
 if(lpExpandedKey==NULL)
 { return HS_ERROR_UNABLE_TO_ALLOCATE_MEMORY; }

 /* Set the block values, for the block:
 * a0,0 a0,1 a0,2 a0,3
 * a1,0 a1,1 a1,2 a1,3
 * a2,0 a2,1 a2,2 a2,3
 * a3,0 a3,1 a3,2 a3,3
 * the mapping order is a0,0 a1,0 a2,0 a3,0 a0,1 a1,1 ... a2,3 a3,3
 */

 /* iterate over the columns */
 for(register BYTE i=0;i<4;i++)
 {
  /* iterate over the rows */
  for(register BYTE j=0;j<4;j++)
  { Buffer[i+(j*4)]=lpState[(i*4)+j]; }
 }

 hsExpandKeyAES(lpExpandedKey,lpCipherKey,hsKeySize,nExpandedKeySize); /* expand the key into an 176, 208, 240 bytes key */
 hsMainAES(Buffer,lpExpandedKey,nRounds); /* encrypt the block using the expandedKey */

 /* Unmap the block again into the output */
 for(register BYTE i=0;i<4;i++)
 {
  /* iterate over the rows */
  for(register BYTE j=0;j<4;j++)
  { lpCipherText[(i*4)+j]=Buffer[i+(j*4)]; }
 }

 free(lpExpandedKey);
 return 0;
}

// Substitute all the values from the state with the value in the SBox using the state value as index for the SBox
// <Контроль качества>
VOID hsISubBytesAES(LPBYTE lpState)
{
 for(register BYTE i=0;i<16;i++)
 { lpState[i]=IS_BOX_AES[lpState[i]]; }
}

VOID hsIShiftRowAES(LPBYTE lpState,BYTE nBytesToRotate)
{
 BYTE Temp;
 /* Each iteration shifts the row to the right by 1 */
 for(register BYTE i=0;i<nBytesToRotate;i++)
 {
  Temp=lpState[3];
  for(register INT8 j=3;j>0;j--)
  { lpState[j]=lpState[j-1]; }
  lpState[0]=Temp;
 }
}

// <Контроль качества>
VOID hsIShiftRowsAES(LPBYTE lpState)
{
 /* Iterate over the 4 rows and call invShiftRow() with that row */
 for(register BYTE i=0;i<4;i++)
 { hsIShiftRowAES(&lpState[i*4],i); }
}

// IGFM x Column = MixColumn
// <Контроль качества>
VOID hsIMixColumnAES(LPBYTE lpColumn)
{
 BYTE Temp[4];
 CopyMemory(Temp,lpColumn,4);
 SecureZeroMemory(lpColumn,4);
 for(register BYTE i=0;i<4;i++)
 {
  for(register BYTE j=0;j<4;j++)
  { lpColumn[i]^=hsGaloisMultiplication(IGFM[i][j],Temp[j]); }
 }
 SecureZeroMemory(Temp,4);
}

// <Контроль качества>
VOID hsIMixColumnsAES(LPBYTE lpState)
{
 BYTE Temp[4];

 /* Iterate over the 4 columns */
 for(register BYTE i=0;i<4;i++)
 {
  /* Construct one column by iterating over the 4 rows */
  for(register BYTE j=0;j<4;j++)
  { Temp[j]=lpState[(j*4)+i]; }

  /* Apply the invMixColumn on one column */
  hsIMixColumnAES(Temp);

  /* Put the values back into the state */
  for(register BYTE j=0;j<4;j++)
  { lpState[(j*4)+i]=Temp[j]; }
 }
}

VOID hsIMainAES(LPBYTE lpState,LPBYTE lpExpandedKey,BYTE nRounds)
{
 BYTE RoundKey[16];
 hsGetRoundKeyAES(lpExpandedKey+16*nRounds,RoundKey);
 hsAddRoundKeyAES(lpState,RoundKey);
 hsIShiftRowsAES(lpState);
 hsISubBytesAES(lpState);
 for(register INT8 i=nRounds-1;i>0;i--)
 {
  hsGetRoundKeyAES(lpExpandedKey+16*i,RoundKey);
  hsAddRoundKeyAES(lpState,RoundKey);
  hsIMixColumnsAES(lpState);
  hsIShiftRowsAES(lpState);
  hsISubBytesAES(lpState);
 }
 hsGetRoundKeyAES(lpExpandedKey,RoundKey);
 hsAddRoundKeyAES(lpState,RoundKey);
}

DWORD32 hsDecryptionAES(LPBYTE lpCipherText,LPBYTE lpState,LPBYTE lpCipherKey,HS_AES_KEY_SIZE hsKeySize)
{
 BYTE Buffer[16];       // 128-ми битный блок для декодирования
 BYTE nExpandedKeySize; // Длина расширенного ключа
 BYTE nRounds;          // Число раундов
 LPBYTE lpExpandedKey;  // Расширенный ключ

 /* Устанавливаем число раундов */
 switch (hsKeySize)
 {
 case HS_AES_128_BIT:
  { nRounds=10; } break;
 case HS_AES_192_BIT:
  { nRounds=12; } break;
 case HS_AES_256_BIT:
  { nRounds=14; } break;
 default:
  { return HS_AES_UNKNOWN_KEY_SIZE; }
 }

 nExpandedKeySize=(16*(nRounds+1)); // Определяем длину расширенного ключа

 lpExpandedKey=(LPBYTE)malloc(nExpandedKeySize*sizeof(BYTE));
 if(lpExpandedKey==NULL)
 { return HS_ERROR_UNABLE_TO_ALLOCATE_MEMORY; }

 /* Set the block values, for the block:
 * a0,0 a0,1 a0,2 a0,3
 * a1,0 a1,1 a1,2 a1,3
 * a2,0 a2,1 a2,2 a2,3
 * a3,0 a3,1 a3,2 a3,3
 * the mapping order is a0,0 a1,0 a2,0 a3,0 a0,1 a1,1 ... a2,3 a3,3
 */

 /* Iterate over the columns */
 for(register BYTE i=0;i<4;i++)
 {
  /* Iterate over the rows */
  for(register BYTE j=0;j<4;j++)
  { Buffer[(i+(j*4))]=lpCipherText[(i*4)+j]; }
 }
 
 hsExpandKeyAES(lpExpandedKey,lpCipherKey,hsKeySize,nExpandedKeySize); /* expand the key into an 176, 208, 240 bytes key */
 hsIMainAES(Buffer,lpExpandedKey,nRounds); /* decrypt the block using the expandedKey */

 /* Unmap the block again into the output */
 for(register BYTE i=0;i<4;i++)
 {
  /* Iterate over the rows */
  for (register BYTE j=0;j<4;j++)
  { lpState[(i*4)+j]=Buffer[(i+(j*4))]; }
 }

 free(lpExpandedKey);
 return 0;
}

// Шифрование с помощью алгоритма AES
// Advanced Encryption Standard (AES)
// Параметры:
// [in/out] lpState      - блок данных (128 бит)
// [in] lpCipherKey      - ключ (128/192/256 бит)
// [out/in] lpCipherText - зашифрованный блок данных (128 бит)
// [in] hsKeySize        - размер ключа (128/192/256 бит)
// [in] hsMode           - режим работы (шифрование/дешифрование)
// Возвращаемое значение: Нет
// <Контроль качества>
VOID hsAES(LPBYTE lpState,LPBYTE lpCipherKey,LPBYTE lpCipherText,HS_AES_KEY_SIZE hsKeySize,HS_CIPHER_MODE hsMode)
{
 switch(hsMode)
 {
 case HS_ENCRYPTION_MODE:
  { hsEncryptionAES(lpState,lpCipherText,lpCipherKey,hsKeySize); } break;
 case HS_DECRYPTION_MODE:
  { hsDecryptionAES(lpCipherText,lpState,lpCipherKey,hsKeySize); } break;
 }
}
#pragma endregion