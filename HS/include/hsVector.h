/* Designed and programmed by Hyperlink, 2007. */
/* Copyright by Hyperlink */
/* Contacts: */
/* E-mail: hyperlink@mail.cis.ru */
/* UIN: 282757076 */

#ifndef HS_VECTOR_UTILITIES
#define HS_VECTOR_UTILITIES

#define HS_VECTOR_UTILITIES_VERSION 1.0

#include <math.h>

/* ��������� �� ������� */
#define HS_SUCCESS 0x0000     // �������� ���������� �������
#define HS_NULLVECTOR 0x0001  // ������ ������� �����

int hsNormalize2dv(double *vector); // ���������� ������� � ��������� ����� (������������)

float hsScalar3fv(float *vector1,float *vector2); // ��������� ������������ ���� ��������
float hsModule3fv(float *vector);  // ���������� ����� ������� (������)
int hsNormalize3fv(float *vector); // ���������� ������� � ��������� ����� (������������)
void hsVector3fv(float *vector1,float *vector2,float *vector3); // ��������� ������������ ���� ��������
void hsNormal3fv(float *point1,float *point2,float *point3,float *vector); // ���������� ������� � ����������� ������������ 3-�� ������� �� �������� �� ����� ������
float hsCosinus3fv(float *vector1,float *vector2); // ������� ���� ����� ����� ���������

double hsScalar3dv(double *vector1,double *vector2); // ��������� ������������ ���� ��������
double hsModule3dv(double *vector); // ���������� ����� ������� (������)
int hsNormalize3dv(double *vector); // ���������� ������� � ��������� ����� (������������)
void hsVector3dv(double *vector1,double *vector2,double *vector3); // ��������� ������������ ���� ��������
void hsNormal3dv(double *point1,double *point2,double *point3,double *vector); // ���������� ������� � ����������� ������������ 3-�� ������� �� �������� �� ����� ������
double hsCosinus3dv(double *vector1,double *vector2); // ������� ���� ����� ����� ���������

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