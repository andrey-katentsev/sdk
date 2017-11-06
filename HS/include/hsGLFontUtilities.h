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

#define FONT_SIZE 30  // Размер шрифта
#define FONT_SCALE 0  // Растяжение вдоль оси вывода
#define ANGLE_OF_ESCAPEMENT 0 // Угол отношения
#define ORIENTATION_ANGLE 0   // Угол наклона
#define BOLD FW_BOLD  // Ширина шрифта
#define ITALIC TRUE   // Курсив
#define UNDERLINE FALSE  // Подчеркнутый
#define CROSSLINE FALSE  // Зачёркнутый

unsigned int hsRegisterFont(char *font_name,HDC hdc); // Создание и регистрация шрифта
void hsTextOut(unsigned int base,const char *string,...); // Вывод форматированной строки (использование аналогично printf();)
void hsDestroyFont(unsigned int base); // Уничтожение шрифта

#endif