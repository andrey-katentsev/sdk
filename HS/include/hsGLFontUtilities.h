/* Designed and programmed by Hyperlink, 2007. */
/* Copyright by Hyperlink */
/* Contacts: */
/* E-mail: hyperlink@mail.cis.ru */
/* UIN: 282757076 */

#ifndef HS_OPENGL_FONT_UTILITIES
#define HS_OPENGL_FONT_UTILITIES

#define HS_OPENGL_FONT_UTILITIES_VERSION 1.0

#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <GL/gl.h>

#define FONT_SIZE 30  // ������ ������
#define FONT_SCALE 0  // ���������� ����� ��� ������
#define ANGLE_OF_ESCAPEMENT 0 // ���� ���������
#define ORIENTATION_ANGLE 0   // ���� �������
#define BOLD FW_BOLD  // ������ ������
#define ITALIC TRUE   // ������
#define UNDERLINE FALSE  // ������������
#define CROSSLINE FALSE  // �����������

unsigned int hsRegisterFont(char *font_name,HDC hdc); // �������� � ����������� ������
void hsTextOut(unsigned int base,const char *string,...); // ����� ��������������� ������ (������������� ���������� printf();)
void hsDestroyFont(unsigned int base); // ����������� ������

#endif