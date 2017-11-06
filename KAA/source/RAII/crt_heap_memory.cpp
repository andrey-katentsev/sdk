//
// File: crt_heap_memory.cpp
// Description: resource handle for memory allocated from the heap (CRT)
// Created: November 5, 2017
// Author: Andrey A. Katentsev
//
// Copyright © Andrey A. Katentsev, 2017
//

#include "../../include/RAII/crt_heap_memory.h"

#include <stdexcept>

namespace KAA
{
	namespace RAII
	{
		heap_memory::heap_memory(void* const memory) :
		m_memory(memory)
		{
			if(nullptr == memory)
				throw std::invalid_argument(__FUNCTION__);
		}

		heap_memory::~heap_memory()
		{
			::free(m_memory);
		}

		heap_memory::operator void* (void) const noexcept
		{
			return m_memory;
		}
	}
}
