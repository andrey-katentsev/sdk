/* Mathematic Library */
/* Designed and Programmed by Hyperlink Software�, 2006-2009 */
/* E-Mail: hyperlink@inbox.ru */
/* UIN: 282757076 */

#pragma once

#ifndef HS_MATH_LIBRARY
#define HS_MATH_LIBRARY
#endif

// �������������� ��������.
#define PLUS     +
#define MINUS    -
#define MULTIPLY *
#define DIVIDE   /
#define MODULUS  %

#define MULT MULTIPLY
#define DIV  DIVIDE
#define MOD  MODULUS

// �������������� ���������.
#define Pi 3.1415926535897932384626433832795
#define e  2.7182818284590452353602874713526

// ������� �� �������� � ������� � �������.
#define TO_DEGREES 57.295779513082320876798154814105   //(180/PI)
#define TO_RADIANS 0.017453292519943295769236907684886 //(PI/180)

// �������������� �������.
double __stdcall hsLog(double Base,double X);

#define ln(X) log((double)X)
#define lg(X) hsLog(10.0,(double)X)
#define lb(X) hsLog(2.0,(double)X)

/*template <class T> T hsABS(const T &n)
{ return n<0?(-n):n; }*/

/*
#pragma region ���������� � ���� ����� (GF(2,8))
BYTE hsGaloisMultiplication(BYTE a,BYTE b);
#pragma endregion

#pragma region ������� ��������� ���������
 int hsSortByIncreaseDWORD(LPVOID Reserved,CONST LPDWORD A,CONST LPDWORD B);
 int hsSortByIncreaseDWORD(LPVOID Reserved,CONST LPDWORD A,CONST LPDWORD B);

 int hsSortByIncreaseDOUBLE(LPVOID Reserved,CONST LPDOUBLE A,CONST LPDOUBLE B);
 int hsSortByDecreaseDOUBLE(LPVOID Reserved,CONST LPDOUBLE A,CONST LPDOUBLE B);
#pragma endregion

DOUBLE hsFactorial(DWORD n); // ���������
DOUBLE hsBinomialCoefficient(DWORD n,DWORD k); // ������������ �����������

//#define F(n)   hsFactorial(n)
#define C(n,k) hsBinomialCoefficient(n,k)

DOUBLE hsRectagleMethod(DOUBLE a,DOUBLE b,DOUBLE (*f)(DOUBLE x),DWORD n); // ���������� ������������ ��������� (����� ���������������)

// The Gamma Function: �(z)
// For all complex numbers z, the following recurrence relation is true: �(z+1)=z*�(z)
// Consequently, for positive integers: n!=�(n+1)
DOUBLE hsGamma(DOUBLE z);

void hsMultMM(double** MatrixA,double** MatrixB,double** MatrixC,unsigned int Rows,unsigned int Columns); // ��������� ������: A[Rows][Columns] * B[Columns][Rows] = C[Rows][Rows]

#ifdef __cplusplus
} // extern "C" {
#endif
*/