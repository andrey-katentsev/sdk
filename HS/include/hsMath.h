/* Mathematic Library */
/* Designed and Programmed by Hyperlink Software®, 2006-2009 */
/* E-Mail: hyperlink@inbox.ru */
/* UIN: 282757076 */

#pragma once

#ifndef HS_MATH_LIBRARY
#define HS_MATH_LIBRARY
#endif

// Арифметические действия.
#define PLUS     +
#define MINUS    -
#define MULTIPLY *
#define DIVIDE   /
#define MODULUS  %

#define MULT MULTIPLY
#define DIV  DIVIDE
#define MOD  MODULUS

// Математические константы.
#define Pi 3.1415926535897932384626433832795
#define e  2.7182818284590452353602874713526

// Перевод из градусов в радианы и обратно.
#define TO_DEGREES 57.295779513082320876798154814105   //(180/PI)
#define TO_RADIANS 0.017453292519943295769236907684886 //(PI/180)

// Математические функции.
double __stdcall hsLog(double Base,double X);

#define ln(X) log((double)X)
#define lg(X) hsLog(10.0,(double)X)
#define lb(X) hsLog(2.0,(double)X)

/*template <class T> T hsABS(const T &n)
{ return n<0?(-n):n; }*/

/*
#pragma region Вычисления в поле Галуа (GF(2,8))
BYTE hsGaloisMultiplication(BYTE a,BYTE b);
#pragma endregion

#pragma region Функции сравнения элементов
 int hsSortByIncreaseDWORD(LPVOID Reserved,CONST LPDWORD A,CONST LPDWORD B);
 int hsSortByIncreaseDWORD(LPVOID Reserved,CONST LPDWORD A,CONST LPDWORD B);

 int hsSortByIncreaseDOUBLE(LPVOID Reserved,CONST LPDOUBLE A,CONST LPDOUBLE B);
 int hsSortByDecreaseDOUBLE(LPVOID Reserved,CONST LPDOUBLE A,CONST LPDOUBLE B);
#pragma endregion

DOUBLE hsFactorial(DWORD n); // Факториал
DOUBLE hsBinomialCoefficient(DWORD n,DWORD k); // Биномиальный коэффициент

//#define F(n)   hsFactorial(n)
#define C(n,k) hsBinomialCoefficient(n,k)

DOUBLE hsRectagleMethod(DOUBLE a,DOUBLE b,DOUBLE (*f)(DOUBLE x),DWORD n); // Вычисление определённого интеграла (Метод прямоугольников)

// The Gamma Function: Г(z)
// For all complex numbers z, the following recurrence relation is true: Г(z+1)=z*Г(z)
// Consequently, for positive integers: n!=Г(n+1)
DOUBLE hsGamma(DOUBLE z);

void hsMultMM(double** MatrixA,double** MatrixB,double** MatrixC,unsigned int Rows,unsigned int Columns); // Умножение матриц: A[Rows][Columns] * B[Columns][Rows] = C[Rows][Rows]

#ifdef __cplusplus
} // extern "C" {
#endif
*/