/* Designed and programmed by Hyperlink, 2007-2008. */
/* Copyright by Hyperlink */
/* Contacts: */
/* E-mail: hyperlink@mail.cis.ru */
/* UIN: 282757076 */

#include "hs_vector_utilities.h"

/* Двумерное пространство */
/* Функции типа double */
int hsNormalize2dv(double *vector)
{
	double ax=sqrt(vector[0]*vector[0]+vector[1]*vector[1]);
	if(ax==0)
		return HS_NULLVECTOR;
	vector[0]/=ax;
	vector[1]/=ax;
	return HS_SUCCESS;
}

/* Трёхмерное пространство */
/* Функции типа float */
float hsScalar3fv(float *vector1,float *vector2)
{
	return vector1[0]*vector2[0]+vector1[1]*vector2[1]+vector1[2]*vector2[2];
}

float hsModule3fv(float *vector)
{
	return sqrt(vector[0]*vector[0]+vector[1]*vector[1]+vector[2]*vector[2]);
}

int hsNormalize3fv(float *vector)
{
	float ax=sqrt(vector[0]*vector[0]+vector[1]*vector[1]+vector[2]*vector[2]);
	if(ax==0)
		return HS_NULLVECTOR;
	vector[0]/=ax;
	vector[1]/=ax;
	vector[2]/=ax;
	return HS_SUCCESS;
}

void hsVector3fv(float *vector1,float *vector2,float *vector3)
{
	vector3[0]=vector1[1]*vector2[2]-vector2[1]*vector1[2];
	vector3[1]=vector1[2]*vector2[0]-vector2[2]*vector1[0];
	vector3[2]=vector1[0]*vector2[1]-vector2[0]*vector1[1];
}

void hsNormal3fv(float *point1,float *point2,float *point3,float *vector)
{
	float vector1[3],vector2[3];
  register unsigned int cx;
	for(cx=0;cx<3;cx++)
	{
		vector1[cx]=point1[cx]-point2[cx];
		vector2[cx]=point2[cx]-point3[cx];
	}
	hsVector3fv(vector1,vector2,vector);
}

float hsCosinus3fv(float *vector1,float *vector2)
{
	float ax,bx,cx;
	ax=(vector1[0]*vector2[0]+vector1[1]*vector2[1]+vector1[2]*vector2[2]);
	bx=sqrt(vector1[0]*vector1[0]+vector1[1]*vector1[1]+vector1[2]*vector1[2]);
	cx=sqrt(vector2[0]*vector2[0]+vector2[1]*vector2[1]+vector2[2]*vector2[2]);
	return ax/(bx*cx);
}

/* Функции типа double */
double hsScalar3dv(double *vector1,double *vector2)
{
	return vector1[0]*vector2[0]+vector1[1]*vector2[1]+vector1[2]*vector2[2];
}

double hsModule3dv(double *vector)
{
	return sqrt(vector[0]*vector[0]+vector[1]*vector[1]+vector[2]*vector[2]);
}

int hsNormalize3dv(double *vector)
{
	double ax=sqrt(vector[0]*vector[0]+vector[1]*vector[1]+vector[2]*vector[2]);
	if(ax==0)
		return HS_NULLVECTOR;
	vector[0]/=ax;
	vector[1]/=ax;
	vector[2]/=ax;
	return HS_SUCCESS;
}

void hsVector3dv(double *vector1,double *vector2,double *vector3)
{
	vector3[0]=vector1[1]*vector2[2]-vector2[1]*vector1[2];
	vector3[1]=vector1[2]*vector2[0]-vector2[2]*vector1[0];
	vector3[2]=vector1[0]*vector2[1]-vector2[0]*vector1[1];
}

void hsNormal3dv(double *point1,double *point2,double *point3,double *vector)
{
	double vector1[3],vector2[3];
  register unsigned int cx;
	for(cx=0;cx<3;cx++)
	{
		vector1[cx]=point1[cx]-point2[cx];
		vector2[cx]=point2[cx]-point3[cx];
	}
	hsVector3dv(vector1,vector2,vector);
}

double hsCosinus3dv(double *vector1,double *vector2)
{
	double ax,bx,cx;
	ax=(vector1[0]*vector2[0]+vector1[1]*vector2[1]+vector1[2]*vector2[2]);
	bx=sqrt(vector1[0]*vector1[0]+vector1[1]*vector1[1]+vector1[2]*vector1[2]);
	cx=sqrt(vector2[0]*vector2[0]+vector2[1]*vector2[1]+vector2[2]*vector2[2]);
	return ax/(bx*cx);
}