//#include "hsWin32Errors.h"
//#include "hsBitwise.h"
//#include "hsCrypt.h"

#include "hsRSA.h"
#include "hsConvert.h"
#include "hsMemory.h"
#include "hsPrime.h"
#include "hsLPrime.h"

// �����������:
// - �������� ������� ����������/������������ ����� ����� ����������/������������ (��-��������� 8 ���).

#pragma region RSA
// ������� ���������� ������ ��� ������������� � ��������� RSA.
// ���������:
// [in]  bits - ����� ����� (� �����).
// [out] e - ���� ����������.
// [out] d - ���� ������������.
// [out] n - ��������� (������).
// ���� (e,n) - �������� ����.
// ���� (d,n) - �������� ����.
// ������������ ��������: ���.
// <�������� ��������>
BOOL hsRSAGenerate(LINT &e,LINT &d,LINT &n,UINT Bits)
{
 int sign_u,sign_v;
 LINT p,q,m,u,v;

 // ���������� ��� ������� �����.
 p=hsGetPrimeLINT(Bits);
 do
 { q=hsGetPrimeLINT(Bits); }
 while(p==q);

 // ��������� ������.
 n=p*q;
 // ��������� ������� ������ �� ������.
 //m=hsEuler(n);
 m=(p-1)*(q-1);
 // �������� e - ������� ������� � (p-1)(q-1) �����. (3<e<n-1)
 do
 //{ e=randl(m/3,m); }   // �������� ������������ ���������.
 { e=randBBS(m/3,m); } // ��������� Blum Blum Shub.
 while(hsGCD(e,m)!=1);
 // ���������� d.
 // ������ ��������� 1-� ������� e*d=1(mod m), d<m (�������� �������).
 // ev+mu=���(e,m)=1
 xgcd(e,m,v,sign_v,u,sign_u);
 //xgcd(54,1234,u,sign_u,v,sign_v);
 //xgcd(111,322,u,sign_u,v,sign_v);
 d=v;

 // ���� ������������� �������� � ������� �������� ������������� �����.
 if((-1)==sign_v)
 {
  if(v<m)
  { d=m-v; }
  else
  {
   d=v%m;
   d=m-d;
  }
 }
 return TRUE;
}

BYTE* hsRSAEncrypt(const BYTE *Data,UINT DataSize,const LINT &e,const LINT &n)
{
 UINT i,j,TextSize;
 CHAR *Bin,*Block,*CipherText;
 BYTE *EnData;

 LINT m,LCT;

 // ���������� ������ ����� ������ ��� ����������.
 const UINT k=ld(n);

 // ��������: ��� ���������� m ���������� ����� �������, ����� 1<m<n

 Block=hsAlloc<CHAR>(k+1);
 Bin=hsAlloc<CHAR>(8*DataSize);
 EnData=hsAlloc<BYTE>(k*DataSize);

 // ��������� ��������� � �������� �������������.
 for(i=0;i<DataSize;i++)
 { hsByteToBin(Data[i],&Bin[8*i]); }

 // ������� �����.
 for(i=0;i<DataSize;i++)
 {
  CopyMemory(Block,&Bin[8*i],8);
  Block[8]=0;
  m=LINT(Block,BIN);
  // ����������.
  LCT=hsModularExponentLINT(m,e,n);
  // ��������� ���������.
  CipherText=LCT.binstr();
  TextSize=strlen(CipherText);
  FillMemory(Block,k,0x30);
  for(j=0;j<TextSize;j++)
  { Block[(k-1)-j]=CipherText[(TextSize-1)-j]; }
  CopyMemory(&EnData[k*i],Block,k);
 }

 hsFree(Block);
 hsFree(Bin);
 return EnData;
}

BYTE* hsRSADecrypt(const BYTE *Data,UINT Size,const LINT &d,const LINT &n)
{
 UINT i,j,TextSize;
 CHAR *Bin,*Block,*PlainText;
 BYTE *DeData;

 LINT c,LCT;

 // ���������� ������ ����� ������ ��� ����������.
 const UINT k=ld(n);

 // ���������� ����� ������.
 const UINT p=Size/k;
 //const UINT q=(8*Size)%k;

 Block=hsAlloc<CHAR>(k+1);
 Bin=hsAlloc<CHAR>(8);
 DeData=hsAlloc<BYTE>(p);

 // ��������� �����.
 for(i=0;i<p;i++)
 {
  CopyMemory(Block,&Data[k*i],k);
  Block[k]=0;
  c=LINT(Block,BIN);
  // ������������.
  LCT=hsModularExponentLINT(c,(LINT&)d,(LINT&)n);
  // ��������� ���������.
  PlainText=LCT.binstr();
  TextSize=strlen(PlainText);
  FillMemory(Bin,8,0x30);
  for(j=0;j<TextSize && j<8;j++) // <-- ����������� � 8 ���.
  { Bin[(8-1)-j]=PlainText[(TextSize-1)-j]; }
  DeData[i]=hsBinToByte(Bin);
 }

 hsFree(Block);
 hsFree(Bin);
 return DeData;
}
#pragma endregion