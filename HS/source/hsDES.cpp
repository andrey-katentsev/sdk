#include "hsDES.h"
#include "hsBitwise.h"
#include "hsWin32Types.h"
#include "hsCrypt.h"

#pragma region DES
// ������� ��������� ������������
CONST BYTE DES_IP[64]={
 58,50,42,34,26,18,10,2,
 60,52,44,36,28,20,12,4,
 62,54,46,38,30,22,14,6,
 64,56,48,40,32,24,16,8,
 57,49,41,33,25,17,9,1,
 59,51,43,35,27,19,11,3,
 61,53,45,37,29,21,13,5,
 63,55,47,39,31,23,15,7};

// ������� �������� ������������
CONST BYTE DES_FP[64]={
 40,8,48,16,56,24,64,32,
 39,7,47,15,55,23,63,31,
 38,6,46,14,54,22,62,30,
 37,5,45,13,53,21,61,29,
 36,4,44,12,52,20,60,28,
 35,3,43,11,51,19,59,27,
 34,2,42,10,50,18,58,26,
 33,1,41,9,49,17,57,25};

// ������� ����������
CONST BYTE DES_E[48]={
 32,1,2,3,4,5,
 4,5,6,7,8,9,
 8,9,10,11,12,13,
 12,13,14,15,16,17,
 16,17,18,19,20,21,
 20,21,22,23,24,25,
 24,25,26,27,28,29,
 28,29,30,31,32,1};

// ������� ������ ������
CONST BYTE DES_S1[4][16]={
 14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7,
 0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8,
 4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0,
 15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13};

CONST BYTE DES_S2[4][16]={
 15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10,
 3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5,
 0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15,
 13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9};

CONST BYTE DES_S3[4][16]={
 10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8,
 13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1,
 13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7,
 1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12};

CONST BYTE DES_S4[4][16]={
 7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15,
 13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9,
 10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4,
 3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14};

CONST BYTE DES_S5[4][16]={
 2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9,
 14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6,
 4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14,
 11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3};

CONST BYTE DES_S6[4][16]={
 12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11,
 10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8,
 9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6,
 4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13};

CONST BYTE DES_S7[4][16]={
 4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1,
 13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6,
 1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2,
 6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12};

CONST BYTE DES_S8[4][16]={
 13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7,
 1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2,
 7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8,
 2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11};

// ������� ����� ������������
CONST BYTE DES_P[32]={
 16,7,20,21,29,12,28,17,
 1,15,23,26,5,18,31,10,
 2,8,24,14,32,27,3,9,
 19,13,30,6,22,11,4,25};

// ������� �������������� ���������� �����
CONST BYTE DES_PC1[56]={
 57,49,41,33,25,17,9,
 1,58,50,42,34,26,18,
 10,2,59,51,43,35,27,
 19,11,3,60,52,44,36,
 63,55,47,39,31,23,15,
 7,62,54,46,38,30,22,
 14,6,61,53,45,37,29,
 21,13,5,28,20,12,4};

// ������� ����������� ��������� �����
CONST BYTE DES_PC2[48]={
 14,17,11,24,1,5,3,28,
 15,6,21,10,23,19,12,4,
 26,8,16,7,27,20,13,2,
 41,52,31,37,47,55,30,40,
 51,45,33,48,44,49,39,56,
 34,53,46,42,50,36,29,32};

// ������� ������� ��� ������ �����
CONST BYTE DES_RC[16]={1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1};

// ��������� ������������ [Initial Permutation]
// 64-� ������ P-��������������
// ���������:
// [in] dwData - ���� ������
// ������������ ��������:
// ������������� ���� ������
// <�������� ��������>
DWORD64 hsIP(DWORD64 dwData)
{
 DWORD64 dwIP=0x0000000000000000;
 for(register BYTE i=0;i<64;i++)
 { dwIP=SET_DWORD64_BIT_VALUE(dwIP,i+1,GET_DWORD64_BIT(dwData,DES_IP[i])); }
 return dwIP;
}

// �������� ������������ [Final Permutation]
// 64-� ������ P-��������������
// ���������:
// [in] dwData - ���� ������
// ������������ ��������:
// ������������� ���� ������
// <�������� ��������>
DWORD64 hsFP(DWORD64 dwData)
{
 DWORD64 dwFP=0x0000000000000000;
 for(register BYTE i=0;i<64;i++)
 { dwFP=SET_DWORD64_BIT_VALUE(dwFP,i+1,GET_DWORD64_BIT(dwData,DES_FP[i])); }
 return dwFP;
}

// ���������� 32-� ������� ������������������ �� 48-�� ������� [Expansion]
// ���������:
// [in] dwData - ���� ������ (32 ����)
// ������������ ��������:
// ����������� ���� ������ (48 ���)
// <�������� ��������>
DWORD64 hsEDES(DWORD32 dwData)
{
 DWORD64 dwE=0x0000000000000000;
 for(register BYTE i=0;i<48;i++)
 { dwE=SET_DWORD64_BIT_VALUE(dwE,i+1,GET_DWORD32_BIT(dwData,DES_E[i])); }
 return dwE;
}

// ���� ������ (S) [Substitution]
// 6-�� ������ S-��������������
// ���������:
// [in] bData - ���� ������ (6 ���)
// [in] nS    - ����� ������� �������������� [1,8]
// ������������ ��������:
// ������������� ���� ������ (4 ����)
// <�������� ��������>
// ! �� �������������� ����� �� ��������� [1,8]
BYTE hsSDES(BYTE bData,BYTE nS)
{
 BYTE bS=0x00;
 BYTE i=((bData AND 0x21) >> 4) OR (bData AND 0x01); // 0x20: 1-� ��� (3 �� 8), 0x01: 6-� ��� (8 �� 8);
 BYTE j=(bData AND 0x1E) >> 1;                       // 0x1E: ���� 2,3,4,5 (4,5,6,7 �� 8)
 CONST BYTE *S[8]={&DES_S1[0][0],&DES_S2[0][0],&DES_S3[0][0],&DES_S4[0][0],&DES_S5[0][0],&DES_S6[0][0],&DES_S7[0][0],&DES_S8[0][0]};
 bS=*(S[nS-1]+i*16+j);
 //bS=*(*(S[0]+i)+j);
 return bS;
}

// ���� ������������ (P) [Permutation]
// 32-� ������ P-��������������
// ���������:
// [in] dwData - ���� ������ (32 ����)
// ������������ ��������:
// ������������� ���� ������ (32 ����)
// <�������� ��������>
DWORD32 hsPDES(DWORD32 dwData)
{
 DWORD32 dwP=0x00000000;
 for(register BYTE i=0;i<32;i++)
 { dwP=SET_DWORD32_BIT_VALUE(dwP,i+1,GET_DWORD32_BIT(dwData,DES_P[i])); }
 return dwP;
}
// �������������� ���������� ����� (G) [Permuted Choice 1]
// 64-� ������ P-��������������
// ���������:
// [in] dwKey - ���� (64 ����)
// ������������ ��������:
// ������������� ���� ������: (56 ���)
// - �������� ����������� ����� 8,16,24,32,40,48,56,64
// - ������������
// - ���������: ������� 56 ��� (������� 8 ��� ����� �������� 0)
// <�������� ��������>
DWORD64 hsPC1(DWORD64 dwKey)
{
 DWORD64 dwPC1=0x0000000000000000;
 for(register BYTE i=0;i<56;i++)
 { dwPC1=SET_DWORD64_BIT_VALUE(dwPC1,i+1,GET_DWORD64_BIT(dwKey,DES_PC1[i])); }
 return dwPC1;
}

// ����������� ��������� ����� (H) [Permuted Choice 2]
// 56-�� ������ P-��������������
// ���������:
// [in] dwKey - ���� (������� 56 ���)
// ������������ ��������:
// ������������� ���� ������: (48 ���)
// - �������� ����� 9,18,22,25,35,38,43,54
// - ������������
// - ���������: ������� 48 ��� (������� 16 ��� ����� �������� 0)
// <�������� ��������>
DWORD64 hsPC2(DWORD64 dwKey)
{
 DWORD64 dwPC2=0x0000000000000000;
 for(register BYTE i=0;i<48;i++)
 { dwPC2=SET_DWORD64_BIT_VALUE(dwPC2,i+1,GET_DWORD64_BIT(dwKey,DES_PC2[i])); }
 return dwPC2;
}

// ������� ����� (�,D) [Round Choice]
// ���������:
// [in] dwKey  - ���� (������� 56 ���)
// [in] nRound - ����� ������ [1,16]
// ������������ ��������:
// ����: (������� 56 ���)
// <�������� ��������>
// ! �� �������������� ����� �� ��������� [1,16]
DWORD64 hsRC(DWORD64 dwKey,BYTE nRound)
{
 DWORD64 dwRC=0x0000000000000000;
 DWORD32 dwC=(DWORD32)((dwKey >> 28) AND 0x000000000FFFFFFF);
 DWORD32 dwD=(DWORD32)(dwKey AND 0x000000000FFFFFFF);
 for(register BYTE i=0;i<DES_RC[nRound-1];i++)
 {
  dwC<<=1;
  dwD<<=1;
  dwC=SET_DWORD32_BIT_VALUE(dwC,1,GET_DWORD32_BIT(dwC,29));
  dwD=SET_DWORD32_BIT_VALUE(dwD,1,GET_DWORD32_BIT(dwD,29));
  dwC&=0x0FFFFFFF;
  dwD&=0x0FFFFFFF;
 }
 dwRC=(DWORD64)dwC<<28;
 dwRC|=(DWORD64)dwD;
 return dwRC;
}

// ��������� ����� [Key Schedule]
// ���������:
// [in] dwKey  - ���� (64 ����)
// [in] nRound - ����� ������ [1,16]
// ������������ ��������:
// ����: (������� 48 ���)
// <�������� ��������>
DWORD64 hsKDES(DWORD64 dwKey,BYTE nRound)
{
 DWORD64 dwKS=0x0000000000000000;
 dwKS=hsPC1(dwKey);      // �������������� ���������� ����� (G) [Permuted Choice 1]
 dwKS=hsRC(dwKS,nRound); // ������� ����� (�,D) [Round Choice]
 dwKS=hsPC2(dwKS);       // ����������� ��������� ����� (H) [Permuted Choice 2]
 return dwKS;
}

// ������� ���������� (F) [The Feistel Function]
// ���������:
// [in] dwData - ���� ������ (32 ����)
// [in] dwKey  - ���� (48 ���)
// ������������ ��������:
// ������������� ���� ������ (32 ����)
// <�������� ��������>
DWORD32 hsFDES(DWORD32 dwData,DWORD64 dwKey)
{
 DWORD64 dwE=0x0000000000000000;
 DWORD32 dwF=0x00000000;
 BYTE bS=0x00;
 dwE=hsEDES(dwData);            // ���������� 32-� ������� ������������������ �� 48-�� ������� [Expansion]
 dwE^=dwKey;                    // �������� � ������ �� ������ 2 [Key Mixing]
 for(register BYTE i=0;i<8;i++) // ���� ������ (S) [Substitution]
 {
  bS=(BYTE)((dwE >> i*6) AND 0x000000000000003F); // �������� 6-���
  bS=hsSDES(bS,8-i);                              // S-��������������
  dwF|=((DWORD32)bS << 4*i);                      // ��������� ���������� 4-� ������� ����� �� ����� ������
 }
 dwF=hsPDES(dwF);               // ���� ������������ (P) [Permutation]
 return dwF;
}

// 64-� ������ �������������� ��������
// ���������:
// [in] dwData - ���� ������ (64 ����)
// [in] dwKey  - ���� (64 ����)
// [in] F      - ���������� �������
// ������������ ��������:
// ������������� ���� ������ (64 ����)
// <�������� ��������>
DWORD64 hsFeistelDES(DWORD64 dwData,DWORD64 dwKey,DWORD32 (*F)(DWORD32 dwData,DWORD64 dwKey))
{
 DWORD32 dwL=HS_HIDWORD32(dwData); // ����� ����
 DWORD32 dwR=HS_LODWORD32(dwData); // ������ ����
 DWORD32 dwF=F(dwR,dwKey);         // ��������� �������� ������������� �������
 dwL^=dwF;                         // ���������� �������� ��������� ������� � ������ ������ ������ �� ������ 2
 return HS_MAKEDWORD64(dwR,dwL);   // ����� ������
}

// ���� ��������
// ���������:
// [in] dwData   - ���� ������ (64 ����)
// [in] dwKey    - ���� (64 ����)
// [in] dwRounds - ����� ������� (������ �������������� ��������)
// [in] F        - ���������� �������
// [in] K        - ������� ������� �����
// [in] hsMode   - ����� [����������,������������]
// ������������ ��������:
// ������������� ���� ������ (64 ����)
// <�������� ��������>
DWORD64 hsFeistelNetworkDES(CONST DWORD64 dwData,DWORD64 dwKey,DWORD32 dwRounds,DWORD32 (*F)(DWORD32 dwData,DWORD64 dwKey),DWORD64 (*K)(DWORD64 dwKey,BYTE nRound),HS_CIPHER_MODE hsMode)
{
 DWORD64 dwFN=0x0000000000000000;
 switch(hsMode)
 {
 case HS_ENCRYPTION_MODE:
  {
   //dwFN=hsFeistelDES(dwData,K(dwKey,0),F);
   dwFN=hsFeistelDES(dwData,K(dwKey,1),F);
   //for(register DWORD32 i=1;i<=dwRounds;i++)
   for(register DWORD32 i=2;i<=dwRounds;i++)
   { dwFN=hsFeistelDES(dwFN,K(dwKey,i),F); }
  } break;
 case HS_DECRYPTION_MODE:
  {
   dwFN=hsFeistelDES(dwData,K(dwKey,dwRounds),F);
   //for(register INT32 i=dwRounds-1;i>=0;i--)
   for(register INT32 i=dwRounds-1;i>=1;i--)
   { dwFN=hsFeistelDES(dwFN,K(dwKey,i),F); }
  } break;
 }
 dwFN=hsExchange(dwFN);
 return dwFN;
}

// �������� ���������� DES
// Data Encryption Standard (DES)
// ���������:
// [in] dwData   - ���� ������ (64 ����)
// [in] dwKey    - ���� (64 ����)
// [in] hsMode   - ����� [����������,������������]
// ������������ ��������:
// ������������� ���� ������ (64 ����)
// <�������� ��������>
DWORD64 hsDES(DWORD64 dwData,DWORD64 dwKey,HS_CIPHER_MODE hsMode)
{
 DWORD64 dwDES=0x0000000000000000;
 dwDES=hsIP(dwData);                                             // ��������� ������������ [Initial Permutation]
 dwDES=hsFeistelNetworkDES(dwDES,dwKey,16,hsFDES,hsKDES,hsMode); // 16 ������ �������������� ��������
 dwDES=hsFP(dwDES);                                              // �������� ������������ [Final Permutation]
 return dwDES;
}

// ���������� � ������� ��������� DES.
// ���������:
// [in] dwData - ���� ������ (64 ����).
// [in] dwKey  - ���� (64 ����).
// ������������ ��������:
// ������������� ���� ������ (64 ����).
// <�������� ��������>
DWORD64 hsDESEncrypt(DWORD64 Data,DWORD64 Key)
{
 DWORD64 dwDES=0x0000000000000000;
 dwDES=hsIP(Data);                                                         // ��������� ������������ [Initial Permutation]
 dwDES=hsFeistelNetworkDES(dwDES,Key,16,hsFDES,hsKDES,HS_ENCRYPTION_MODE); // 16 ������ �������������� ��������
 dwDES=hsFP(dwDES);                                                        // �������� ������������ [Final Permutation]
 return dwDES;
}

// ������������ � ������� ��������� DES.
// ���������:
// [in] dwData - ���� ������������� ������ (64 ����).
// [in] dwKey  - ���� (64 ����).
// ������������ ��������:
// �������������� ���� ������ (64 ����).
// <�������� ��������>
DWORD64 hsDESDecrypt(DWORD64 Data,DWORD64 Key)
{
 DWORD64 dwDES=0x0000000000000000;
 dwDES=hsIP(Data);                                                         // ��������� ������������ [Initial Permutation]
 dwDES=hsFeistelNetworkDES(dwDES,Key,16,hsFDES,hsKDES,HS_DECRYPTION_MODE); // 16 ������ �������������� ��������
 dwDES=hsFP(dwDES);                                                        // �������� ������������ [Final Permutation]
 return dwDES;
}

DWORD64 hsEncryptFileDES(LPCTSTR lpSrcFileName,LPCTSTR lpDstFileName,DWORD64 dwKey,HS_CIPHER_MODE hsMode)
{
 DWORD dwFileSize,dwBytesRead,dwBytesWritten,dwBlock;
 BYTE *pFileData,*pEncryptedData;
 DWORD64* pData64;

 HANDLE hFileA=CreateFile(lpSrcFileName,GENERIC_READ,0,NULL,OPEN_EXISTING,0,NULL);
 if(hFileA==INVALID_HANDLE_VALUE)
 { return 0; }

 HANDLE hFileB=CreateFile(lpDstFileName,GENERIC_WRITE,0,NULL,CREATE_ALWAYS,0,NULL);
 if(hFileB==INVALID_HANDLE_VALUE)
 { return 0; }

 dwFileSize=GetFileSize(hFileA,NULL);

 pFileData=(PBYTE)malloc(dwFileSize);
 if(pFileData==NULL)
 { return 0; }

 pEncryptedData=(PBYTE)malloc(dwFileSize);
 if(pEncryptedData==NULL)
 { return 0; }

 ReadFile(hFileA,pFileData,dwFileSize,&dwBytesRead,NULL);

 CopyMemory(pEncryptedData,pFileData,dwFileSize);

 pData64=(DWORD64*)pFileData;
 dwBlock=dwFileSize/8;

 for(DWORD i=0;i<dwBlock;i++)
 { ((DWORD64*)pEncryptedData)[i]=hsDES(pData64[i],dwKey,hsMode); }

 WriteFile(hFileB,pEncryptedData,dwFileSize,&dwBytesWritten,NULL);

 free(pFileData);
 free(pEncryptedData);
 CloseHandle(hFileB);
 CloseHandle(hFileA);
 return 0;
}
#pragma endregion