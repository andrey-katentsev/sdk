//
// FILE: hsDialog.h
// DESCRIPTION: IDD_DIALOG procedure and message processing functions declaration.
// CREATED: 22/05/2012
// AUTHOR: Andrey A. Katentsev
//
// COPYRIGHT © 2012, Hyperlink Software.
//

#pragma once

#include <windows.h>

INT_PTR CALLBACK DialogProcedure(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);

namespace DDP
{
	void OnClose(HWND hDlg);
	BOOL OnInitDialog(HWND hDlg, HWND hFocus, LPARAM lParam);
	void OnCommand(HWND hDlg, int nID, HWND hControl, UINT uNotifyCode);
	void OnHotKey(HWND hDlg, int nHotKeyID, UINT uModifiers, UINT uVirtualKey);

	void ProcessMenuMessage(HWND hDlg, int nID);
	void ProcessAcceleratorMessage(HWND hDlg, int nID);
	void ProcessControlMessage(HWND hDlg, int nID, HWND hControl, UINT uNotifyCode);
}