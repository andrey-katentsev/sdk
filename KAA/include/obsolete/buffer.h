//
// File: buffer.h
// Description: a/w buffer typedef and stuff
// Created: April 21, 2013
// Author: Andrey A. Katentsev
//
// Copyright (C) 2013, Hyperlink Software.
//

#include <vector>

namespace KAA
{
	namespace buffer
	{
		typedef std::vector<char> abuffer;
		typedef std::vector<wchar_t> wbuffer;

		template <class T, class A>
		inline typename std::vector<T, A>::value_type* cast_ptr(std::vector<T, A>& container)
		{ return &container[0]; }

		template <class T, class A>
		inline typename const std::vector<T, A>::value_type* cast_ptr(const std::vector<T, A>& container)
		{ return &container[0]; }
	}
}