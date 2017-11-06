/* Designed and programmed by Hyperlink, 2008. */
/* Copyright by Hyperlink */
/* Contacts: */
/* e-mail: hyperlink@inbox.ru */
/* UIN: 282757076 */

/* Win32 notify handlers header file */

#ifndef HS_WIN32_NOTIFY_HANDLERS_HEADER
#define HS_WIN32_NOTIFY_HANDLERS_HEADER

#define DIRECTX

#include <windows.h>
#include "hsDirectSound.h"

#define HS_THREAD_OK    0
#define HS_THREAD_FALSE 1

DWORD hsDirectSoundNotifyHandle(LPHSDIRECTSOUND lpDS); // hsDirectSound notify handler: Loads data to sound buffer if necessary

#endif