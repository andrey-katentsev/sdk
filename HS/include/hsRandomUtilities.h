/* Designed and programmed by Hyperlink, 2007. */
/* Copyright by Hyperlink */
/* Contacts: */
/* E-mail: hyperlink@mail.cis.ru */
/* UIN: 282757076 */

/* ��������� ������� ������������ ��������������� ����� */

#ifndef HS_RANDOM_UTILITIES
#define HS_RANDOM_UTILITIES

#define HS_RADNOM_UTILITIES_VERSION 1.0.1

#include <stdlib.h>
#include <limits.h>
#include <windows.h>

#define HS_RANDOM_MAX RAND_MAX

int hsRandomA(int a); // ���������� ��������������� ����� �� ��������� [0,a]
int hsRandomAB(int a,int b); // ���������� ��������������� ����� �� ��������� [a,b]

#endif