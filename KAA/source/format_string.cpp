//
// File: format_string.cpp
// Description: string format helper
// Created: April 24, 2013
// Author: Andrey A. Katentsev
//
// Copyright © Andrey A. Katentsev, 2013
//

#include "../include/format_string.h"

#include "../include/unicode.h"
#include "../include/exception/system_failure.h"
#include "../include/RAII/invalid_parameter_handler.h"
#include "../include/RAII/variable_argument_list.h"

#include <vector>
#include <cstdarg>

namespace
{
	void allow_execution(const wchar_t*, const wchar_t*, const wchar_t*, unsigned int, uintptr_t) { return; }
	// THROWS: system_failure
	// SAFE GUARANTEE: strong
	// SIDE EFFECTS: -
	std::wstring format_string(const std::wstring& format, va_list arguments)
	{
		const KAA::RAII::invalid_parameter_handler session(allow_execution);
		{
			const int formatted_string_lenght = _vscwprintf(format.c_str(), arguments);
			if(-1 == formatted_string_lenght)
			{
				const errno_t error = *_errno();
				throw KAA::system_failure { __FUNCTION__, "cannot determine the number of characters in the formatted string", error };
			}

			std::vector<wchar_t> buffer(formatted_string_lenght + 1, L'\0');
			if(formatted_string_lenght != vswprintf_s(buffer.data(), buffer.size(), format.c_str(), arguments))
			{
				const errno_t error = *_errno();
				throw KAA::system_failure { __FUNCTION__, "cannot write formatted output to the memory buffer", error };
			}
			return std::wstring(buffer.data(), formatted_string_lenght);
		}
	}
}

namespace KAA
{
	using namespace unicode;
	// THROWS: system_failure
	// SAFE GUARANTEE: strong
	// SIDE EFFECTS: -
	std::string format_string(const std::string format, ...) // passed by value due to va_list, va_start, va_end
	{
		va_list arguments;
		va_start(arguments, format);
		const RAII::variable_argument_list va_handler(arguments);
		return to_UTF8(::format_string(to_UTF16(format), arguments));
	}

	// THROWS: system_failure
	// SAFE GUARANTEE: strong
	// SIDE EFFECTS: -
	std::wstring format_string(const std::wstring format, ...) // passed by value due to va_list, va_start, va_end
	{
		va_list arguments;
		va_start(arguments, format);
		const RAII::variable_argument_list va_handler(arguments);
		return ::format_string(format, arguments);
	}
}
