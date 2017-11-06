/* Statistic Library */
/* Programmed by Hyperlink Software®, 2009 */
/* E-Mail: hyperlink@inbox.ru */
/* UIN: 282757076 */

#ifndef HS_STATISTIC_LIBRARY
#define HS_STATISTIC_LIBRARY

//#include <windows.h>
//#include "hsWin32Types.h"
#include "hsTypes.h"

#pragma region Стандартные статистики [Standard Statistics]
// Оценка математического ожидания.
// <Контроль качества>
template <class T> double hsMean(const T *Sample,size_t SampleSize)
{
 double Mean=0.0;
 for(register size_t i=0;i<SampleSize;i++)
 { Mean+=Sample[i]; }
 return Mean/(double)SampleSize;
}
//double hsMean(const LPDWORD lpSample,DWORD dwSampleSize);

// Оценка дисперсии.
// <Контроль качества>
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

// Оценка коэффициента корреляции для равномерного распределения [0,M].
double hsCorrelation(const LPDWORD32 lpSample,DWORD32 dwSampleSize,DWORD32 dwS,DWORD dwMax);
#pragma endregion

// Определение периода псевдослучайной последовательности.
DWORD32 hsGetPeriod(const LPDWORD32 Sample,DWORD32 SampleSize,DWORD32 Significance);

#pragma region Двоичные последовательности [Binary Samples]
// Статистические свойства периодических псевдослучайных двоичных последовательностей
DOUBLE hsBinaryBalance(CONST LPBIT lpSample,DWORD dwSampleSize); // Сбаланисированность
DOUBLE hsBinaryRound(CONST LPBIT lpSample,DWORD dwSampleSize); // Цикличность
DOUBLE hsBinaryCorrelation(CONST LPBIT lpSample,DWORD dwSampleSize,DWORD dwShift); // Корреляция

DOUBLE hsBinaryCHISquareStandartUniform(CONST LPBIT bSample,DWORD dwSampleSize); // Статистика критерия ХИ-квадрат проверки простой гипотезы о согласии опытного распределения с равномерным распределением на интервале [0,1]
//DWORD hsBinaryGetPeriod(CONST LPBIT lpSample,DWORD dwSampleSize); // Определение периода двоичной последовательности
DWORD hsBinaryGetPeriod(CONST LPBIT lpSample,DWORD dwSampleSize,DWORD dwSignificance); // Определение периода двоичной последовательности
#pragma endregion

/*
PDF - Probability Density Function (Функция плотности вероятности) [f]
CDF - Cumulative Distribution Function (Функция распределения вероятности) [F]

F' = f [d/dx(F) = f]

Sample - Выборка
Set of Order Statistic - Вариационный ряд
*/

/*
#pragma region Функции распределения вероятности
#pragma region Равномерное распределение
DOUBLE hsUniformCDF(DOUBLE a,DOUBLE b,DOUBLE x);  // Функция распределения вероятности равномерного распределения на отрезке [a,b]
#pragma endregion

DOUBLE hsPoissonCDF(DWORD k,DOUBLE L); // Функция распределения вероятности распределения Пуассона с параметром L
DOUBLE hsHypergeometricCDF(DWORD k,DWORD N,DWORD D,DWORD n); // Функция распределения вероятности гипергеометрического распределения

#pragma region Статистика Колмогорова
DOUBLE hsKolmogorovCDF(DOUBLE S); // Функция распределения вероятности статистики Колмогорова
#pragma endregion
#pragma endregion

DOUBLE hsHypergeometricPDF(DWORD k,DWORD N,DWORD D,DWORD n); // Вероятность получить число со значением k
DOUBLE hsPoissonPDF(DWORD k,DOUBLE L);                  // Вероятность получить число со значением k
DOUBLE hsChiSquarePDF(DWORD n,DOUBLE x);                 // Функция плотности вероятности распределения ХИ-квадрат с n степенями свободы

DWORD hsInverseTest(CONST LPDWORD lpSample,DWORD dwSampleSize); // Проверка числа перестановок (Тест на случайность)
DWORD hsFrequencyTest(CONST LPDWORD lpSample,DWORD dwSampleSize,DWORD m,DWORD K,LPDOUBLE lpRate,LPDOUBLE lpMX,LPDOUBLE lpDX); // Частотный тест (Тест на равномерность)
DOUBLE hsCorrelationTest(CONST LPDWORD lpSample,DWORD dwSampleSize,DWORD m,DWORD s); // Оценка корреляции (Тест на независимость)

#pragma region Критерий Хи-квадрат Пирсона
DOUBLE hsTestChiSquare(DWORD n,DOUBLE S);                                                                // Вычисляет значение P{S>S*}
DOUBLE hsChiSquareTestPoisson(CONST LPDWORD lpSample,DWORD dwSampleSize,DOUBLE L);                       // Статистика критерия ХИ-квадрат Пирсона проверки простой гипотезы о согласии опытного распределения с распределением Пуассона
DOUBLE hsChiSquareTestHypergeometric(CONST LPDWORD lpSample,DWORD dwSampleSize,DWORD N,DWORD D,DWORD n); // Статистика критерия ХИ-квадрат Пирсона проверки простой гипотезы о согласии опытного распределения с гипергеометрическим распределением

DOUBLE hsChiSquareUniform(CONST LPDWORD lpSample,DWORD dwSampleSize,DWORD K,DWORD A,DWORD B); // Статистика критерия ХИ-квадрат проверки гипотезы о согласии опытного распределения с равномерным распределением на интервале [A,B]
#pragma endregion

DOUBLE hsAndersonDarlingDistribution(DOUBLE S); // Функция распределения статистики ОМЕГА-квадрат Андерсона-Дарлинга (используется для проверки простой гипотезы о согласии опытного распределения с теоретическим)
DOUBLE hsAndersonDarlingUniform(CONST LPDWORD lpSample,DWORD dwSampleSize,DOUBLE (*F)(DOUBLE A,DOUBLE B,DOUBLE X),DOUBLE A,DOUBLE B); // Статистика Андерсона-Дарлинга для проверки гипотезы о согласии опытного распределения с равномерным распределением на интервале [A,B]

#pragma region Критерий Колмогорова
DOUBLE hsKolmogorovTestUniform(CONST LPDOUBLE lpSample,DWORD dwSampleSize,DOUBLE a,DOUBLE b);             // Статистика Колмогорова для проверки простой гипотезы о согласии опытного распределения с равномерным распределением
DOUBLE hsKolmogorovTestPoisson(CONST LPDWORD lpSample,DWORD dwSampleSize,DOUBLE L);                       // Статистика Колмогорова для проверки простой гипотезы о согласии опытного распределения с распределением Пуассона
DOUBLE hsKolmogorovTestHypergeometric(CONST LPDWORD lpSample,DWORD dwSampleSize,DWORD N,DWORD D,DWORD n); // Статистика Колмогорова для проверки простой гипотезы о согласии опытного распределения с гипергеометрическим распределением
#pragma endregion
*/
#endif