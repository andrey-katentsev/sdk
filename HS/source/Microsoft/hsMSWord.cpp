//
// FILE: hsMSWord.cpp
// DESCRIPTION: access to Microsoft® Word COM server functions definition.
// CREATED: 04/06/2012
// AUTHOR: Andrey A. Katentsev
//
// COPYRIGHT © 2012, Hyperlink Software.
//

/*#include "C:\SDK\HS\include\hsMSWord.h"

HRESULT hsRunMSWord(Word::_ApplicationPtr* pptrMSWord, BOOL isVisible, BOOL isActivate)
{
	HRESULT hResult = E_FAIL;
	try
	{
		Word::_ApplicationPtr ptrMSWord(TEXT(HS_MSWORD_APPLICATION));

		(*pptrMSWord) = ptrMSWord;

		if(isVisible)
			ptrMSWord->Visible = VARIANT_TRUE;

		if(isActivate)
			hResult = ptrMSWord->Activate();
		else
			hResult = S_OK;
	}
	catch(_com_error& error)
	{
		hResult = error.Error();
	}
	return hResult;
}

HRESULT hsAddMSWordDocument(Word::_ApplicationPtr ptrMSWord, Word::_DocumentPtr* pptrDocument, const std::wstring& wstrFileName)
{
	HRESULT hResult = E_FAIL;
	try
	{
		const long nDocsCount = ptrMSWord->Documents->Count;

		Word::_DocumentPtr ptrDocument = ptrMSWord->Documents->Add(&_variant_t(wstrFileName.c_str()));

		if(nDocsCount < ptrMSWord->Documents->Count)
		{
			(*pptrDocument) = ptrDocument;
			hResult = S_OK;
		}
	}
	catch(_com_error& error)
	{
		hResult = error.Error();
	}
	return hResult;
}

// Range Object - Represents a contiguous area in a document. Each Range object is defined by a starting and ending character position.
HRESULT hsGetMSWordRange(Word::_DocumentPtr ptrDocument, Word::RangePtr* pptrRange, DWORD dwStart, DWORD dwEnd)
{
	HRESULT hResult = E_FAIL;
	try
	{
		_variant_t varStart(dwStart);
		_variant_t varEnd(dwEnd);
		Word::RangePtr ptrRange = ptrDocument->Range(&varStart, &varEnd);
		(*pptrRange) = ptrRange;
		hResult = S_OK;
	}
	catch(_com_error& error)
	{
		hResult = error.Error();
	}
	return hResult;
}

HRESULT hsGoToMSWordBookmark(Word::_DocumentPtr ptrDocument, Word::RangePtr* pptrBookmark, const std::wstring& wstrBookmarkName)
{
	HRESULT hResult = E_FAIL;
	Word::RangePtr ptrRange = NULL;
	try
	{
		hResult = hsGetMSWordRange(ptrDocument, reinterpret_cast<Word::RangePtr*>(&ptrRange));
		ptrRange = ptrRange->GoTo(&_variant_t(Word::wdGoToBookmark), &_variant_t(), &_variant_t(), &_variant_t(wstrBookmarkName.c_str()));
		(*pptrBookmark) = ptrRange;
		hResult = S_OK;
	}
	catch(_com_error& error)
	{
		hResult = error.Error();
	}
	return hResult;
}

// SUMMARY
//  NAME: hsUnknownMSWord
//  AUTHOR: Andrew A. Katentsev
//  PARAMS: pointer to Microsoft Word Application object;
//  RETURNS: standard HRESULT;
//  CREATED: 06/06/2012
//  PURPOSE: API function template;
//  NOTES: use this template as start point for your own new functions.
HRESULT hsUnknownMSWord(Word::_ApplicationPtr ptrMSWord)
{
	HRESULT hResult = E_FAIL;
	try
	{
		IUnknown* ptrUnknown = reinterpret_cast<IUnknown*>(&ptrMSWord);
		UNREFERENCED_PARAMETER(ptrUnknown);
		hResult = S_OK;
	}
	catch(_com_error& error)
	{
		hResult = error.Error();
	}
	return hResult;
}*/