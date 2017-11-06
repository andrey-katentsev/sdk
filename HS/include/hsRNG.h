/* PseudoRandom Number Generator Library */
/* Designed and Programmed by Hyperlink Software�, 2009 */

#ifndef HS_PSEUDORANDOM_NUMBER_GENERATOR_LIBRARY
#define HS_PSEUDORANDOM_NUMBER_GENERATOR_LIBRARY

#include <windows.h>

#define HS_RANDOM_MAX 0xFFFFFFFF

unsigned int hsRandom(void); // ���������� ��������������� ����� �� ��������� �� 0 �� UINT_MAX

// ���������� ��������������� ����� �� ��������� �� a �� b
int hsUniform(const int a,const int b);

float hsUniform(const float a,const float b);
double hsUniform(const double a,const double b);

DWORD hsUniform(DWORD a,DWORD b);
//UINT32 hsUniform(UINT32 a,UINT32 b);
UINT64 hsUniform(UINT64 a,UINT64 b);
DWORD32 hsUniform(DWORD32 a,DWORD32 b);

DWORD hsHypergeometric(DWORD N,DWORD D,DWORD n); // ���������� ��������������� �����, ������������� �������������������� ������������� (Hypergeometric distribution)
DWORD hsHypergeometric(DWORD N,DWORD D,DWORD n,DOUBLE (*U)(DOUBLE,DOUBLE));

DWORD hsPoisson(DOUBLE L); // ���������� ��������������� �����, ������������� ������������� �������� (Poisson distribution)
DWORD hsPoisson(DOUBLE L,DOUBLE (*U)(DOUBLE,DOUBLE));

DWORD hsLCM(VOID); // �������� ������������ ����� (Linear Congruous Method)
DWORD hsQG(VOID);  // ������������ ��������� (Quadratic Generator)

DOUBLE hsLCM(DOUBLE a,DOUBLE b); // ���������� ��������������� ����� �� ��������� �� a �� b
DOUBLE hsQG(DOUBLE a,DOUBLE b);  // ���������� ��������������� ����� �� ��������� �� a �� b

void hsSetLCM(unsigned int a=1220703125,unsigned int c=0,unsigned int x=32,unsigned int m=2147483648);
void hsSetQG(unsigned int a=2,unsigned int b=0,unsigned int c=0,unsigned int x=32,unsigned int m=46199);

#endif