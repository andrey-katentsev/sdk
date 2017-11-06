/* PseudoRandom Number Generator Library */
/* Designed and Programmed by Hyperlink Software�, 2009 */

#define _CRT_RAND_S
#include <stdlib.h>
#include <math.h>

#include "hsRNG.h"
//#include "hsStat.h"

#pragma message("Pseudorandom Number Generator (version 1.0)")

#pragma region NOT FOR EXPORT
#pragma region DATA
// LCM data
unsigned int _hsLCMa=1220703125; // 5^13
unsigned int _hsLCMc=0;
unsigned int _hsLCMm=2147483648; // 2^31
unsigned int _hsLCMx=32;

// SG data
unsigned int _hsQGa=2;
unsigned int _hsQGb=0;
unsigned int _hsQGc=0;
unsigned int _hsQGx=32;
unsigned int _hsQGm=46199;
#pragma endregion

#pragma region STANDART
// R(k)=P(k+1)/P(k)

// ������������������� �������������
DOUBLE RHD(DWORD k,DWORD N,DWORD D,DWORD n)
{
 //return hsHypergeometricCDF(k+1,N,D,n)/hsHypergeometricCDF(k,N,D,n);
 //return (n1-k)*(l-k)/((k+1)*(n-n1-l+1+k)); // (��� �.�.)
 return ((DOUBLE)(D-k)*(n-k))/(DOUBLE)((k+1)*(1+N+k-D-n));
}

// ������������� ��������
DOUBLE RPD(DWORD k,DOUBLE L)
{
 //return hsProbabilityPoisson(k+1,L)/hsProbabilityPoisson(k,L);
 return L/((DOUBLE)k+1.0);
}
#pragma endregion

#pragma endregion

// ���������� ��������������� ����� �� ��������� �� 0 �� UINT_MAX
unsigned int hsRandom(void)
{
 int error;
 unsigned int number;
 error=rand_s(&number);
 return number;
}

#pragma region ����������� ������������� (UNIFORM DISTRIBUTION)
// ���������� ��������������� ����� �� ��������� �� a �� b
int hsUniform(const int a,const int b)
{
 int error;
 unsigned int number;
 error=rand_s(&number);
 return (int)(((double)number/UINT_MAX)*((b+1)-a)+a); // b+1 - ������ ��� ������������� ����� ������.
}

float hsUniform(const float a,const float b)
{
 int error;
 unsigned int number;
 error=rand_s(&number);
 return (((float)number/UINT_MAX)*(b-a)+a);
}

double hsUniform(const double a,const double b)
{
 int error;
 unsigned int number;
 error=rand_s(&number);
 return (((double)number/(double)UINT_MAX)*(b-a)+a);
}

// ���������� ��������������� ����� �� ��������� �� a �� b
DWORD hsUniform(DWORD a,DWORD b)
{
 int error;
 unsigned int number;
 error=rand_s(&number);
 return (DWORD)(((DOUBLE)number/(DOUBLE)UINT_MAX)*((b+1)-a)+a); // ������ ��� ������������� ����� ������.
}

// ���������� ��������������� ����� �� ��������� �� a �� b
// ���������:
// [in] a - ������ ������� ���������
// [in] b - ������� ������� ���������
// ������������ ��������:
// ������������������ ����������� ��������������� ����� �� ��������� [a,b)
// <�������� ��������>
/*UINT32 hsUniform(UINT32 a,UINT32 b)
{
 // ������
 UINT32 uRandom;
 HCRYPTPROV hCSP; // Cryptographic Service Provider
 // ��������� ���������� �����
 CryptAcquireContext(&hCSP,NULL,NULL,PROV_RSA_FULL,0);
 CryptGenRandom(hCSP,sizeof(uRandom),(BYTE*)&uRandom);
 CryptReleaseContext(hCSP,0);
 // ����������� ������������� [a,b)
 //return (UINT32)(((DOUBLE)uRandom/(DOUBLE)_UI32_MAX)*(b-a)+a);
 // ����������� ������������� [a,b]
 return (UINT32)(((DOUBLE)uRandom/(DOUBLE)_UI32_MAX)*((b+1)-a)+a); // ������ ��� ������������� ����� ������.
}*/

// ���������� ��������������� ����� �� ��������� �� a �� b
// ���������:
// [in] a - ������ ������� ���������
// [in] b - ������� ������� ���������
// ������������ ��������:
// ����������������������� ����������� ��������������� ����� �� ��������� [a,b]
// <�������� ��������>
UINT64 hsUniform(UINT64 a,UINT64 b)
{
 // ������
 UINT64 uRandom;
 HCRYPTPROV hCSP; // Cryptographic Service Provider
 // ��������� ���������� �����
 CryptAcquireContext(&hCSP,NULL,NULL,PROV_RSA_FULL,0);
 CryptGenRandom(hCSP,sizeof(UINT64),(BYTE*)&uRandom);
 CryptReleaseContext(hCSP,0);
 // ����������� ������������� [a,b]
 return (UINT64)(((DOUBLE)uRandom/(DOUBLE)_UI64_MAX)*((b+1)-a)+a);  // ������ ��� ������������� ����� ������.
}

// ���������� ��������������� ����� �� ��������� �� a �� b.
// ���������:
// [in] a - ������ ������� ���������
// [in] b - ������� ������� ���������
// ������������ ��������:
// ������������������ ��������������� ����� �� ��������� [a,b].
// <�������� ��������>
DWORD32 hsUniform(DWORD32 a,DWORD32 b)
{
 DWORD32 Random;
 //HCRYPTPROV hCSP; // Cryptographic Service Provider.
 // ��������� ���������� �����
 /*if(FALSE==CryptAcquireContext(&hCSP,NULL,NULL,PROV_RSA_FULL,0))
 { return 0xFFFFFFFF; }
 if(FALSE==CryptGenRandom(hCSP,sizeof(Random),(BYTE*)&Random))
 { return 0xFFFFFFFF; }
 if(FALSE==CryptReleaseContext(hCSP,0))
 { return 0xFFFFFFFF; }*/
 if(0!=rand_s(&Random))
 { return 0xFFFFFFFF; }
 // ����������� ������������� [a,b)
 //return (UINT32)(((DOUBLE)uRandom/(DOUBLE)_UI32_MAX)*(b-a)+a);
 // ����������� ������������� [a,b]
 return (DWORD32)(((DOUBLE)Random/(DOUBLE)0xFFFFFFFF)*((b+1)-a)+a);
}
#pragma endregion
/*
#pragma region HYPERGEOMETRIC DISTRIBUTION
// ������������������� ������������� (Hypergeometric distribution)
// N ~ N,(��� �.�.: n)
// D ~ m,(��� �.�.: n1)
// n ~ n,(��� �.�.: l)
DWORD hsHypergeometric(DWORD N,DWORD D,DWORD n)
{
 DWORD i=0;
 DOUBLE M=hsUniform(0.0,1.0);
 DOUBLE P=hsHypergeometricPDF(i,N,D,n);

 //M-=P;
 ////for(i=0;M>=P;i++)
 //for(i=0;M>=0;i++)
 //{
  //P*=RHD(i,N,D,n);
  //M-=P;
 //}
 while(M>=0)
 {
  P*=RHD(i,N,D,n);
  i++;
  M-=P;
 }

 return i;
}

// ������������������� ������������� (Hypergeometric distribution)
DWORD hsHypergeometric(DWORD N,DWORD D,DWORD n,DOUBLE (*U)(DOUBLE,DOUBLE))
{
 //DWORD i=0;
 //DOUBLE M=U(0.0,1.0);
 //DOUBLE P=hsHypergeometricPDF(0,N,D,n);

 //M-=P;
 ////for(i=0;M>=P;i++)
 //for(i=0;M>=0;i++) // 2 ��������
 //{
  //P*=RHD(i,N,D,n); // 10 ��������
  //M-=P;            // 1 ��������
 //}
 //return i;

 DWORD i=0;
 DOUBLE M=U(0.0,1.0);

 M-=hsHypergeometricPDF(i,N,D,n);  // 1 �������� + 19 ��������
 while(M>=0)
 {
  i++;                             // 1 ��������
  M-=hsHypergeometricPDF(i,N,D,n); // 1 �������� + 19 ��������
 }                                 // �����: 21+1 ��������
 return i;
}
#pragma endregion

#pragma region POISSON DISTRIBUTION
// ������������� �������� (Poisson distribution)
DWORD hsPoisson(DOUBLE L)
{
 DWORD i=0;
 DOUBLE M=hsUniform(0.0,1.0);
 DOUBLE P=hsPoissonPDF(i,L);

 M-=P;
 ////for(i=0;M>=P;i++)
 //for(i=0;M>=0;i++)
 //{
  //P*=RPD(i,L);
  //M-=P;
 //}
 while(M>=0)
 {
  P*=RPD(i,L);
  i++;
  M-=P;
 }
 return i;
}

// ������������� �������� (Poisson distribution)
DWORD hsPoisson(DOUBLE L,DOUBLE (*U)(DOUBLE,DOUBLE))
{
 //DWORD i=0;
 //DOUBLE M=U(0.0,1.0);
 //DOUBLE P=hsPoissonPDF(0,L);

 //M-=P;             // 1 ��������
 ////for(i=0;M>=P;i++)
 //for(i=0;M>=0;i++) // 1 ��������
 //{
  //P*=RPD(i,L);     // 2 �������� + 1 ��������
  //M-=P;            // 1 ��������
 //}
 //return i;
 DWORD i=0;
 DOUBLE M=U(0.0,1.0);
 DOUBLE P=hsPoissonPDF(i,L);

 M-=P;         // 1 ��������
 while(M>=0)
 {
  P*=RPD(i,L); // 2 �������� + 1 ��������
  i++;         // 1 ��������
  M-=P;        // 1 ��������
 }             // �����: 5+1
 return i;
}
#pragma endregion
*/
DWORD hsLCM(VOID)
{
	_hsLCMx=(_hsLCMa*_hsLCMx+_hsLCMc)%_hsLCMm;
	return _hsLCMx;
}

// ���������� ��������������� ����� �� ��������� �� a �� b
DOUBLE hsLCM(DOUBLE a,DOUBLE b)
{
 DWORD number;
	number=hsLCM();
	return (((DOUBLE)number/((DOUBLE)_hsLCMm-1.0))*(b-a)+a);
}

void hsSetLCM(unsigned int a,unsigned int c,unsigned int x,unsigned int m)
{
	_hsLCMa=a;
	_hsLCMc=c;
	_hsLCMm=m;
	_hsLCMx=x;
}

DWORD hsQG(VOID)
{
	_hsQGx=(_hsQGa*_hsQGx*_hsQGx+_hsQGb*_hsQGx+_hsQGc)%_hsQGm;
	return _hsQGx;
}

// ���������� ��������������� ����� �� ��������� �� a �� b
DOUBLE hsQG(DOUBLE a,DOUBLE b)
{
 DWORD number;
	number=hsQG();
	return (((DOUBLE)number/((DOUBLE)_hsQGm-1.0))*(b-a)+a);
}

void hsSetQG(unsigned int a,unsigned int b,unsigned int c,unsigned int x,unsigned int m)
{
	_hsQGa=a;
	_hsQGb=b;
	_hsQGc=c;
	_hsQGx=x;
	_hsQGm=m;
}