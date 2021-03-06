//
// File: local_memory.h
// Description: resource handle for memory allocated from the heap (local)
// Created: January 26, 2014
// Author: Andrey A. Katentsev
//
// Copyright � Andrey A. Katentsev, 2014
//

#pragma once

#include <windows.h>

namespace KAA
{
	namespace RAII
	{
		class local_memory
		{
		public:
			explicit local_memory(HLOCAL);
			~local_memory();

			local_memory(const local_memory&) = delete;
			local_memory(local_memory&&) = delete;

			local_memory& operator = (const local_memory&) = delete;
			local_memory& operator = (local_memory&&) = delete;

			operator HLOCAL (void) const throw();

		private:
			HLOCAL m_memory;
		};
	}
}
