//
// FILE: hsControls.h
// DESCRIPTION: windows controls helper API declaration.
// CREATED: 24/05/2012
// AUTHOR: Andrey A. Katentsev
//
// COPYRIGHT © 2012, Hyperlink Software.
//

#pragma once

#include <vector>
#include <string>
#include <windows.h>

#pragma region Edit Control
HRESULT hsGetEditTextW(__in HWND hDlg, __in int nControlID, __out std::wstring& strText);
#pragma endregion

#pragma region Combo Box
#define HS_COMBOBOX_SEARCH_FROM_BEGINING (-1)
HRESULT hsGetComboTextW(__in HWND hDlg, __in int nControlID, __out std::wstring& strText);
HRESULT hsInitComboBoxW(__in HWND hDlg, __in int nControlID, __in const std::vector<std::wstring>& data);
#pragma endregion

#pragma region Common Controls
#pragma region List View
#define HS_LISTVIEW_NO_SELECTION_MARK (-1)
#define HS_LISTVIEW_SEARCH_FROM_BEGINING (-1)
#define HS_LISTVIEW_ITEM_NOT_FOUND (-1)
int hsListView_GetItemText(__in HWND hControl, __in int nItem, __in int nSubItem, __out std::wstring& strText, __in int nTextCchMax);
#pragma endregion
#pragma region Date and Time Picker
#define DateTime_Enable(hwndCtl, fEnable) EnableWindow((hwndCtl), (fEnable)) // just like <windowsx.h> API.

#pragma warning(disable:4480) // C4480: nonstandard extension used: specifying underlying type for enum 'hsESystemTimeFormat'.
typedef enum hsESystemTimeFormat : BYTE
{
	HS_STF_SHORT_DATE,// dd/MM/yyyy
	HS_STF_LONG_DATE, // dd MMMM YYYY
	HS_STF_SHORT_TIME,// mm:ss
	HS_STF_LONG_TIME, // HH:mm:ss
	HS_STF_FULL_TIME  // HH:mm:ss:milliseconds
} HS_SYSTEMTIMEFORMAT, *HS_PSYSTEMTIMEFORMAT;
#pragma warning(default:4480)

HRESULT hsSystemTimeToStringW(__in const SYSTEMTIME& tSystemTime, __in HS_SYSTEMTIMEFORMAT eFormat, __out std::wstring& wstrText);
HRESULT hsStringToSystemTimeW(__in const std::wstring& wstrText, __in HS_SYSTEMTIMEFORMAT eFormat, __out SYSTEMTIME& tSystemTime);
#pragma endregion
#pragma endregion