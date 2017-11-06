// <�������� ��������>

#pragma once

#include <windows.h>

// ������� ����������� ��������� (Message-Handling, Message-Processing Functions).
// ����� �� ���� ������� ������ ���������� TRUE, ���� ��� ���������� ��������� � FALSE � ��������� ������ (These functions should return TRUE, if it processes message and FALSE otherwise).

// Message-Processing Functions.
BOOL ProcessMenuMessage(HWND hWnd,WPARAM wParam);
BOOL ProcessAcceleratorMessage(HWND hWnd,WPARAM wParam);
BOOL ProcessControlMessage(HWND hWnd,WPARAM wParam,LPARAM lParam);
BOOL ProcessHotKeyMessage(HWND hWnd,WPARAM wParam,LPARAM lParam);

// Message-Handling Functions.
BOOL OnDestroy(void); // WM_DESTROY