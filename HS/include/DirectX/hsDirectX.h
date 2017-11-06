/* Designed and programmed by Hyperlink, 2008. */
/* Copyright by Hyperlink */
/* Contacts: */
/* e-mail: hyperlink@inbox.ru */
/* UIN: 282757076 */

/* DirectX MACROS header file */

#ifndef HS_DIRECTX_MACROS
#define HS_DIRECTX_MACROS

#define DIRECTX

#include <WinError.h>

#define CHECK_ACCESS(Pointer) if(Pointer==NULL){return S_FALSE;}
#define PROCESS_RESULT(hResult) if(FAILED((HRESULT)hResult)){return (HRESULT)hResult;}

#define SET_IN_RANGE(Value,MIN,MAX) Value=(Value<MIN)?MIN:Value;Value=(Value>MAX)?MAX:Value;

#endif