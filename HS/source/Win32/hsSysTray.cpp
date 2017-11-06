#include "hsSysTray.h"

#include <strsafe.h>

BOOL hsSystemTrayAdd(HWND hWnd,UINT uIconID,HICON hIcon,LPCTSTR szTip)
{
 NOTIFYICONDATA NID;

 SecureZeroMemory(&NID,sizeof(NOTIFYICONDATA));

 NID.cbSize=sizeof(NOTIFYICONDATA);
 NID.hWnd=hWnd;
 NID.uID=uIconID;
 NID.uFlags=NIF_ICON|NIF_TIP|NIF_MESSAGE;
 NID.uCallbackMessage=WM_USER;
 NID.hIcon=hIcon;
 StringCchCopy(NID.szTip,128,szTip);

 return Shell_NotifyIcon(NIM_ADD,&NID);
}

BOOL hsSystemTrayRemove(HWND hWnd,UINT uIconID)
{
 NOTIFYICONDATA NID;

 SecureZeroMemory(&NID,sizeof(NOTIFYICONDATA));

 NID.cbSize=sizeof(NOTIFYICONDATA);
 NID.hWnd=hWnd;
 NID.uID=uIconID;

 return Shell_NotifyIcon(NIM_DELETE,&NID);
}

BOOL hsSystemTrayModify(HWND hWnd,UINT uIconID,HICON hIcon,LPCTSTR szTip)
{
 NOTIFYICONDATA NID;

 SecureZeroMemory(&NID,sizeof(NOTIFYICONDATA));

 NID.cbSize=sizeof(NOTIFYICONDATA);
 NID.hWnd=hWnd;
 NID.uID=uIconID;
 NID.uFlags=NIF_MESSAGE;
 NID.uCallbackMessage=WM_USER;

 if(hIcon!=NULL)
 {
  NID.hIcon=hIcon;
  NID.uFlags|=NIF_ICON;
 }

 if(szTip!=NULL)
 {
  NID.uFlags|=NIF_TIP;
  StringCchCopy(NID.szTip,128,szTip);
 }

 return Shell_NotifyIcon(NIM_MODIFY,&NID);
}