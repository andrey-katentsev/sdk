//
// File: critical_section.cpp
// Description: synchronization point
// Created: July 20, 2018
// Author: Andrey A. Katentsev
//
// Copyright © Andrey A. Katentsev, 2018
//

#include "../include/critical_section.h"
#include "../include/exception/windows_api_failure.h"

namespace KAA
{
	namespace synchronization
	{
		critical_section::critical_section() : mutex { 0 }
		{
			::InitializeCriticalSection(&mutex);
		}

		critical_section::critical_section(const unsigned int spin_count, const bool debug) : mutex { 0 }
		{
			if (0 == ::InitializeCriticalSectionEx(&mutex, spin_count, debug ? 0 : CRITICAL_SECTION_NO_DEBUG_INFO))
			{
				const auto code = ::GetLastError();
				throw windows_api_failure { __FUNCTION__, "cannot initialize a critical section object", code };
			}
		}
		
		critical_section::~critical_section()
		{
			::DeleteCriticalSection(&mutex);
		}

		void critical_section::iseize(void)
		{
			// MSDN: this function can raise EXCEPTION_POSSIBLE_DEADLOCK if a wait operation on the critical section times out.
			::EnterCriticalSection(&mutex);
		}

		void critical_section::irelease(void)
		{
			::LeaveCriticalSection(&mutex);
		}
	}
}
