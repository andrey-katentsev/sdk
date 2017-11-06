//
// File: convert.h
// Description: CRT wrappers (with Security Enhancements)
// Created: May 19, 2013
// Author: Andrey A. Katentsev
//
// Copyright (C) 2013, Hyperlink Software.
//

#include <string>

namespace KAA
{
	namespace convert
	{
		long to_long(const std::wstring& value);

		std::string to_string(const std::wstring&);

		std::wstring to_wstring(long value, int radix = 10);

		std::wstring to_wstring(const std::string&);
	}
}
