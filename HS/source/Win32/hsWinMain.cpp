#define ISOLATION_AWARE_ENABLED 1
#define MANIFEST_RESOURCE_ID 2

//#define _WIN32_WINNT 0x501

#include <windows.h>
#include <commctrl.h>

#include "Resources.h"
#include "hsWindowProcedures.h"
#include "hsDialogProcedures.h"

// If the function succeeds, terminating when it receives a WM_QUIT message, it should return the exit value contained in that message's wParam parameter. If the function terminates before entering the message loop, it should return zero.
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPreviousInstance,LPSTR lpCmdLine,int nCmdShow)
{
 WNDCLASSEX WC;
 INITCOMMONCONTROLSEX ICC;

 HANDLE hIcon;
 HANDLE hCursor;

 HGDIOBJ hBackground;

 ATOM WindowClass;
 HWND hWnd;

 MSG Msg;

 int x,y,Width,Height;

 BOOL Status;
 DWORD ErrorCode;

 LPCTSTR ClassName=TEXT("hsWin32Class");
 LPCTSTR WindowName=TEXT("[Win32] Window Template");

 // Регистрируем дополнительные классы элементов управления.
 ICC.dwSize=sizeof(INITCOMMONCONTROLSEX);
 ICC.dwICC=ICC_WIN95_CLASSES;

 if(!InitCommonControlsEx(&ICC))
 {
  MessageBox(NULL,TEXT("InitCommonControlsEx()=FALSE"),TEXT("Инициализация"),MB_ICONERROR|MB_OK);
  return 0;
 }

 // Создаём модальное диалоговое окно.
 DialogBox(hInstance,MAKEINTRESOURCE(IDD_TEMPLATE),NULL,hsDialogProcedure);

 // Получаем указатели на ресурсы.
 hIcon=LoadImage(hInstance,MAKEINTRESOURCE(IDI_MAIN),IMAGE_ICON,0,0,LR_DEFAULTSIZE);
 hCursor=LoadImage(hInstance,MAKEINTRESOURCE(IDC_ARROW),IMAGE_CURSOR,0,0,LR_DEFAULTSIZE);
 hBackground=GetStockObject(BLACK_BRUSH);

 // Регистрируем класс окна.
 WC.cbSize=sizeof(WNDCLASSEX);         // Specifies the size, in bytes, of this structure.
 WC.style=CS_DROPSHADOW|CS_CLASSDC;    // Specifies the class style(s).
 WC.lpfnWndProc=hsWindowProcedure;     // Pointer to the window procedure.
 WC.cbClsExtra=0;                      // Specifies the number of extra bytes to allocate following the window-class structure.
 WC.cbWndExtra=0;                      // Specifies the number of extra bytes to allocate following the window instance.
 WC.hInstance=hInstance;               // Handle to the instance that contains the window procedure for the class.
 WC.hIcon=(HICON)hIcon;                // Handle to the class icon.
 WC.hCursor=(HCURSOR)hCursor;          // Handle to the class cursor.
 WC.hbrBackground=(HBRUSH)hBackground; // Handle to the class background brush.
 WC.lpszMenuName=NULL;                 // Pointer to a null-terminated character string that specifies the resource name of the class menu, as the name appears in the resource file.
 WC.lpszClassName=ClassName;           // Pointer to a null-terminated string or is an atom.
 WC.hIconSm=NULL;                      // Handle to a small icon that is associated with the window class.

 WindowClass=RegisterClassEx(&WC);

 if(0==WindowClass)
 {
  MessageBox(NULL,TEXT("RegisterClassEx()=FALSE"),TEXT("Инициализация"),MB_ICONERROR|MB_OK);
  return 0;
 }

 // Создаём окно.
 x=CW_USEDEFAULT;
 y=CW_USEDEFAULT; // If the y parameter is CW_USEDEFAULT, then the window manager calls ShowWindow() with the SW_SHOW flag after the window has been created.

 Width=CW_USEDEFAULT;
 Height=0;        // If the Width parameter is set to CW_USEDEFAULT, the system ignores Height.

 hWnd=CreateWindowEx(0,(LPCTSTR)MAKELONG(WindowClass,0),WindowName,WS_OVERLAPPED|WS_SYSMENU|WS_MINIMIZEBOX,x,y,Width,Height,NULL,NULL,hInstance,NULL);

 if(NULL==hWnd)
 {
  UnregisterClass((LPCTSTR)MAKELONG(WindowClass,0),hInstance);
  MessageBox(NULL,TEXT("CreateWindowEx()=FALSE"),TEXT("Инициализация"),MB_ICONERROR|MB_OK);
  return 0;
 }

 // Отображаем окно.
 //ShowWindow(hWnd,SW_SHOW);
 ShowWindow(hWnd,nCmdShow);
 //UpdateWindow(hWnd);

 // Цикл обработки сообщений.
 while(0!=(Status=GetMessage(&Msg,NULL,NULL,NULL))) // If the function retrieves the WM_QUIT message, the return value is zero.
 {
  if((-1)==Status) // Ошибка (Error).
  {
   // Handle the error and possibly exit.
   ErrorCode=GetLastError();
   //FormatMessage();

   MessageBox(NULL,TEXT("GetMessage()=FALSE"),TEXT("Цикл обработки сообщений"),MB_ICONERROR|MB_OK);
   DestroyWindow(hWnd);
   //UnregisterClass((LPCTSTR)MAKELONG(WindowClass,0),hInstance);
  }
  else
  {
   TranslateMessage(&Msg);
   DispatchMessage(&Msg);
  }
 }
 return (int)Msg.wParam;
}