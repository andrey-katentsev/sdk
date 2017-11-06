/* Designed and programmed by Hyperlink, 2007-2008. */
/* Copyright by Hyperlink */
/* Contacts: */
/* e-mail: hyperlink@inbox.ru */
/* UIN: 282757076 */

#ifndef HS_CONVERT_UTILITIES
#define HS_CONVERT_UTILITIES

#define HS_CONVERT_UTILITIES_VERSION 1.0

#include <stdio.h>
#include <ctype.h>
#include <string.h>

char* hsIntToChar(unsigned int number,char *buffer);

void hsStringToUpperCase(char *String);
void hsStringToLowerCase(char *String);

#endif