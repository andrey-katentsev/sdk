#include "hsStat.h"
#include <math.h>

#pragma region Стандартные статистики [Standard Statistics]
// Оценка математического ожидания.
/*double hsMean(const LPDWORD lpSample,DWORD dwSampleSize)
{
 double dMean=0.0;
 for(register DWORD i=0;i<dwSampleSize;i++)
 { dMean+=(double)lpSample[i]; }
 return dMean/(double)dwSampleSize;
}*/

// Оценка дисперсии.
/*double hsVariance(const LPDWORD lpSample,DWORD dwSampleSize)
{
 double dMean=0.0,dVariance=0.0;
 dMean=hsMean(lpSample,dwSampleSize);
 dMean*=dMean; // M2X
 for(register DWORD i=0;i<dwSampleSize;i++)
 { dVariance+=(double)lpSample[i]*(double)lpSample[i]; }
 dVariance/=(double)dwSampleSize; // MX2
 return dVariance-dMean; // MX2-M2X
}*/

// Оценка коэффициента корреляции между числами X(i) и X(i+dwS), отстоящих друг от друга на шаг dwS>0.
// Для равномерного распределения на отрезке [0,dwMAX]
double hsCorrelation(const LPDWORD lpSample,DWORD dwSampleSize,DWORD dwS,DWORD dwMax)
{
 double dCorrelation=0.0;
 for(register DWORD i=0;i<dwSampleSize-dwS;i++)
 { dCorrelation+=(double)lpSample[i]*(double)lpSample[i+dwS]; }
 dCorrelation*=12.0;
 dCorrelation/=(((double)dwMax*(double)dwMax)*((double)dwSampleSize-(double)dwS));
 return dCorrelation-3.0;
}
#pragma endregion

// Функция сравнения двух подпоследовательностей.
// Параматры:
// [in] Sample        - исходная выборка.
// [in] BaseA         - индекс начала первой подпоследовательности (первый элемент подпоследовательности Sample[BaseA]).
// [in] BaseB         - индекс начала второй подпоследовательности (первый элемент подпоследовательности Sample[BaseB]).
// [in] Period        - период сравниваемых последовательностей.
// [out] TotalChecked - число совпадений.
// Возвращаемое значение:
// TRUE - подпоследовательности равны. TotalMatches содержит период подпоследовательности.
// FALSE - подпоследовательности не равны. TotalMatches содержит индекс первого отличающегося элемента, начиная со смещения BaseA.
// <Контроль качества>
template <class T,class W> BOOL hsCheckSubPeriod(const T* Sample,W BaseA,W BaseB,W Period,W* TotalChecked)
{
 W Stop=min(BaseA,BaseB)+1;
 W offset=0;

 if(Period>BaseA-BaseB)
 { return FALSE; }

 for(offset=0;offset<Period && Stop;offset++,Stop--)
 {
  if(Sample[BaseA-offset]!=Sample[BaseB-offset])
  { return FALSE; }
 }
 *TotalChecked=offset;
 return TRUE;
}

// Определение периода псевдослучайной последовательности.
// Параматры:
// [in] Sample       - выборка.
// [in] SampleSize   - объём выборки.
// [in] Significance - глубина проверки.
// Возвращаемое значение:
// Период псевдослучайной последовательности.
// <Контроль качества>
DWORD32 hsGetPeriod(const LPDWORD32 Sample,DWORD32 SampleSize,DWORD32 Significance)
{
 DWORD32 Base=SampleSize-1;
 DWORD32 Period=1;
 DWORD32 Matches=0;
 DWORD32 Rate=0;

 BOOL Stop=FALSE;

 for(Period=1;Period<Base;Period++)
 {
  if(Sample[Base]==Sample[Base-Period])
  {
   Stop=FALSE;
   Rate=0;
   for(register DWORD32 i=1;i*Period<Base && !Stop;i++,Rate++)
   {
    if(Rate==Significance) // Достигнут требуемый уровень значимости. (Глубина проверки)
    { return Period; }
    if(FALSE==hsCheckSubPeriod(Sample,Base,Base-i*Period,Period,&Matches))
    { Stop=TRUE; }
   }
   if(!Stop)
   { return Period; }
  }
 }
 return SampleSize;
}

#pragma region Двоичные последовательности [Binary Samples]
// Статистические свойства периодических псевдослучайных двоичных последовательностей
// Сбалансированность
DOUBLE hsBinaryBalance(CONST LPBIT lpSample,DWORD dwSampleSize)
{
 DOUBLE dStatistic=0.0; // Статистика

 // Подсчитываем число двоичных 1
 for(register DWORD ecx=0;ecx<dwSampleSize;ecx++)
 { dStatistic+=(DOUBLE)lpSample[ecx]; }

 // Вычисляем значение статистики
 return dStatistic/((DOUBLE)dwSampleSize-dStatistic);
}

// Цикличность
DOUBLE hsBinaryRound(CONST LPBIT lpSample,DWORD dwSampleSize)
{
 DOUBLE dStatistic=1.0; // Статистика
 DWORD dwBlocksTotal=0; // Количество последовательностей
 DWORD dwCount=0;       // Длина последовательности
 LPDOUBLE dTotal=NULL;  // Таблица длин последовательностей

 dTotal=new DOUBLE[dwSampleSize];
 ZeroMemory(dTotal,dwSampleSize*sizeof(DOUBLE));

 // Подсчитываем длины последовательностей и их количество
 for(register DWORD ecx=0;ecx<dwSampleSize;ecx++)
 {
  dwCount=0;
  for(register DWORD eax=ecx;eax<dwSampleSize;eax++)
  {
   if(lpSample[ecx]==lpSample[eax])
   { dwCount++; }
   else
   { break ; }
  }
  dwBlocksTotal++;
  dTotal[dwCount-1]+=1.0;
  ecx+=(dwCount-1);
 }

 // Вычисляем значение статистики
 for(register DWORD ecx=0;ecx<dwSampleSize;ecx++)
 {
  dTotal[ecx]/=((DOUBLE)dwBlocksTotal/pow(2.0,(DOUBLE)ecx+1.0));
  if(dTotal[ecx]!=0.0)
  { dStatistic*=dTotal[ecx]; }
 }
 delete [] dTotal;
 return dStatistic;
}

// Корреляция
DOUBLE hsBinaryCorrelation(CONST LPBIT lpSample,DWORD dwSampleSize,DWORD dwShift)
{
 DOUBLE dStatistic=0.0; // Статистика

 // Подсчитываем число совпадений исходной и сдвинутой последовательности
 for(register DWORD ecx=0;ecx<dwSampleSize;ecx++)
 {
  if(lpSample[ecx]==lpSample[(ecx+dwShift)%dwSampleSize])
  { dStatistic+=1.0; }
 }
 return dStatistic/((DOUBLE)dwSampleSize-dStatistic);
}

// Статистика критерия ХИ-квадрат проверки простой гипотезы о согласии опытного распределения с равномерным распределением на интервале [0,1]
DOUBLE hsBinaryCHISquareStandartUniform(CONST LPBIT bSample,DWORD dwSampleSize)
{
 DWORD N=dwSampleSize; // Объём выборки
 DWORD K=2; // Число интервалов [0,1),[1,#INF)
 DWORD n[2]={0,0}; // Число значений попавших в каждый интервал
 DOUBLE P[2]={0.5,0.5}; // Вероятность попадания в интервал
 DOUBLE S=0.0; // Статистика

 // Подсчитываем число попаданий в каждый интервал
 for(register DWORD i=0;i<N;i++)
 { n[1]+=(DWORD)bSample[i]; }
 n[0]=N-n[1];

 // Вычисляем статистику ХИ-квадрат
 for(register DWORD i=0;i<K;i++)
 { S+=pow((DOUBLE)n[i]/(DOUBLE)N-P[i],2.0)/P[i]; }
 S*=N;

 return S;
}

DWORD hsBinaryGetPeriod(CONST LPBIT lpSample,DWORD dwSampleSize,DWORD dwSignificance)
{
 DWORD dwBase=dwSampleSize-1;
 DWORD dwPeriod=1;
 DWORD dwChecked=0;
 DWORD dwRate=0;
 BOOL bStop=FALSE;
 for(dwPeriod=1;dwPeriod<dwBase;dwPeriod++)
 {
  if(lpSample[dwBase]==lpSample[dwBase-dwPeriod])
  {
   bStop=FALSE;
   dwRate=0;
   for(register DWORD i=1;i*dwPeriod<dwBase && !bStop;i++,dwRate++)
   {
    if(dwRate==dwSignificance) // Достигнут требуемый уровень значимости
    { return dwPeriod; }
    if(hsCheckSubPeriod(lpSample,dwBase,dwBase-i*dwPeriod,dwPeriod,&dwChecked)==FALSE)
    { bStop=TRUE; }
   }
   if(!bStop)
   { return dwPeriod; }
  }
 }
 return dwSampleSize;
}
#pragma endregion

/*
#include <math.h>
#include "hsMath.h"

#pragma region Функуии плотности вероятности
// k - число событий, произошедших за фиксированное время, при условии, что данные события происходят с некоторой фиксированной средней интенсивностью и независимо друг от друга.
DOUBLE hsPoissonPDF(DWORD k,DOUBLE L)
{ return (pow(L,(DOUBLE)k)*pow(E,-L))/hsFactorial(k); }

// Вероятность получить число со значением k
// Вероятность получения ровно k успехов в серии из n испытаний
DOUBLE hsHypergeometricPDF(DWORD k,DWORD N,DWORD D,DWORD n)
{
 DOUBLE PHD=0.0;
 PHD=(C(D,k)*C(N-D,n-k))/C(N,n); // 5*3+4 операции
 return PHD;
}

DOUBLE hsChiSquarePDF(DWORD n,DOUBLE x)
{ return (pow(1.0/2.0,(DOUBLE)n/2.0)*pow(x,((DOUBLE)n/2.0)-1.0)*pow(E,-x/2.0))/hsGamma((DOUBLE)n/2.0); }
#pragma endregion

#pragma region Функции распределения вероятности
#pragma region Равномерное распределение
// Функция распределения вероятности непрерывного равномерного распределения
// <Контроль качетва>
DOUBLE hsUniformCDF(DOUBLE a,DOUBLE b,DOUBLE x)
{
 if(x<a)
 { return 0.0; }
 if(x>=b)
 { return 1.0; }
 return ((x-a)/(b-a));
}
#pragma endregion

// Функция распределения вероятности распределения Пуассона с параметром L
DOUBLE hsPoissonCDF(DWORD k,DOUBLE L)
{
 DOUBLE P=0.0;
 for(REGISTER DWORD i=0;i<=k;i++)
 { P+=hsPoissonPDF(i,L); }
 return P;
}

DOUBLE hsHypergeometricCDF(DWORD k,DWORD N,DWORD D,DWORD n) // Функция распределения вероятности гипергеометрического распределения
{
 DOUBLE H=0.0;
 for(REGISTER DWORD i=0;i<=k;i++)
 { H+=hsHypergeometricPDF(i,N,D,n); }
 return H;
}

#pragma region Статистика Колмогорова
// Функция распределения вероятности статистики Колмогорова
// S - значение статистики Колмогорова
// <Контроль качества>
DOUBLE hsKolmogorovCDF(DOUBLE S)
{
 DOUBLE K=0.0;
 for(REGISTER INT32 k=-12;k<=12;k++) // (-1.#INF,1.#INF)
 { K+=pow(-1.0,(DOUBLE)k)*pow(E,-2.0*pow((DOUBLE)k,2.0)*pow(S,2.0)); }
 return K;
}
#pragma endregion
#pragma endregion

#pragma region NOT FOR EXPORT
#pragma region DATA
DWORD _ChiSquareN=1;
#pragma endregion

int hsMoreThan(VOID *pContext,CONST DWORD* pValueA,CONST DWORD* pValueB)
{
 if((*pValueA)==(*pValueB))
 { return 0; }
 return ((*pValueA)>(*pValueB))?1:(-1);
}

DOUBLE _hsChiSquarePDF(DOUBLE x)
{ return hsChiSquarePDF(_ChiSquareN,x); }
#pragma endregion

DWORD hsInverseTest(CONST LPDWORD lpSample,DWORD dwSampleSize)
{
	DWORD dwStatistic=0;
	for(REGISTER DWORD i=0;i+1<dwSampleSize;i++)
	{
		if(lpSample[i]>lpSample[i+1])
		{ dwStatistic++; }
	}
	return dwStatistic;
}

DWORD hsFrequencyTest(CONST LPDWORD lpSample,DWORD dwSampleSize,DWORD m,DWORD K,LPDOUBLE lpRate,LPDOUBLE lpMX,LPDOUBLE lpDX)
{
	DWORD dwStatistic=0;
	DOUBLE dLength=(DOUBLE)m/(DOUBLE)K; // 1.	Разбиваем [0,m) на K равных интервалов.

	// 2.	Подсчитаем количество элементов, попадавших в каждый интервал.
	for(REGISTER DWORD i=0;i<dwSampleSize;i++)
	{
		for(REGISTER DWORD j=0;j<K;j++)
		{
			if(lpSample[i]>=j*dLength && lpSample[i]<(j+1)*dLength)
			{ lpRate[j]++; break; }
		}
	}

	// 3. Рассчитаем относительные частоты попаданий в интервалы
	for(REGISTER DWORD i=0;i<K;i++)
	{ lpRate[i]/=dwSampleSize; }

	*lpMX=hsMean(lpSample,dwSampleSize); // 4. Оценка математического ожидания
	*lpDX=hsVariance(lpSample,dwSampleSize); // 5. Оценка дисперсии

	return dwStatistic;
}

DOUBLE hsCorrelationTest(CONST LPDWORD lpSample,DWORD dwSampleSize,DWORD m,DWORD s)
{
	DOUBLE dStatistic=0;
	dStatistic=hsCorrelation(lpSample,dwSampleSize,s,m);
	return dStatistic;
}

#pragma region Критерий Хи-Квадрат Пирсона
// Вычисляет значение P{S>S*}
// n - число степеней свободы распределения Хи-квадрат
// S - значение статистики Хи-квадрат Пирсона
// <Контроль качества>
DOUBLE hsTestChiSquare(DWORD n,DOUBLE S)
{
 _ChiSquareN=n;
 return hsRectagleMethod(S,S*3.0,_hsChiSquarePDF,1000000);
}

DOUBLE hsChiSquareUniform(CONST LPDWORD lpSample,DWORD dwSampleSize,DWORD K,DWORD A,DWORD B)
{
 DWORD D=(B-A)/K;      //K - Число интервалов
 DWORD N=dwSampleSize; // Объём выборки
 DWORD *n=NULL;        // Число значений попавших в каждый интервал
 DOUBLE *P=NULL;       // Вероятность попадания в интервал
 DOUBLE S=0.0;         // Статистика

 n=new DWORD[N];
 P=new DOUBLE[N];

 ZeroMemory(n,N*sizeof(DWORD));
 ZeroMemory(P,N*sizeof(DOUBLE));

 // Подсчитываем число попаданий в каждый интервал
 for(REGISTER DWORD i=0;i<N;i++)
 {
  P[i]=1.0/(DOUBLE)K; // Вероятность попадания в i-й интервал
  for(REGISTER DWORD j=0;j<K;j++)
  {
   if((A+j*D)<=lpSample[i] && lpSample[i]<(A+(j+1)*D))
   {
    n[j]++;
    break;
   }
  }
 }

 // Вычисляем статистику ХИ-квадрат
 for(REGISTER DWORD i=0;i<K;i++)
 { S+=pow((DOUBLE)n[i]/(DOUBLE)N-P[i],2.0)/P[i]; }
 S*=N;

 delete [] n;
 delete [] P;

 return S;
}

// Статистика критерия ХИ-квадрат Пирсона проверки гипотезы о согласии опытного распределения с теоретическим
// lpSample     - выборка
// dwSampleSize - объём выборки
// L            - Параметр функции распределения Пуассона
// <Контроль качества>
DOUBLE hsChiSquareTestPoisson(CONST LPDWORD lpSample,DWORD dwSampleSize,DOUBLE L)
{
 DOUBLE S=0.0;   // Статистика Хи-квадрат Пирсона
 DWORD K=0;      // Число интервалов разбиения
 DOUBLE *P=NULL; // Вероятности попадания в интервал
 DWORD *Nn=NULL; // Группированая выборка (Число значений попавших в каждый интервал)

 // Подсчитываем число интервалов
 for(REGISTER DWORD i=0;i<dwSampleSize;i++)
 { K=max(K,lpSample[i]); }

 K+=2; // Включаем P(K=0) и P(K=x)

 P=new DOUBLE[K];
 Nn=new DWORD[K];

 ZeroMemory(P,K*sizeof(DOUBLE));
 ZeroMemory(Nn,K*sizeof(DWORD));

 // Группируем выборку (Подсчитываем число попаданий в каждый интервал)
 for(REGISTER DWORD i=0;i<dwSampleSize;i++)
 { Nn[lpSample[i]]++; }

 // Вычисляем вероятности попадания в интервалы
 for(REGISTER DWORD i=0;i<K;i++)
 { P[i]=hsPoissonPDF(i,L); }
 P[K-1]=1-hsPoissonCDF(K-2,L); // P(K=x)

 // Вычисляем значение статистики ХИ-квадрат Пирсона
 for(REGISTER DWORD i=0;i<K;i++)
 { S+=pow((DOUBLE)Nn[i]/(DOUBLE)dwSampleSize-P[i],2.0)/P[i]; }
 S*=(DOUBLE)dwSampleSize;

 //for(REGISTER DWORD i=0;i<K;i++)
 //{ S+=pow((DOUBLE)Nn[i]-(DOUBLE)dwSampleSize*P[i],2.0)/((DOUBLE)dwSampleSize*P[i]); }

 delete [] P;
 delete [] Nn;
 return S;
}

// Статистика критерия ХИ-квадрат Пирсона проверки гипотезы о согласии опытного распределения с теоретическим
// lpSample - выборка
// dwSampleSize - объём выборки
// N,D,n - Параметрs функции гипергеометрического распределения
// <Контроль качества>
DOUBLE hsChiSquareTestHypergeometric(CONST LPDWORD lpSample,DWORD dwSampleSize,DWORD N,DWORD D,DWORD n)
{
 DOUBLE S=0.0;   // Статистика Хи-квадрат Пирсона
 DWORD K=0;      // Число интервалов разбиения
 DOUBLE *P=NULL; // Вероятности попадания в интервал
 DWORD *Nn=NULL; // Группированая выборка (Число значений попавших в каждый интервал)

 //K=D+1;

 // Подсчитываем число интервалов
 for(REGISTER DWORD i=0;i<dwSampleSize;i++)
 { K=max(K,lpSample[i]); }

 K++; // Включаем P(K=0)

 P=new DOUBLE[K];
 Nn=new DWORD[K];

 ZeroMemory(P,K*sizeof(DOUBLE));
 ZeroMemory(Nn,K*sizeof(DWORD));

 // Группируем выборку (Подсчитываем число попаданий в каждый интервал)
 for(REGISTER DWORD i=0;i<dwSampleSize;i++)
 { Nn[lpSample[i]]++; }

 // Вычисляем вероятности попадания в интервалы
 for(REGISTER DWORD i=0;i<K;i++)
 { P[i]=hsHypergeometricPDF(i,N,D,n); }

 // Вычисляем значение статистики ХИ-квадрат Пирсона
 for(REGISTER DWORD i=0;i<K;i++)
 { S+=pow((DOUBLE)Nn[i]/(DOUBLE)dwSampleSize-P[i],2.0)/P[i]; }
 S*=dwSampleSize;

 delete [] P;
 delete [] Nn;
 return S;
}
#pragma endregion

DOUBLE hsAndersonDarlingDistribution(DOUBLE S)
{
 DOUBLE ADD=0.0;
 return ADD;
}

DOUBLE hsAndersonDarlingUniform(CONST LPDWORD lpSample,DWORD dwSampleSize,DOUBLE (*F)(DOUBLE A,DOUBLE B,DOUBLE X),DOUBLE A,DOUBLE B)
{
 DOUBLE S=0.0;         // Значение статистики
 DWORD N=dwSampleSize; // Объём выборки

 DOUBLE M,P,L,R;

 // Вариационный ряд
 DWORD *pSetOfOrderStatistic=NULL;
 pSetOfOrderStatistic=new DWORD[N];
 for(REGISTER DWORD i=0;i<N;i++)
 { pSetOfOrderStatistic[i]=lpSample[i]; }
 qsort_s(pSetOfOrderStatistic,N,sizeof(DWORD),(int (*)(void*,const void*,const void*))hsMoreThan,NULL);

 for(REGISTER DWORD i=0;i<N;i++)
 {
  P=F(A,B,pSetOfOrderStatistic[i]);
  if(P==0 || P==1) // Пропускаем граничные точки (ln(0)=#INF, ln(1)=0)
  { continue; }
  M=(2.0*((DOUBLE)i+1.0)-1.0)/(2.0*(DOUBLE)N);
  L=M*log(P);
  R=(1.0-M)*log(1.0-P);
  S+=(L+R);
 }
 S*=2.0;
 delete [] pSetOfOrderStatistic;
 return -(DOUBLE)N-S;
}

#pragma region Критерий Колмогорова
// Проверка простой гипотезы о согласии опытного распределения с теоретическим (критерий Колмогорова)
// lpSample - выборка
// dwSampleSize - объём выборки
// a,b - Параметры функции непрерывного равномерного распределения
// <Контроль качества>
DOUBLE hsKolmogorovTestUniform(CONST LPDOUBLE lpSample,DWORD dwSampleSize,DOUBLE a,DOUBLE b)
{
 DOUBLE S=0.0;  // Статистика Колмогорова
 DOUBLE DN=0.0; // Dn
 DOUBLE DP=0.0; // Dn+
 DOUBLE DM=0.0; // Dn-
 LPDOUBLE SetOfOrder=new DOUBLE[dwSampleSize]; // Вариационный ряд

 // Составляем вариационный ряд
 CopyMemory((LPDOUBLE)SetOfOrder,(CONST LPDOUBLE)lpSample,dwSampleSize*sizeof(DOUBLE));
 qsort_s(SetOfOrder,dwSampleSize,sizeof(DOUBLE),(int (*)(void*,const void*,const void*))hsSortByIncreaseDOUBLE,0);

 // Вычисляем значение статистики Dn
 for(REGISTER DWORD i=0;i<dwSampleSize;i++)
 {
  DP=max(DP,((DOUBLE)i+1.0)/(DOUBLE)dwSampleSize-hsUniformCDF(a,b,SetOfOrder[i]));
  DM=max(DM,hsUniformCDF(a,b,SetOfOrder[i])-(DOUBLE)i/(DOUBLE)dwSampleSize);
 }
 DN=max(DP,DM);

 // Вычисляем значение статистики Колмогорова
 S=(6.0*(DOUBLE)dwSampleSize*DN+1.0)/(6.0*sqrt((DOUBLE)dwSampleSize));

 delete [] SetOfOrder;
 return S;
}

// Проверка простой гипотезы о согласии опытного распределения с теоретическим (критерий Колмогорова)
// lpSample     - выборка
// dwSampleSize - объём выборки
// L            - Параметр функции распределения Пуассона
// <Контроль качества>
DOUBLE hsKolmogorovTestPoisson(CONST LPDWORD lpSample,DWORD dwSampleSize,DOUBLE L)
{
 DOUBLE S=0.0;  // Статистика Колмогорова
 DOUBLE DN=0.0; // Dn
 DOUBLE DP=0.0; // Dn+
 DOUBLE DM=0.0; // Dn-
 LPDWORD SetOfOrder=new DWORD[dwSampleSize]; // Вариационный ряд

 // Составляем вариационный ряд
 CopyMemory((LPDWORD)SetOfOrder,(CONST LPDWORD)lpSample,dwSampleSize*sizeof(DWORD));
 qsort_s(SetOfOrder,dwSampleSize,sizeof(DWORD),(int (*)(void*,const void*,const void*))hsSortByIncreaseDWORD,0);

 // Вычисляем значение статистики Dn
 for(REGISTER DWORD i=0;i<dwSampleSize;i++)
 {
  DP=max(DP,((DOUBLE)i+1.0)/(DOUBLE)dwSampleSize-hsPoissonCDF(SetOfOrder[i],L));
  DM=max(DM,hsPoissonCDF(SetOfOrder[i],L)-(DOUBLE)i/(DOUBLE)dwSampleSize);
 }
 DN=max(DP,DM);

 // Вычисляем значение статистики Колмогорова
 S=(6.0*(DOUBLE)dwSampleSize*DN+1.0)/(6.0*sqrt((DOUBLE)dwSampleSize));

 delete [] SetOfOrder;
 return S;
}

// Проверка простой гипотезы о согласии опытного распределения с теоретическим (критерий Колмогорова)
// lpSample - выборка
// dwSampleSize - объём выборки
// N,D,n - Параметр функции гипергеометрического распределения
// <Контроль качества>
DOUBLE hsKolmogorovTestHypergeometric(CONST LPDWORD lpSample,DWORD dwSampleSize,DWORD N,DWORD D,DWORD n)
{
 DOUBLE S=0.0;  // Статистика Колмогорова
 DOUBLE DN=0.0; // Dn
 DOUBLE DP=0.0; // Dn+
 DOUBLE DM=0.0; // Dn-
 LPDWORD SetOfOrder=new DWORD[dwSampleSize]; // Вариационный ряд

 // Составляем вариационный ряд
 CopyMemory((LPDWORD)SetOfOrder,(CONST LPDWORD)lpSample,dwSampleSize*sizeof(DWORD));
 qsort_s(SetOfOrder,dwSampleSize,sizeof(DWORD),(int (*)(void*,const void*,const void*))hsSortByIncreaseDWORD,0);

 // Вычисляем значение статистики Dn
 for(REGISTER DWORD i=0;i<dwSampleSize;i++)
 {
  DP=max(DP,((DOUBLE)i+1.0)/(DOUBLE)dwSampleSize-hsHypergeometricCDF(SetOfOrder[i],N,D,n));
  DM=max(DM,hsHypergeometricCDF(SetOfOrder[i],N,D,n)-(DOUBLE)i/(DOUBLE)dwSampleSize);
 }
 DN=max(DP,DM);

 // Вычисляем значение статистики Колмогорова
 S=(6.0*(DOUBLE)dwSampleSize*DN+1.0)/(6.0*sqrt((DOUBLE)dwSampleSize));

 delete [] SetOfOrder;
 return S;
}
#pragma endregion

// ЗАМЕНЕНО!
BOOL hsCheckSubPeriod(const LPDWORD32 Sample,DWORD32 BaseA,DWORD32 BaseB,DWORD32 Period,LPDWORD32 TotalMatches)
{
 DWORD32 Stop=min(BaseA,BaseB)+1;
 DWORD32 offset=0;

 if(Period>BaseA-BaseB)
 { return FALSE; }

 for(offset=0;offset<Period && Stop;offset++,Stop--)
 {
  if(Sample[BaseA-offset]!=Sample[BaseB-offset])
  { return FALSE; }
 }
 *TotalMatches=offset;
 return TRUE;
}

BOOL hsCheckSubPeriod(const LPBIT Sample,DWORD32 BaseA,DWORD32 BaseB,DWORD32 Period,LPDWORD32 TotalChecked)
{
 DWORD32 Stop=min(BaseA,BaseB)+1;
 DWORD32 offset=0;

 if(Period>BaseA-BaseB)
 { return FALSE; }

 for(offset=0;offset<Period && Stop;offset++,Stop--)
 {
  if(Sample[BaseA-offset]!=Sample[BaseB-offset])
  { return FALSE; }
 }
 *TotalChecked=offset;
 return TRUE;
}
*/