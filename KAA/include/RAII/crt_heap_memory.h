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
		class heap_memory
		{
		public:
			explicit heap_memory(void*);
			~heap_memory();

			operator void* (void) const noexcept;

		private:
			void* m_memory;

			heap_memory(const heap_memory&) = delete;
			heap_memory(heap_memory&&) = delete;
			heap_memory& operator = (const heap_memory&) = delete;
			heap_memory& operator = (heap_memory&&) = delete;
		};
	}
}
