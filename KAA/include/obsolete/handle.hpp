//
// File: .\RAII\handle.hpp
// Description: handle managers
// Created: May 26, 2013
// Author: Andrey A. Katentsev
//
// Copyright (C) 2013, Hyperlink Software.
//

#pragma once

namespace KAA
{
	namespace RAII
	{
		// REMARKS: R should not throws any exceptions
		// THROWS: depends on T (no throw : T, R - built-in types)
		// SAFE GUARANTEE: depends on T, strong (no fail : T, R - built-in types)
		// SIDE EFFECTS: depends on T, R (none: T, R - built-in types)
		template<class T, class R>
		class handle
		{
		public:
			typedef R (*close_handle_function)(T);

			handle(T resource_handle, close_handle_function release_function) :
			m_handle(resource_handle),
			m_close_handle(release_function)
			{}

			~handle()
			{
				(*m_close_handle)(m_handle);
			}

			operator T (void) const
			{
				return m_handle;
			}

		private:
			T m_handle;
			close_handle_function m_close_handle;

			handle(const handle&);
			handle& operator = (const handle&);

			#if(1500 < _MSC_VER)
			handle(handle&&);
			handle& operator = (handle&&);
			#endif
		};
	}
}