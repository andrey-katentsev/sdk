//
// FILE: hsControls.cpp
// DESCRIPTION: windows controls helper API definition.
// CREATED: 24/05/2012
// AUTHOR: Andrey A. Katentsev
//
// COPYRIGHT © 2012, Hyperlink Software.
//

#include "hsControls.h"

#include <windowsx.h> // regular controls API.
#include <commctrl.h> // common controls API.

#include <stdio.h> // swscanf_s();

#pragma region Edit Control
HRESULT hsGetEditTextW(HWND hDlg, int nControlID, std::wstring& strText)
{
	HRESULT hResult = E_NOTIMPL;
	HWND hControl = GetDlgItem(hDlg, nControlID);
	UINT uTextLength = Edit_GetTextLength(hControl);
	std::vector<wchar_t> vecBuffer(uTextLength + 1, 0);
	std::vector<wchar_t>::iterator index = vecBuffer.begin();
	Edit_GetText(hControl, &vecBuffer[0], vecBuffer.size());
	strText.assign(index, index + uTextLength); // index - valid iterator.
	return hResult;
}
#pragma endregion

#pragma region ComboBox
HRESULT hsGetComboTextW(HWND hDlg, int nControlID, std::wstring& strText)
{
	HRESULT hResult = E_NOTIMPL;
	HWND hControl = GetDlgItem(hDlg, nControlID);
	UINT uTextLength = ComboBox_GetTextLength(hControl);
	std::vector<wchar_t> vecBuffer(uTextLength + 1, 0);
	std::vector<wchar_t>::iterator index = vecBuffer.begin();
	ComboBox_GetText(hControl, &vecBuffer[0], vecBuffer.size());
	strText.assign(index, index + uTextLength); // index - valid iterator.
	return hResult;
}

HRESULT hsInitComboBoxW(HWND hDlg, int nControlID, const std::vector<std::wstring>& data)
{
	HRESULT hResult = E_NOTIMPL;
	std::vector<std::wstring>::size_type n = data.size();
	HWND hControl = GetDlgItem(hDlg, nControlID);
	ComboBox_ResetContent(hControl);
	for(std::vector<std::wstring>::size_type i = 0; i < n; i++)
		ComboBox_AddString(hControl, data[i].c_str());
	return hResult;
}
#pragma endregion

#pragma region Common Controls
#pragma region List View
int hsListView_GetItemText(HWND hControl, int nItem, int nSubItem, std::wstring& strText, int nTextCchMax)
{
	LVITEM item = {0};
	std::vector<wchar_t> vecBuffer(nTextCchMax + 1, 0);
	int nLength = 0;

	item.mask = LVIF_TEXT;
	item.iItem = nItem;
	item.iSubItem = nSubItem;
	item.cchTextMax = vecBuffer.size();
	item.pszText = &vecBuffer[0];

	nLength = SendMessage(hControl, LVM_GETITEMTEXT, nItem, reinterpret_cast<LPARAM>(&item));
	strText.assign(vecBuffer.begin(), vecBuffer.begin() + nLength);
	return nLength;
}
#pragma endregion
#pragma region Date and Time Picker
// length("31 сентября 2012") = 16;
// length("11:29:40 PM") = 11;
#define HS_STTS_BUFFER_CCH_SIZE 16
#define HS_STTS_SHORT_DATE_FORMAT L"dd/MM/yyyy"
#define HS_STTS_LONG_DATE_FORMAT L"dd MMMM yyyy"

HRESULT hsSystemTimeToStringW(const SYSTEMTIME& tSystemTime, HS_SYSTEMTIMEFORMAT eFormat, std::wstring& wstrText)
{
	HRESULT hResult = E_NOTIMPL;
	std::vector<wchar_t> vecBuffer(HS_STTS_BUFFER_CCH_SIZE + 1, 0);
	std::wstring wstrFormat;
	int nLength = 0;

	switch(eFormat)
	{
	case HS_STF_SHORT_DATE:
		{
			wstrFormat = HS_STTS_SHORT_DATE_FORMAT;
			nLength = GetDateFormatW(LOCALE_USER_DEFAULT, NULL, &tSystemTime, wstrFormat.c_str(), &vecBuffer[0], vecBuffer.size());
			hResult = S_OK;
		} break;
	case HS_STF_LONG_DATE:
		{
			wstrFormat = HS_STTS_LONG_DATE_FORMAT;
			nLength = GetDateFormatW(LOCALE_USER_DEFAULT, NULL, &tSystemTime, wstrFormat.c_str(), &vecBuffer[0], vecBuffer.size());
			hResult = S_OK;
		} break;
	case HS_STF_SHORT_TIME:
	case HS_STF_LONG_TIME:
	case HS_STF_FULL_TIME:
		{
			//GetTimeFormatW(LOCALE_USER_DEFAULT, LOCALE_NOUSEROVERRIDE | TIME_FORCE24HOURFORMAT, &tSystemTime, strFormat.c_str(), &vecBuffer[0], vecBuffer.size());
		} break;
	default: hResult = E_INVALIDARG;
	}

	if(SUCCEEDED(hResult))
		wstrText.assign(vecBuffer.begin(), vecBuffer.begin() + nLength);

	return hResult;
}

#define HS_STST_SHORT_DATE_FIELDS_CONVERTED 3
#define HS_STST_SHORT_DATE_FORMAT L"%hu/%hu/%hu"

HRESULT hsStringToSystemTimeW(const std::wstring& wstrText, HS_SYSTEMTIMEFORMAT eFormat, SYSTEMTIME& tSystemTime)
{
	HRESULT hResult = E_NOTIMPL;

	switch(eFormat)
	{
	case HS_STF_SHORT_DATE:
		{
			ZeroMemory(&tSystemTime, sizeof(tSystemTime));
			if(HS_STST_SHORT_DATE_FIELDS_CONVERTED == swscanf_s(wstrText.c_str(), HS_STST_SHORT_DATE_FORMAT, &tSystemTime.wDay, &tSystemTime.wMonth, &tSystemTime.wYear))
			{
				// tSystemTime.wDayOfWeek field adjustment.
				FILETIME tFileTime = {0};
				SystemTimeToFileTime(&tSystemTime, &tFileTime);
				FileTimeToSystemTime(&tFileTime, &tSystemTime);
				hResult = S_OK;
			}
			else
				hResult = S_FALSE;
		} break;
	case HS_STF_LONG_DATE:
		{	} break;
	case HS_STF_SHORT_TIME:
	case HS_STF_LONG_TIME:
	case HS_STF_FULL_TIME:
		{ } break;
	default: hResult = E_INVALIDARG;
	}

	return hResult;
}

#pragma endregion
#pragma endregion