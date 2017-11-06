/* Statistic Library */
/* Programmed by Hyperlink Software�, 2009 */
/* E-Mail: hyperlink@inbox.ru */
/* UIN: 282757076 */

#ifndef HS_STATISTIC_LIBRARY
#define HS_STATISTIC_LIBRARY

//#include <windows.h>
//#include "hsWin32Types.h"
#include "hsTypes.h"

#pragma region ����������� ���������� [Standard Statistics]
// ������ ��������������� ��������.
// <�������� ��������>
template <class T> double hsMean(const T *Sample,size_t SampleSize)
{
 double Mean=0.0;
 for(register size_t i=0;i<SampleSize;i++)
 { Mean+=Sample[i]; }
 return Mean/(double)SampleSize;
}
//double hsMean(const LPDWORD lpSample,DWORD dwSampleSize);

// ������ ���������.
// <�������� ��������>
template <class T> double hsVariance(const T Sample,size_t SampleSize)
{
 double Mean=0.0,Variance=0.0;
 Mean=hsMean(Sample,SampleSize);
 Mean*=Mean; // M^2X
 for(register size_t i=0;i<SampleSize;i++)
 { Variance+=(double)Sample[i]*(double)Sample[i]; }
 Variance/=(double)SampleSize; // MX^2
 return Variance-Mean;         // MX^2-M^2X
}
//double hsVariance(const LPDWORD lpSample,DWORD dwSampleSize);

// ������ ������������ ���������� ��� ������������ ������������� [0,M].
double hsCorrelation(const LPDWORD32 lpSample,DWORD32 dwSampleSize,DWORD32 dwS,DWORD dwMax);
#pragma endregion

// ����������� ������� ��������������� ������������������.
DWORD32 hsGetPeriod(const LPDWORD32 Sample,DWORD32 SampleSize,DWORD32 Significance);

#pragma region �������� ������������������ [Binary Samples]
// �������������� �������� ������������� ��������������� �������� �������������������
DOUBLE hsBinaryBalance(CONST LPBIT lpSample,DWORD dwSampleSize); // �������������������
DOUBLE hsBinaryRound(CONST LPBIT lpSample,DWORD dwSampleSize); // �����������
DOUBLE hsBinaryCorrelation(CONST LPBIT lpSample,DWORD dwSampleSize,DWORD dwShift); // ����������

DOUBLE hsBinaryCHISquareStandartUniform(CONST LPBIT bSample,DWORD dwSampleSize); // ���������� �������� ��-������� �������� ������� �������� � �������� �������� ������������� � ����������� �������������� �� ��������� [0,1]
//DWORD hsBinaryGetPeriod(CONST LPBIT lpSample,DWORD dwSampleSize); // ����������� ������� �������� ������������������
DWORD hsBinaryGetPeriod(CONST LPBIT lpSample,DWORD dwSampleSize,DWORD dwSignificance); // ����������� ������� �������� ������������������
#pragma endregion

/*
PDF - Probability Density Function (������� ��������� �����������) [f]
CDF - Cumulative Distribution Function (������� ������������� �����������) [F]

F' = f [d/dx(F) = f]

Sample - �������
Set of Order Statistic - ������������ ���
*/

/*
#pragma region ������� ������������� �����������
#pragma region ����������� �������������
DOUBLE hsUniformCDF(DOUBLE a,DOUBLE b,DOUBLE x);  // ������� ������������� ����������� ������������ ������������� �� ������� [a,b]
#pragma endregion

DOUBLE hsPoissonCDF(DWORD k,DOUBLE L); // ������� ������������� ����������� ������������� �������� � ���������� L
DOUBLE hsHypergeometricCDF(DWORD k,DWORD N,DWORD D,DWORD n); // ������� ������������� ����������� �������������������� �������������

#pragma region ���������� �����������
DOUBLE hsKolmogorovCDF(DOUBLE S); // ������� ������������� ����������� ���������� �����������
#pragma endregion
#pragma endregion

DOUBLE hsHypergeometricPDF(DWORD k,DWORD N,DWORD D,DWORD n); // ����������� �������� ����� �� ��������� k
DOUBLE hsPoissonPDF(DWORD k,DOUBLE L);                  // ����������� �������� ����� �� ��������� k
DOUBLE hsChiSquarePDF(DWORD n,DOUBLE x);                 // ������� ��������� ����������� ������������� ��-������� � n ��������� �������

DWORD hsInverseTest(CONST LPDWORD lpSample,DWORD dwSampleSize); // �������� ����� ������������ (���� �� �����������)
DWORD hsFrequencyTest(CONST LPDWORD lpSample,DWORD dwSampleSize,DWORD m,DWORD K,LPDOUBLE lpRate,LPDOUBLE lpMX,LPDOUBLE lpDX); // ��������� ���� (���� �� �������������)
DOUBLE hsCorrelationTest(CONST LPDWORD lpSample,DWORD dwSampleSize,DWORD m,DWORD s); // ������ ���������� (���� �� �������������)

#pragma region �������� ��-������� �������
DOUBLE hsTestChiSquare(DWORD n,DOUBLE S);                                                                // ��������� �������� P{S>S*}
DOUBLE hsChiSquareTestPoisson(CONST LPDWORD lpSample,DWORD dwSampleSize,DOUBLE L);                       // ���������� �������� ��-������� ������� �������� ������� �������� � �������� �������� ������������� � �������������� ��������
DOUBLE hsChiSquareTestHypergeometric(CONST LPDWORD lpSample,DWORD dwSampleSize,DWORD N,DWORD D,DWORD n); // ���������� �������� ��-������� ������� �������� ������� �������� � �������� �������� ������������� � ������������������� ��������������

DOUBLE hsChiSquareUniform(CONST LPDWORD lpSample,DWORD dwSampleSize,DWORD K,DWORD A,DWORD B); // ���������� �������� ��-������� �������� �������� � �������� �������� ������������� � ����������� �������������� �� ��������� [A,B]
#pragma endregion

DOUBLE hsAndersonDarlingDistribution(DOUBLE S); // ������� ������������� ���������� �����-������� ���������-�������� (������������ ��� �������� ������� �������� � �������� �������� ������������� � �������������)
DOUBLE hsAndersonDarlingUniform(CONST LPDWORD lpSample,DWORD dwSampleSize,DOUBLE (*F)(DOUBLE A,DOUBLE B,DOUBLE X),DOUBLE A,DOUBLE B); // ���������� ���������-�������� ��� �������� �������� � �������� �������� ������������� � ����������� �������������� �� ��������� [A,B]

#pragma region �������� �����������
DOUBLE hsKolmogorovTestUniform(CONST LPDOUBLE lpSample,DWORD dwSampleSize,DOUBLE a,DOUBLE b);             // ���������� ����������� ��� �������� ������� �������� � �������� �������� ������������� � ����������� ��������������
DOUBLE hsKolmogorovTestPoisson(CONST LPDWORD lpSample,DWORD dwSampleSize,DOUBLE L);                       // ���������� ����������� ��� �������� ������� �������� � �������� �������� ������������� � �������������� ��������
DOUBLE hsKolmogorovTestHypergeometric(CONST LPDWORD lpSample,DWORD dwSampleSize,DWORD N,DWORD D,DWORD n); // ���������� ����������� ��� �������� ������� �������� � �������� �������� ������������� � ������������������� ��������������
#pragma endregion
*/
#endif