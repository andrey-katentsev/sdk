#include "hsDS.h"
#include "hsPrime.h"
#include "hsVector.h"
#include "hsBitwise.h"
#include "hsRNG.h"

#include <math.h>

#pragma message("Digital Signature (version 1.0)")

// �������:
// - ���������� ��� ������ (0), ���� ��������� ������ ������� (ElGamal).

#pragma region Digital Signature (RSA)
// ������� �������� 32-� ������ ���.
// ���������:
// [in] M  - ��������� (�������� ���-������� �� ���������).
// [in] DS - �������� �������.
// [in] e  - ���� ���������� RSA.
// [in] n  - ��������� (������) RSA.
// ������������ ��������:
// TRUE, ���� ������� �����. FALSE � ��������� ������.
// <�������� ��������>
BOOL hsRSA32Verify(DWORD32 M,DWORD32 DS,DWORD32 e,DWORD32 n)
{ return M==hsModularExponent32(DS,e,n)?TRUE:FALSE; }
#pragma endregion

// ElGamal Encryption System (EGES)/ (Taher Elgamal)
#pragma region Digital Signature (ElGamal)
// ��������� ���������� ��� ��� ���-������.
BOOL hsElGamal32Generate(PDWORD32 x,PDWORD32 k,PDWORD32 h,PDWORD32 g,PDWORD32 p,BYTE Bits)
{
 *p=hsGetPrime32(Bits);
 *g=hsUniform(1,*p-1);  // (?) ������ ���� ������������� ������.
 *x=hsUniform(1,*p-1);
 *h=hsElGamal32GetH(*g,*x,*p);
 do
 { *k=hsUniform(1,*p-1); }
 while(1!=hsGCD(*k,*p-1));
 return TRUE;
}
// ������� ��������� 1-� ������� ���� ax=1(mod b).
// ���������:
// [in] a - ������������ �����*.
// [in] b - ������������ �����*.
// *) ���(a,b)=1, �<b.
// ������������ ��������:
// x - ������� ��������� ������ �������.
// 0 - ���� ������� �� ����������.
// <�������� ��������>
DWORD32 hsElGamal32GetXK(DWORD32 a,DWORD32 b)
{
 // ������� ��� �������.
 INT64 q,x[3],y[3],t[3];

 // �������������.
 x[0]=1;
 x[1]=0;
 x[2]=b;

 y[0]=0;
 y[1]=1;
 y[2]=a;

START:
 // ����������� �������� �������.
 if(0==y[2])
 { return 0; }

 if(1==y[2]) // ���(a,b)=1
 {
  while(y[1]<0)
  { y[1]+=b; }
  return (DWORD32)y[1];
 }

 q=x[2]/y[2];

 // t=x-qy
 hsMult3v(y,q,t);
 hsMinus3v(x,t,t);

 x[0]=y[0];
 x[1]=y[1];
 x[2]=y[2];

 y[0]=t[0];
 y[1]=t[1];
 y[2]=t[2];
 goto START;
}

// ������� ��������� �������� ��������� ����� ��� �������� ��� �� ��������� ���-������.
// ���������:
// [in] g - ������������ �����, g<p [�������� ����].
// [in] x - ������������ �����, x<p [��������� ����].
// [in] p - ������� �����           [�������� ����].
// ������������ ��������:
// �������� ��������� ����� h.
// <�������� ��������>
DWORD32 hsElGamal32GetH(DWORD32 g,DWORD32 x,DWORD32 p)
{ return hsModularExponent32(g,x,p); }

// ������� ��������� �������� ������ ���������� ��� �� ��������� ���-������.
// ���������:
// [in] g - ������������ �����, g<p               [�������� ����].
// [in] k - ������������ �����, ���(k,p-1)=1, k<p [��������� ����].
// [in] p - ������� �����                         [�������� ����].
// ������������ ��������:
// ������ ���������� ���.
// <�������� ��������>
DWORD32 hsElGamal32GetA(DWORD32 g,DWORD32 k,DWORD32 p)
{ return hsModularExponent32(g,k,p); }

// ������� ��������� �������� ������ ���������� ��� �� ��������� ���-������.
// ���������:
// [in] M   - ��������� (�������� ���-������� �� ���������).
// [in] x   - ������������ �����, x<p               [��������� ����].
// [in] k   - ������������ �����, ���(k,p-1)=1, k<p [��������� ����].
// [in] DSA - ������ ���������� ���.
// [in] p   - ������� �����                         [�������� ����].
// ������������ ��������:
// ������ ���������� ���.
// <�������� ��������>
DWORD32 hsElGamal32GetB(DWORD32 M,DWORD32 x,DWORD32 k,DWORD32 DSA,DWORD32 p)
{
 INT64 DSB=((INT64)hsElGamal32GetXK(k,p-1)*((INT64)M-(INT64)x*(INT64)DSA))%(INT64)(p-1);
 while(DSB<0)
 { DSB+=(p-1); }
 return (DWORD32)DSB;
}

// ������� ��� ���������� 32-� ������ ���.
// ���������:
// [in] M    - ��������� (�������� ���-������� �� ���������).
// [in] x    - ������������ �����, x<p               [��������� ����].
// [in] k    - ������������ �����, ���(k,p-1)=1, k<p [��������� ����].
// [in] g    - ������������ �����, g<p               [�������� ����].
// [in] p    - ������� ����� [�������� ����].
// [out] DSA - ������ ���������� ��� (������� 32-� ������ �����).
// [out] DSB - ������ ���������� ��� (������� 32-� ������ �����).
// ������������ ��������:
// 64-� ������ �������� ��� <DSA,DSB>.
// ���� �������� �������� 32-� ������� ����� DSB ����� ����, ������ HS_ERROR_INVALID_PARAMETERS.
// <�������� ��������>
DWORD64 hsElGamal32Sign(DWORD32 M,DWORD32 x,DWORD32 k,DWORD32 g,DWORD32 p,PDWORD32 DSA,PDWORD32 DSB)
{
 *DSA=hsElGamal32GetA(g,k,p);
 *DSB=hsElGamal32GetB(M,x,k,*DSA,p);
 return HS_MAKEDWORD64(*DSA,*DSB);
}

// ������� �������� 32-� ������ ���.
// ���������:
// [in] M   - ��������� (�������� ���-������� �� ���������).
// [in] DSA - ������ ���������� ��� (������� 32-� ������ �����).
// [in] DSB - ������ ���������� ��� (������� 32-� ������ �����).
// [in] h   - ������������ �����      [�������� ����].
// [in] g   - ������������ �����, g<p [�������� ����].
// [in] p   - ������� �����           [�������� ����].
// ������������ ��������:
// TRUE, ���� ������� �����. FALSE � ��������� ������.
// <�������� ��������>
BOOL hsElGamal32Verify(DWORD32 M,DWORD32 DSA,DWORD32 DSB,DWORD32 h,DWORD32 g,DWORD32 p)
{
 DWORD32 A=hsModularExponent32(h,DSA,p);
 DWORD32 B=hsModularExponent32(DSA,DSB,p);
 return ((DWORD64)A*(DWORD64)B)%p==hsModularExponent32(g,M,p)?TRUE:FALSE;
}
#pragma endregion