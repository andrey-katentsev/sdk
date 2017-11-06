#pragma once

#include <windows.h>

BOOL hsSystemTrayAdd(HWND hWnd,UINT uIconID,HICON hIcon,LPCTSTR szTip);
BOOL hsSystemTrayRemove(HWND hWnd,UINT uIconID);
BOOL hsSystemTrayModify(HWND hWnd,UINT uIconID,HICON hIcon,LPCTSTR szTip);