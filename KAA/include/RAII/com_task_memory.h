//
// File: com_task_memory.h
// Description: resource handle for component object model task memory
// Created: January 26, 2014
// Author: Andrey A. Katentsev
//
// Copyright © Andrey A. Katentsev, 2014
//

#pragma once

namespace KAA
{
	namespace RAII
	{
		class com_task_memory
		{
		public:
			explicit com_task_memory(void*);
			~com_task_memory();

			operator void* (void) const throw();

		private:
			void* m_memory;

			// FUTURE: C++11: move semantics, = delete.
			com_task_memory(const com_task_memory&);
			com_task_memory& operator = (const com_task_memory&);
		};
	}
}
