//
// File: com_task_memory.cpp
// Description: resource handle for component object model task memory
// Created: January 26, 2014
// Author: Andrey A. Katentsev
//
// Copyright © Andrey A. Katentsev, 2014
//

#include "../../include/RAII/com_task_memory.h"
#include "../../include/exception/com_failure.h"

#include <objbase.h>

namespace KAA
{
	namespace RAII
	{
		com_task_memory::com_task_memory(void* memory) :
		m_memory(memory)
		{
			if(nullptr == memory)
			{
				throw KAA::com_failure(__FUNCTIONW__, L"Unable to allocate a block of task memory.", E_OUTOFMEMORY); // NOTE: KAA: see CoTaskMemAlloc return value (MSDN)
			}
		}

		com_task_memory::~com_task_memory()
		{
			::CoTaskMemFree(m_memory);
		}

		com_task_memory::operator void* (void) const throw()
		{
			return m_memory;
		}
	}
}
