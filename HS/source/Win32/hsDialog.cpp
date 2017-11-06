//
// FILE: hsDialog.cpp
// DESCRIPTION: IDD_DIALOG procedure and message processing functions definition.
// CREATED: 22/05/2012
// AUTHOR: Andrey A. Katentsev
//
// COPYRIGHT © 2012, Hyperlink Software.
//

#include <windows.h>
#include <windowsx.h>
//#include <commctrl.h> // link with: comctl32.lib
//#pragma comment(linker, "comctl32.lib")

#include "Resource.h"
#include "hsDialog.h"

#include "hsError.h"

// Typically, the dialog box procedure should return TRUE if it processed the message, and FALSE if it did not.
INT_PTR CALLBACK DialogProcedure(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	using namespace UDP;
	switch(uMsg)
	{
		HANDLE_MSG(hDlg, WM_CLOSE, OnClose);
		HANDLE_MSG(hDlg, WM_INITDIALOG, OnInitDialog);
		HANDLE_MSG(hDlg, WM_COMMAND, OnCommand);
		HANDLE_MSG(hDlg, WM_HOTKEY, OnHotKey);
	}
	return FALSE; // message not processed.
}

namespace UDP {
// If an application processes this message, it should return zero.
void OnClose(HWND hDlg)
{
	EndDialog(hDlg, HS_DLG_CLOSE);
	SetDlgMsgResult(hDlg, WM_CLOSE, HS_MSG_PROCESSED); // message processed.
}

// The dialog box procedure should return TRUE to direct the system to set the keyboard focus to the control specified by hFocus(wParam).
// Otherwise, it should return FALSE to prevent the system from setting the default keyboard focus. 
BOOL OnInitDialog(HWND hDlg, HWND hFocus, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(hDlg);
	UNREFERENCED_PARAMETER(hFocus);
	UNREFERENCED_PARAMETER(lParam);
	return TRUE;
}

// If an application processes this message, it should return zero.
void OnCommand(HWND hDlg, int nID, HWND hControl, UINT uNotifyCode)
{
	if(hControl)
		return ProcessControlMessage(hDlg, nID, hControl, uNotifyCode);

	switch(uNotifyCode)
	{
	case 0: return ProcessMenuMessage(hDlg, nID);
	case 1: return ProcessAcceleratorMessage(hDlg, nID);
	}
}

// No return value.
void OnHotKey(HWND hDlg, int nHotKeyID, UINT uModifiers, UINT uVirtualKey)
{
	UNREFERENCED_PARAMETER(hDlg);
	UNREFERENCED_PARAMETER(uVirtualKey);

	switch(nHotKeyID)
	{
	case IDHOT_SNAPDESKTOP:
	case IDHOT_SNAPWINDOW:
		{ ; } break;
	}

	switch(uModifiers)
	{
	case MOD_ALT:
	case MOD_CONTROL:
	case MOD_SHIFT:
	case MOD_WIN:
		{ ; } break;
	}
}

#pragma warning(disable:4065) // C4065: switch statement contains 'default' but no 'case' labels.
// If an application processes this message, it should return zero.
void ProcessAcceleratorMessage(HWND hDlg, int nID)
{
	switch(nID)
	{
	default: return; // message not processed.
	}
	SetDlgMsgResult(hDlg, WM_COMMAND, HS_MSG_PROCESSED); // message processed.
}
#pragma warning(default:4065)

#pragma warning(disable:4065) // C4065: switch statement contains 'default' but no 'case' labels.
// If an application processes this message, it should return zero.
void ProcessMenuMessage(HWND hDlg, int nID)
{
	switch(nID)
	{
	default: return; // message not processed.
	}
	SetDlgMsgResult(hDlg, WM_COMMAND, HS_MSG_PROCESSED); // message processed.
}
#pragma warning(default:4065)

#pragma warning(disable:4065) // C4065: switch statement contains 'default' but no 'case' labels.
// If an application processes this message, it should return zero.
void ProcessControlMessage(HWND hDlg, int nID, HWND hControl, UINT uNotifyCode)
{
	UNREFERENCED_PARAMETER(hControl);
	UNREFERENCED_PARAMETER(uNotifyCode);
	switch(nID)
	{
	default: return; // message not processed.
	}
	SetDlgMsgResult(hDlg, WM_COMMAND, HS_MSG_PROCESSED); // message processed.
} } // namespace UDP
#pragma warning(default:4065)