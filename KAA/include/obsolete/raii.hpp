//
// File: raii.hpp
// Description: resource acquisition is initialization (RAII) helpers
// Created: May 25, 2013
// Author: Andrey A. Katentsev
//
// Copyright (C) 2013, Hyperlink Software.
//

namespace KAA
{
	namespace RAII
	{
		template<class P, class R>
		class CMemoryPointer
		{
		public:
			typedef R (__stdcall *free_function_t)(P);

			CMemoryPointer(P pointer, free_function_t function) :
			m_pointer(pointer),
			m_function(function)
			{}

			~CMemoryPointer()
			{
				(*m_function)(m_pointer);
			}

		private:
			P m_pointer;
			free_function_t m_function;
		};
	} // namespace RAII
} // namespace KAA