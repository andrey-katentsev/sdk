/* Designed and programmed by Hyperlink, 2007. */
/* Copyright by Hyperlink */
/* Contacts: */
/* E-mail: hyperlink@mail.cis.ru */
/* UIN: 282757076 */

#ifndef HS_VECTOR_UTILITIES
#define HS_VECTOR_UTILITIES

#define HS_VECTOR_UTILITIES_VERSION 1.0

#include <math.h>

/* —ообщени€ об ошибках */
#define HS_SUCCESS 0x0000     // ”спешное выполнение команды
#define HS_NULLVECTOR 0x0001  // ¬ектор нулевой длины

int hsNormalize2dv(double *vector); // ѕриведение вектора к единичной длине (нормализаци€)

float hsScalar3fv(float *vector1,float *vector2); // —кал€рное произведение двух векторов
float hsModule3fv(float *vector);  // ¬ычисление длины вектора (модуль)
int hsNormalize3fv(float *vector); // ѕриведение вектора к единичной длине (нормализаци€)
void hsVector3fv(float *vector1,float *vector2,float *vector3); // ¬екторное произведение двух векторов
void hsNormal3fv(float *point1,float *point2,float *point3,float *vector); // ¬ычисление нормали к поверхности образованной 3-м€ точками не лежащими на одной пр€мой
float hsCosinus3fv(float *vector1,float *vector2); //  осинус угла между двум€ векторами

double hsScalar3dv(double *vector1,double *vector2); // —кал€рное произведение двух векторов
double hsModule3dv(double *vector); // ¬ычисление длины вектора (модуль)
int hsNormalize3dv(double *vector); // ѕриведение вектора к единичной длине (нормализаци€)
void hsVector3dv(double *vector1,double *vector2,double *vector3); // ¬екторное произведение двух векторов
void hsNormal3dv(double *point1,double *point2,double *point3,double *vector); // ¬ычисление нормали к поверхности образованной 3-м€ точками не лежащими на одной пр€мой
double hsCosinus3dv(double *vector1,double *vector2); //  осинус угла между двум€ векторами

template <class T> void hsMinus3v(const T* vector1,const T* vector2,T* vector3)
{
 for(register char i=0;i<3;i++)
 { vector3[i]=vector1[i]-vector2[i]; }
}

template <class T,class W> void hsMult3v(const T* vector1,const W scalar,T* vector2)
{
 for(register char i=0;i<3;i++)
 { vector2[i]=scalar*vector1[i]; }
}
#endif