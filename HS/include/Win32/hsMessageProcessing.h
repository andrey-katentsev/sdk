// <Контроль качества>

#pragma once

#include <windows.h>

// Функции обработчики сообщений (Message-Handling, Message-Processing Functions).
// Любая из этих функций должна возвращать TRUE, если она обработала сообщение и FALSE в противном случае (These functions should return TRUE, if it processes message and FALSE otherwise).

// Message-Processing Functions.
BOOL ProcessMenuMessage(HWND hWnd,WPARAM wParam);
BOOL ProcessAcceleratorMessage(HWND hWnd,WPARAM wParam);
BOOL ProcessControlMessage(HWND hWnd,WPARAM wParam,LPARAM lParam);
BOOL ProcessHotKeyMessage(HWND hWnd,WPARAM wParam,LPARAM lParam);

// Message-Handling Functions.
BOOL OnDestroy(void); // WM_DESTROY