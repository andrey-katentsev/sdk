#pragma region ���� 28147-89
// ������� ������� ������
CONST BYTE GOST_K[32]={1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8,8,7,6,5,4,3,2,1};

// ������� ������ ������
CONST BYTE GOST_S1[16]={4,10,9,2,13,8,0,14,6,11,1,12,7,15,5,3};
CONST BYTE GOST_S2[16]={14,11,4,12,6,13,15,10,2,3,8,1,0,7,5,9};
CONST BYTE GOST_S3[16]={5,8,1,13,10,3,4,2,14,15,12,7,6,0,9,11};
CONST BYTE GOST_S4[16]={7,13,10,1,0,8,9,15,14,4,6,12,11,2,5,3};
CONST BYTE GOST_S5[16]={6,12,7,1,5,15,13,8,4,10,9,14,0,3,11,2};
CONST BYTE GOST_S6[16]={4,11,10,0,7,2,1,13,3,6,8,5,9,12,15,14};
CONST BYTE GOST_S7[16]={13,11,4,1,3,15,5,9,0,10,14,7,6,8,2,12};
CONST BYTE GOST_S8[16]={1,15,13,0,5,7,10,4,9,2,3,14,6,11,8,12};

// ������������� ����� [Key Schedule]
// ���������:
// [in] dwKey[8] - ���� (256 ���)
// [in] nRound   - ����� ������ [1,32]
// ������������ ��������:
// ����: (32 ����)
// <�������� ��������>
// �� �������������� ����� �� �������� [1,32]
DWORD32 hsKGOST(DWORD32 dwKey[8],BYTE nRound)
{ return dwKey[GOST_K[nRound-1]-1]; }

// ���� ������ (S) [Substitution]
// 4-� ������ S-��������������
// ���������:
// [in] bData - ���� ������ (4 ���)
// [in] nS    - ����� ������� �������������� [1,8]
// ������������ ��������:
// ������������� ���� ������ (4 ����)
// <�������� ��������>
// ! �� �������������� ����� �� ��������� [1,8]
BYTE hsSGOST(BYTE bData,BYTE nS)
{
 BYTE bS=0x00;
 CONST BYTE *S[8]={&GOST_S1[0],&GOST_S2[0],&GOST_S3[0],&GOST_S4[0],&GOST_S5[0],&GOST_S6[0],&GOST_S7[0],&GOST_S8[0]};
 bData&=0x0F;
 bS=*(S[nS-1]+bData);
 return bS;
}

// ������� ���������� (F) [The Feistel Function]
// ���������:
// [in] dwData - ���� ������ (32 ����)
// [in] dwKey  - ���� (32 ����)
// ������������ ��������:
// ������������� ���� ������ (32 ����)
// <�������� ��������>
DWORD32 hsFGOST(DWORD32 dwData,DWORD32 dwKey)
{
 DWORD64 dwE=(dwData+dwKey)%0x100000000;          // �������� � ������ �� ������ 2^32
 DWORD32 dwF=0x00000000;
 BYTE bS=0x00;
 for(register BYTE i=0;i<8;i++)                   // ���� ������ (S) [Substitution]
 {
  bS=(BYTE)((dwE >> i*4) AND 0x000000000000000F); // �������� 4-����
  bS=hsSGOST(bS,8-i);                             // S-��������������
  dwF|=((DWORD32)bS << 4*i);                      // ��������� ���������� 4-� ������� ����� �� ����� ������
 }
 dwF=hsLCS32(dwF,11);                             // ����������� ����� ����� �� 11 ���
 return dwF;
}

// 64-� ������ �������������� ��������
// ���������:
// [in] dwData - ���� ������ (64 ����)
// [in] dwKey  - ���� (32 ����)
// [in] F      - ���������� �������
// ������������ ��������:
// ������������� ���� ������ (64 ����)
// <�������� ��������>
DWORD64 hsFeistelGOST(DWORD64 dwData,DWORD32 dwKey,DWORD32 (*F)(DWORD32 dwData,DWORD32 dwKey))
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
// [in] dwKey    - ���� (256 ���)
// [in] dwRounds - ����� ������� (������ �������������� ��������)
// [in] F        - ���������� �������
// [in] K        - ������� ������� �����
// [in] hsMode   - ����� [����������,������������]
// ������������ ��������:
// ������������� ���� ������ (64 ����)
// <�������� ��������>
DWORD64 hsFeistelNetworkGOST(CONST DWORD64 dwData,DWORD32 dwKey[8],DWORD32 dwRounds,DWORD32 (*F)(DWORD32 dwData,DWORD32 dwKey),DWORD32 (*K)(DWORD32 dwKey[8],BYTE nRound),HS_CIPHER_MODE hsMode)
{
 DWORD64 dwFN=0x0000000000000000;
 switch(hsMode)
 {
 case HS_ENCRYPTION_MODE:
  {
   //dwFN=hsFeistelGOST(dwData,K(dwKey,0),F);
   dwFN=hsFeistelGOST(dwData,K(dwKey,1),F);
   //for(register DWORD32 i=1;i<=dwRounds;i++)
   for(register DWORD32 i=2;i<=dwRounds;i++)
   { dwFN=hsFeistelGOST(dwFN,K(dwKey,i),F); }
  } break;
 case HS_DECRYPTION_MODE:
  {
   dwFN=hsFeistelGOST(dwData,K(dwKey,dwRounds),F);
   //for(register INT32 i=dwRounds-1;i>=0;i--)
   for(register INT32 i=dwRounds-1;i>=1;i--)
   { dwFN=hsFeistelGOST(dwFN,K(dwKey,i),F); }
  } break;
 }
 dwFN=hsExchange(dwFN);
 return dwFN;
}

// ���������� � ������� ��������� ���� 28147-89
// ���������:
// [in] dwData   - ���� ������ (64 ����)
// [in] dwKey    - ���� (256 ���)
// [in] hsMode   - ����� [����������,������������]
// ������������ ��������:
// ������������� ���� ������ (64 ����)
// <�������� ��������>
DWORD64 hsGOST(DWORD64 dwData,DWORD32 dwKey[8],HS_CIPHER_MODE hsMode)
{
 DWORD64 dwGOST=0x0000000000000000;
 dwGOST=hsFeistelNetworkGOST(dwData,dwKey,32,hsFGOST,hsKGOST,hsMode); // 32 ����� �������������� ��������
 return dwGOST;
}

// ���������� ����� � ������� ��������� ���� 28147-89
// ���������:
// [in] lpSrcFileName - ��� �����, ������� ��������� �����������
// [in] lpDstFileName - ��� �������������� �����
// [in] dwKey    - ���� (256 ���)
// [in] hsMode   - ����� [����������,������������]
DWORD64 hsEncryptFileGOST(LPCTSTR lpSrcFileName,LPCTSTR lpDstFileName,DWORD32 dwKey[8],HS_CIPHER_MODE hsMode)
{
 DWORD dwFileSize,dwBytesRead,dwBytesWritten,dwBlock;
 BYTE *pFileData,*pEncryptedData;
 DWORD64* pData64;

 HANDLE hFileA=CreateFile(lpSrcFileName,GENERIC_READ,0,NULL,OPEN_EXISTING,0,NULL);
 if(hFileA==INVALID_HANDLE_VALUE)
 { return 1; }

 HANDLE hFileB=CreateFile(lpDstFileName,GENERIC_WRITE,0,NULL,CREATE_ALWAYS,0,NULL);
 if(hFileB==INVALID_HANDLE_VALUE)
 { return 1; }

 dwFileSize=GetFileSize(hFileA,NULL);

 pFileData=(PBYTE)malloc(dwFileSize);
 if(pFileData==NULL)
 { return 2; }

 pEncryptedData=(PBYTE)malloc(dwFileSize);
 if(pEncryptedData==NULL)
 { return 2; }

 ReadFile(hFileA,pFileData,dwFileSize,&dwBytesRead,NULL);

 CopyMemory(pEncryptedData,pFileData,dwFileSize);

 pData64=(DWORD64*)pFileData;
 dwBlock=dwFileSize/8;

 for(DWORD i=0;i<dwBlock;i++)
 { ((DWORD64*)pEncryptedData)[i]=hsGOST(pData64[i],dwKey,hsMode); }

 WriteFile(hFileB,pEncryptedData,dwFileSize,&dwBytesWritten,NULL);

 free(pFileData);
 free(pEncryptedData);
 CloseHandle(hFileB);
 CloseHandle(hFileA);
 return 0;
}
#pragma endregion