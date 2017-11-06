/* ���������� ������� ����� (Prime Numbers Library) */
/* ����������: �������� �.�., 2009 ���. */
/* �2009, �������� �.�. */

/* ���������� ����������: */
/* E-Mail: hyperlink@inbox.ru */
/* UIN: 282757076 */

#pragma once

#include <windows.h>

// ������� ��������� ���������� ����� �������� ���� ����� a � b.
// ���(a,b), GCD(a,b) (Greatest Common Divisor)
// ������������ �������� �������.
// <�������� ��������>
template <class T> T hsGCD(T a,T b)
{
 // ��������������� ����������.
 T t;

 // ������ ������� ��������, ���� ����������.
 if(b>a)
 {
  t=a;
  a=b;
  b=t;
 }

 // �������� �������
 while(b!=0)
 {
  t=a%b;
  a=b;
  b=t;
 }

 // ���������� ���(a,b)
 return a;
}

// ������� ���������� �������� �� ��� ����� a � b ���������������.
// <�������� ��������>
template <class T> bool hsIsCoprime(T a,T b)
{ return hsGCD(a,b)==1?true:false; }

// ��������� �������� ������� ������.
// <�������� ��������>
template <class T> T hsEulerWiki(T n)
{
 T i,p,e=1;
 for(i=2;i*i<=n;++i)
 {
  p=1;
  while(n%i==0)
  {
   p*=i;
   n/=i;
  }

  if((p/=i)>=1)
  { e*=p*(i-1); }
 }

 return (--n>0)?n*e:e;
}

// ���������� ������� ������ (������� ������������ ����� [������� ���������]).
// <�������� ��������>
template <class T> T hsEuler(T n)
{
	T i,e=n;

 // ������������ ����� ������� �������� ���������.
 for(i=2;i*i<=n;++i)
 {
  // ����� ��������.
  if(n%i==0)
  {
   // ��������� �����.
   while(n%i==0)
   { n/=i; }
   // ��������� �������� ���������� ��� ������� ������.
   e-=e/i;
  }
 }

 // ��������� ���������, ���� ��� ����������.
 if(n>1)
 { e-=e/n; }

 return e;
}

// ���������� ������� ������ (��-�����������).
/*template <class T> T hsEuler(T n)
{
 // �������� ������� ������
 T e=0;

 // ���������� �������� ������� ������ (��-�����������).
 for(T i=1;i<n;i++)
 {
  if(1==hsGCD(n,i))
  { e++; }
 }

 return e;
}*/

#define hsTotient(n) hsEuler(n)

// �������� �������� ���������� � ������� �� ������.
// ��������: Page 244 of Bruce Schneier's "Applied Cryptography", 2e, ISBN 0-471-11709-9
// <�������� ��������>
template <class T> T hsModularExponent(T base,T power,T modulus) 
{
 T result=1;

 while(power>0)
 {
  if((power&1)==1)
  { result=(result*base)%modulus; } // Multiply in this bit's contribution while using modulus to keep result small.
  power>>=1; // Move to the next bit of the exponent, square (and mod) the base accordingly.
  base=(base*base)%modulus;
 }
 return result;
}

#pragma region ��������� ������������
// ������������ ����� ������� �������� ���������.
// <�������� ��������>
template <class T> T* hsFactorization(T n,unsigned int &count)
{
 T i,*p;

 count=0;
 p=NULL;

 // ������� ���� �����(��� �������: �������) ����� �� 2 �� ����������� ����� �� �������������� �����.
 for(i=2;i*i<=n;++i)
 {
  // ����� ��������.
  if(n%i==0)
  {
   // ��������� �����.
   while(n%i==0)
   { n/=i; }

   // ��������� ������ ������� ������������.
   count++;
   p=(T*)realloc(p,count*sizeof(T));
   p[count-1]=i;
  }
 }

 // ��������� � ������ ��������� �����������, ���� �� ����������.
 if(n>1)
 {
  count++;
  p=(T*)realloc(p,count*sizeof(T));
  p[count-1]=n;
 }

 return p;
}

//#include "hsRNG.h"

// ����� p-��������.
// ���������:
// [in] n      - �����, ������� ��������� ��������� �� ������� �����������.
// [in] f(x,n) - ������� ��������� ��������������� ����� �� ������ n.
// ������������ ��������:
// ������� ����� - �������� n, ��� 0 � ������ ��������.
// �������� ����� � �� ����� ������� ����������� ���� ��� ���������� n. � ���� ������ ������� ����� ������ f(x) � ���������� �����.
// <�������� ��������>
template <class T> T hsPollardsRho(const T &n,T (*f)(const T&,const T&))
{
 T x=2,y=2,d=1,t;

 while(1==d)
 {
  x=f(x,n);      // x=f(x);
  y=f(f(y,n),n); // y=f(f(y));

  t=x>y?x-y:y-x; // t=|x-y|;
  d=hsGCD(t,n);  // d=GCD(|x-y|,n);
 }

 if(n==d) // �������.
 { return 0; }

 return d;

 /*T x,y,k,d,i=1;

 // 1) �������� ��������� ������� x(i) �� ��������� {0,1,...,n-1};
 //seedBBS(GetTickCount());
 //x=randBBS(0,n-1);
 //seedl(LINT(GetTickCount()));
 x=hsUniform(0,n-1);
 y=x;
 k=2;

LOOP:
 // 2) ��������� ��������� ������� ������������������.
 i=i+1;
 x=f(x)%n;

 // 3) ���������� �� ����?
 d=hsGCD(y-x,n);

 if(1!=d && n!=d)
 { return d; } // d - �������� n, ���� ��������.

 // 4) ��������� ��������
 if(i==k)
 {
  y=x;
  k=2*k;
 }
 goto LOOP;*/
}
#pragma endregion

// ������� ������� ��� ������������� ����� ��� ��������� n.
// ��������:
// - ������� �������� ������� ������ �� n (e), ����������� ��� (p).
// - ���������� ��� ����� g=2..n
// - (!) ��� ������� �����, ��� �������� ����������� ���(g,n)=1
// - ���� g^e=1(mod n), �� ������� ��� �������� g^(e/p(i)) mod n
// - ���� ��� �������� g ��� ��� ����� ��������� ��������� �� 1, �� g �������� ������� ������������� ������.
// ���������:
// [in]  n  - ����� ��� �������� ��������� ����� ������������� �����.
// [out] rn - ���������� ������������� ������.
// ������������ ��������:
// ��������� �� ������� ������ � ������� ������������� rn �������� ������������� ������.
// ����� �������������� ������ ������� ���� ����������� �������� free().
// <�������� ��������>
template <class T> T* hsPrimitiveRootModuloN(T n,T &rn)
{
 unsigned int pn,i,j=0;
 T e,g,*p,*r;
 bool f;

 // ��������� �������� ������� ������.
 e=hsEuler(n);

 // ��������� ���������� ������������� ������. (�������������)
 rn=hsEuler(e);

 // �������� ������ ��� ���������� ������������� ������.
 r=(T*)malloc(rn*sizeof(T));

 // ����������� �������� ������� ������.
 p=hsFactorization(e,pn);

 // ���������� ��� ����� g=2..n
 for(g=2;g<n;g++)
 {
  // (!) ������� ���� ��������� ��� ���(g,n)==1 (!) �, ���� g^e=1(mod n), �� g - ��� � ���� ������������� ������ (���������� ���� ����� �� �����).
  // ...
  // ���� g^e=1(mod n), ��...
  if(hsModularExponent(g,e,n)==1) // (?) ����� �� ��� ��������?
  {
   // ...������� ��� �������� g^(e/p(i)) mod n
   f=true;
   for(i=0;i<pn && f;i++)
   {
    // ���� g^(e/p(i))=1(mod n), �� g �� �������� ������������� ������ �� ������ N.
    if(hsModularExponent(g,e/p[i],n)==1)
    { f=false; }
   }
   // ���� ��� �������� g ��� ��������� �� �����������, �� g �������� ������������� ������.
   if(f)
   { r[j++]=g; }
  }
 }

 // �������������� ����� ������������� ������. (?) �����, ���� ��� ��������?
 rn=j;
 free(p);
 return r;
}

#pragma region ��������� ����������
DWORD32 hsModularExponent32(DWORD32 Base,DWORD32 Power,DWORD32 Modulus);
#pragma endregion

#pragma region ������� �����
#define HS_PRIME_ACCURACY_DEFAULT 5

DWORD32 hsGetPrime32(BYTE Bits=32,BYTE Accuracy=HS_PRIME_ACCURACY_DEFAULT);

#pragma region ���� �������-������
#define COMPOSITE FALSE
#define PRIME     TRUE

BOOL hsMillerRabinPass32(DWORD32 Number,BYTE Accuracy=HS_PRIME_ACCURACY_DEFAULT);
#pragma endregion
#pragma endregion

/*
#pragma region ������� �����
DWORD32 hsGetPrime32(BYTE Bits=32,DOUBLE dAccuracy=0.0009765625); // ��������� n-������� �������� �����
BOOL hsMillerRabinPass32(UINT32 uNumber,DOUBLE dAccuracy=0.0009765625); // ���� �������-������ (�������� ����� �� ��������)
UINT32* hsPrimitiveRootModuloN32(UINT32 uN,UINT32 &uTotal);
#pragma endregion
*/