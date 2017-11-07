//
// File: crt_heap_memory.h
// Description: resource handle for memory allocated from the heap (CRT)
// Created: November 5, 2017
// Author: Andrey A. Katentsev
//
// Copyright © Andrey A. Katentsev, 2017
//

#pragma once

namespace KAA
{
	namespace RAII
	{
		class crt_heap_memory
		{
		public:
			explicit crt_heap_memory(void*);
			~crt_heap_memory();

			operator void* (void) const noexcept;

		private:
			void* m_memory;

			crt_heap_memory(const crt_heap_memory&) = delete;
			crt_heap_memory(crt_heap_memory&&) = delete;
			crt_heap_memory& operator = (const crt_heap_memory&) = delete;
			crt_heap_memory& operator = (crt_heap_memory&&) = delete;
		};
	}
}
