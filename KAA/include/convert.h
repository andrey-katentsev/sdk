//
// File: convert.h
// Description: CRT wrappers (with Security Enhancements)
// Created: May 19, 2013
// Author: Andrey A. Katentsev
//
// Copyright © Andrey A. Katentsev, 2013
//

#include <string>

namespace KAA
{
	namespace convert
	{
		// If the first character is 0 and the second character is not 'x' or 'X', the string is interpreted as an octal integer.
		// If the first character is '0' and the second character is 'x' or 'X', the string is interpreted as a hexadecimal integer.
		// If the first character is '1' through '9', the string is interpreted as a decimal integer.
		long to_long_ex(const std::wstring& value) noexcept;
		unsigned long to_ulong_ex(const std::wstring& value) noexcept;

		long to_long(const std::wstring& value, int radix = 10);
		unsigned long to_ulong(const std::wstring& value, int radix = 10);

		std::wstring to_wstring(long value, int radix = 10);
		std::wstring to_wstring(unsigned long value, int radix = 10);

		std::string to_string(const std::wstring&);
		std::wstring to_wstring(const std::string&);
	}
}
