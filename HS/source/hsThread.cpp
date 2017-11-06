//
// File: hsThread.cpp
// Description: declaration of HS::CreateThread function for thread-safe use of Standard C++ Library.
// Created: 4/15/2012
// Author: Andrey A. Katentsev
//
// Copyright (c) 2012, Hyperlink Software.
//

#include "hsThread.h"
#include <process.h>

// using namespace HS;

typedef unsigned (__stdcall *start_routine_t)(void*);

HANDLE HS::CreateThread(LPSECURITY_ATTRIBUTES lpThreadAttributes,
																								SIZE_T dwStackSize,
																								LPTHREAD_START_ROUTINE lpStartAddress,
																								LPVOID lpParameter,
																								DWORD dwCreationFlags,
																								LPDWORD lpThreadId)
{
	void* security = reinterpret_cast<void*>(lpThreadAttributes);
	unsigned stack_size = static_cast<unsigned>(dwStackSize);
	start_routine_t start_address = reinterpret_cast<start_routine_t>(lpStartAddress);
	void* parameter = reinterpret_cast<void*>(lpParameter);
	unsigned initflag = static_cast<unsigned>(dwCreationFlags);
	unsigned* thread_id = reinterpret_cast<unsigned*>(lpThreadId);
	return reinterpret_cast<HANDLE>(_beginthreadex(security, stack_size, start_address, parameter, initflag, thread_id));
}

VOID HS::ExitThread(DWORD dwExitCode)
{
	_endthreadex(static_cast<unsigned>(dwExitCode));
}