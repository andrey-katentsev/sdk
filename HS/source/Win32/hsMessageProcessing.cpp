// <Контроль качества>

#include <windows.h>
#include "Resources.h"
#include "hsVKey.h"
//#include "hsMessageProcessing.h"

#pragma region MESSAGES
// WM_DESTROY
BOOL OnDestroy(void)
{
 int ExitCode=0;
 PostQuitMessage(ExitCode);
 return TRUE;
}
#pragma endregion

#pragma region CONTROL
// LOWORD(wParam) - Идентификатор элемента управления (Control identifier).
// HIWORD(wParam) - Код уведомления (Control-defined notification code).
//        lParam  - Указатель на окно элемента управления (Handle to the control window).
BOOL ProcessControlMessage(HWND hWnd,WPARAM wParam,LPARAM lParam)
{
 UNREFERENCED_PARAMETER(hWnd);
 UNREFERENCED_PARAMETER(lParam);

 switch(LOWORD(wParam))
 {
 case IDC_OK_BUTTON:
  {
   CloseWindow(hWnd);
   return TRUE;
  } break;
 }
 return FALSE;
}
#pragma endregion

#pragma region ACCELERATOR
// LOWORD(wParam) - Идентификатор акселератора (Accelerator identifier).
// HIWORD(wParam) - 1::const;
//        lParam  - 0::const;
BOOL ProcessAcceleratorMessage(HWND hWnd,WPARAM wParam)
{
 UNREFERENCED_PARAMETER(hWnd);
 UNREFERENCED_PARAMETER(wParam);
 return FALSE;
}
#pragma endregion

#pragma region MENU
// LOWORD(wParam) - Идентификатор элемента меню (Menu identifier).
// HIWORD(wParam) - 0::const;
//        lParam  - 0::const;
BOOL ProcessMenuMessage(HWND hWnd,WPARAM wParam)
{
 UNREFERENCED_PARAMETER(hWnd);
 
 switch(LOWORD(wParam))
 {
 case IDC_CLOSE_MENU:
  {
   SendMessage(hWnd,WM_CLOSE,0,0);
   return TRUE;
  } break;
 }
 return FALSE;
}
#pragma endregion

#pragma region HOTKEYS
//        wParam  - (Specifies the identifier of the hot key that generated the message).
// LOWORD(lParam) - (The low-order word specifies the keys that were to be pressed in combination with the key specified by the high-order word to generate the WM_HOTKEY message).
// HIWORD(lParam) - (The high-order word specifies the virtual key code of the hot key).
BOOL ProcessHotKeyMessage(HWND hWnd,WPARAM wParam,LPARAM lParam)
{
 UNREFERENCED_PARAMETER(hWnd);
 switch(wParam)
 {
 case IDHOT_SNAPDESKTOP:
 case IDHOT_SNAPWINDOW:
 case HK_COPY:
 case HK_PASTE:
  {
   // Do something.
  } break;
 }

 switch(LOWORD(lParam))
 {
 case MOD_ALT:
 case MOD_CONTROL:
 case MOD_SHIFT:
 case MOD_WIN:
  {
   // Do something.
  } break;
 }
 return FALSE;
}
#pragma endregion