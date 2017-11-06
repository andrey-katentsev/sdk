//
// File: local_memory.cpp
// Description: resource handle for memory allocated from the heap (local)
// Created: January 26, 2014
// Author: Andrey A. Katentsev
//
// Copyright © Andrey A. Katentsev, 2014
//

#include "../../include/RAII/local_memory.h"

#include <stdexcept>

#include "../../include/keywords.h"

namespace KAA
{
	namespace RAII
	{
		local_memory::local_memory(const HLOCAL memory) :
		m_memory(memory)
		{
			if(nullptr == memory)
				throw std::invalid_argument(__FUNCTION__);
		}

		local_memory::~local_memory()
		{
			::LocalFree(m_memory);
		}

		local_memory::operator HLOCAL (void) const throw()
		{
			return m_memory;
		}
	}
}
