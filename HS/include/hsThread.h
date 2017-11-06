//
// File: hsThread.h
// Description: declaration of HS::CreateThread function for thread-safe use of Standard C++ Library.
// Created: 4/15/2012
// Author: Andrey A. Katentsev
//
// Copyright (c) 2012, Hyperlink Software.
//

#pragma once

#include <windows.h>
//#include <WinNT.h> // HANDLE
//#include <WinDef.h> // WINAPI, LPVOID, DWORD, LPDWORD
//#include <BaseTsd.h> // SIZE_T
//#include <WinBase.h> // LPSECURITY_ATTRIBUTES, LPTHREAD_START_ROUTINE

namespace HS
{
	HANDLE CreateThread(LPSECURITY_ATTRIBUTES lpThreadAttributes, SIZE_T dwStackSize, LPTHREAD_START_ROUTINE lpStartAddress, LPVOID lpParameter, DWORD dwCreationFlags, LPDWORD lpThreadId);
	VOID ExitThread(DWORD dwExitCode);
}