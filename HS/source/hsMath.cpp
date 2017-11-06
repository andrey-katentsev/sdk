#include <math.h>
#include "hsMath.h"

#pragma message("Mathematical Library (version 1.0 BETA)")

// Функция вычисляет значения логарифма по основанию Base числа X.
// Параметры:
// [in] Base  - основание логарифма.
// [in] X     - число, логарифм по основанию Base которого необходимо вычислить.
// Возвращаемое значение:
// Логарифм по основанию Base числа X.
// <Контроль качества>
double __stdcall hsLog(double Base,double X)
{
 //log(a,b)=log(c,b)/log(c,a) - замена основания логарифма.
 //return log10(X)/log10(base);
 return log(X)/log(Base);
}
/*
#pragma region Функции сравнения элементов
// <Контроль качества>
int hsSortByIncreaseDWORD(LPVOID Reserved,CONST LPDWORD A,CONST LPDWORD B)
{
 if(*A==*B){return 0;}
 return *A>*B?1:-1;
}

// <Контроль качества>
int hsSortByDecreaseDWORD(LPVOID Reserved,CONST LPDWORD A,CONST LPDWORD B)
{
 if(*A==*B){return 0;}
 return *A<*B?1:-1;
}

// <Контроль качества>
int hsSortByIncreaseDOUBLE(LPVOID Reserved,CONST LPDOUBLE A,CONST LPDOUBLE B)
{
 if(*A==*B){return 0;}
 return *A>*B?1:-1;
}

// <Контроль качества>
int hsSortByDecreaseDOUBLE(LPVOID Reserved,CONST LPDOUBLE A,CONST LPDOUBLE B)
{
 if(*A==*B){return 0;}
 return *A<*B?1:-1;
}
#pragma endregion

// Факториал
DOUBLE hsFactorial(DWORD n)
{
 DOUBLE F=1.0;
 if(n==0){return F;}
 for(REGISTER DWORD k=1;k<=n;k++)
 { F*=k; }
 return F;
}

// Биномиальный коэффициент
DOUBLE hsBinomialCoefficient(DWORD n,DWORD k)
{
 DOUBLE BC=0.0;
 if(k>n){return BC;}
 BC=(hsFactorial(n)/(hsFactorial(k)*hsFactorial(n-k))); // n*2 + k*2 + (n-k)*2 + 2 операций
 return BC;
}

#pragma region DEFINITE INTEGRAL
DOUBLE hsRectagleMethod(DOUBLE a,DOUBLE b,DOUBLE (*f)(DOUBLE x),DWORD n)
{
 DOUBLE dx=(b-a)/(DOUBLE)n;
 DOUBLE y=0.0;
 for(REGISTER DWORD i=0;i<n;i++)
 { y+=f(a+i*dx); }
 return dx*y;
}
#pragma endregion

DOUBLE hsGamma(DOUBLE z)
{
 CONST DOUBLE p[7]={1.000000000190015,76.18009172947146,-86.50532032941677,24.01409824083091,-1.231739572450155,1.208650973866179E-3,-5.395239384953E-6};
 DOUBLE G=0.0;
 for(REGISTER DWORD n=1;n<=6;n++)
 { G+=(p[n]/(z+n)); }
 G+=p[0];
 G*=(sqrt(2.0*PI)/z);
 G*=pow(z+5.5,z+0.5);
 G*=pow(E,-(z+5.5));
 return G;
}
/*
DOUBLE hsGamma(DOUBLE z)
{
 CONST DOUBLE q[7]={75122.6331530,80916.6278952,36308.2951477,8687.24529705,1168.92649479,83.8676043424,2.50662827511};
 DOUBLE A=1.0;
 DOUBLE G=0.0;
 for(REGISTER DWORD n=0;n<=6;n++)
 {
  G+=(q[n]*pow(z,(DOUBLE)n));
  A*=(z+n);
 }
 G/=A;
 G*=pow(z+5.5,z+0.5);
 G*=pow(E,-(z+5.5));
 return G;
}
*/
/*
void hsMultMM(double** MatrixA,double** MatrixB,double** MatrixC,unsigned int Rows,unsigned int Columns)
{
 for(register unsigned int i=0;i<Rows;i++)
  for(register unsigned int j=0;j<Rows;j++)
   for(register unsigned int k=0;k<Columns;k++)
    MatrixC[i][j]+=MatrixA[i][k]*MatrixB[k][j];
}

#pragma region Вычисления в поле Галуа (GF(2,8))
BYTE hsGaloisMultiplication(BYTE a,BYTE b)
{
 BYTE p = 0;
	BYTE counter;
	BYTE hi_bit_set;
	for(counter = 0; counter < 8; counter++)
 {
  if((b & 1) == 1)
   p ^= a;
  hi_bit_set = (a & 0x80);
  a <<= 1;
  if(hi_bit_set == 0x80)
   a ^= 0x1b;
  b >>= 1;
 }
 return p;
}
#pragma endregion*/