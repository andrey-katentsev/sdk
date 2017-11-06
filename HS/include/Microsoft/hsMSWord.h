//
// FILE: hsMSWord.h
// DESCRIPTION: access to Microsoft® Word COM server functions declaration.
// CREATED: 04/06/2012
// AUTHOR: Andrey A. Katentsev
//
// COPYRIGHT © 2012, Hyperlink Software.
//

#pragma once

#include <string>
#include <windows.h>

//#include <comutil.h> // link with: comsuppw.lib or comsuppwd.lib
//#pragma comment(lib, "comsuppw.lib")
//#pragma comment(lib, "comsuppwd.lib")

#define HS_MSWORD_APPLICATION "Word.Application"

// Incorporate information from a type library.
//#define Uses_MSO2003
#define Uses_MSO2007
//#define Uses_MSO2010
//#define Uses_MSO2012

// Microsoft® Office 2003 ..\\OFFICE11
// Microsoft® Office 2007 ..\\OFFICE12
// Microsoft® Office 2010 ..\\OFFICE13
// Microsoft® Office 2012 ..\\OFFICE14

//#pragma warning(disable:)
#import "C:\Program Files\Common Files\Microsoft Shared\Office12\MSO.DLL"
#import "C:\Program Files\Common Files\Microsoft Shared\VBA\VBA6\VBE6EXT.OLB"
#import "C:\Program Files\Microsoft Office\Office12\MSWORD.OLB" rename("ExitWindows", "_ExitWindows")
#import "C:\Program Files\Common Files\Microsoft Shared\DAO\DAO360.DLL" rename("EOF", "EndOfFile") rename("BOF", "BegOfFile")
//#pragma warning(default:)

// CLASS DECLARATION
//  NAME: имя класса
//  AUTHOR: имя автора
//  CREATED: дата создания
//  PURPOSE: назначение
//  LIMITATIONS: известные ограничения
typedef class CMSWord
{
public:
	HRESULT RunMSWord(const std::wstring& wstrFileName = std::wstring());

private:
	Word::_ApplicationPtr m_ptrWordApplication;
} HS_MSWORD, *HS_PMSWORD;

// API
HRESULT hsRunMSWord(__out Word::_ApplicationPtr* pptrMSWord, __in BOOL isVisible = TRUE, __in BOOL isActivate = TRUE);
HRESULT hsAddMSWordDocument(__in Word::_ApplicationPtr ptrMSWord, __out Word::_DocumentPtr* pptrDocument, __in const std::wstring& wstrFileName = std::wstring());

HRESULT hsGoToMSWordBookmark(__in Word::_DocumentPtr ptrDocument, __out Word::RangePtr* pptrBookmark, __in const std::wstring& wstrBookmarkName);
HRESULT hsGetMSWordRange(__in Word::_DocumentPtr ptrDocument, __out Word::RangePtr* pptrRange, __in DWORD dwStart = 0, __in DWORD dwEnd = 0);

HRESULT hsUnknownMSWord(__in Word::_ApplicationPtr ptrMSWord);