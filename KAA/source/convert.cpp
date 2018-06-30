//
// File: convert.cpp
// Description: CRT wrappers (with Security Enhancements)
// Created: May 19, 2013
// Author: Andrey A. Katentsev
//
// Copyright © Andrey A. Katentsev, 2013
//

#include "../include/convert.h"

#include <vector>

#include <cstdlib>

#include "../include/keywords.h"
#include "../include/exception/system_failure.h"
#include "../include/RAII/invalid_parameter_handler.h"

namespace
{
	void allow_execution(const wchar_t*, const wchar_t*, const wchar_t*, unsigned int, uintptr_t) { return; }

	// DEFECT: KAA: DRY violation.

	// THROWS: system_failure
	// SAFE GUARANTEE: strong
	// SIDE EFFECTS: -
	// RETURNS: the size in bytes of the converted string, including the null terminator
	size_t get_buffer_size(const std::wstring& string_to_convert)
	{
		const KAA::RAII::invalid_parameter_handler session(allow_execution);
		{
			size_t buffer_size = 0;
			const errno_t code = wcstombs_s(&buffer_size, nullptr, 0, string_to_convert.c_str(), 0);
			if(0 != code)
			{
				throw KAA::system_failure(__FUNCTIONW__, L"EXCEPTION: Unable to determine appropriate buffer size.", code);
			}

			return buffer_size;
		}
	}

	// THROWS: system_failure
	// SAFE GUARANTEE: strong
	// SIDE EFFECTS: -
	// RETURNS: the size in wide characters of the converted string, including the null terminator
	size_t get_buffer_size(const std::string& string_to_convert)
	{
		const KAA::RAII::invalid_parameter_handler session(allow_execution);
		{
			size_t buffer_size = 0;
			const errno_t code = mbstowcs_s(&buffer_size, nullptr, 0, string_to_convert.c_str(), 0);
			if(0 != code)
			{
				throw KAA::system_failure(__FUNCTIONW__, L"EXCEPTION: Unable to determine appropriate buffer size.", code);
			}

			return buffer_size;
		}
	}
}

namespace KAA
{
	namespace convert
	{
		// THROWS: -
		// SAFE GUARANTEE: strong
		// SIDE EFFECTS: set errno to ERANGE, EINVAL
		long to_long(const std::wstring& value)
		{
			return _wtol(value.c_str()); // DEFECT: KAA: error handling?
		}

		// THROWS: system_failure
		// SAFE GUARANTEE: strong
		// SIDE EFFECTS: -
		std::string to_string(const std::wstring& string_to_convert)
		{
			const RAII::invalid_parameter_handler session(allow_execution);
			{
				std::vector<char> buffer(get_buffer_size(string_to_convert), '\0');
				const errno_t code = wcstombs_s(nullptr, &buffer[0], buffer.size(), string_to_convert.c_str(), _TRUNCATE);
				if(0 != code)
				{
					throw system_failure(__FUNCTIONW__, L"EXCEPTION: Unable to convert wide string to multibyte string.", code);
				}

				return std::string(&buffer[0]);
			}
		}

		// THROWS: system_failure
		// SAFE GUARANTEE: strong
		// SIDE EFFECTS: -
		std::wstring to_wstring(long value, int radix)
		{
			RAII::invalid_parameter_handler session(allow_execution);
			{
				std::vector<wchar_t> buffer(sizeof(value) * 8 + 1, 0); // binary (radix = 2)
				const errno_t error = _ltow_s(value, &buffer[0], buffer.size(), radix);
				if(0 != error)
				{
					throw system_failure(__FUNCTIONW__, L"EXCEPTION: Unable to convert a long integer to a string.", error);
				}

				return std::wstring(&buffer[0]);
			}			
		}

		// THROWS: system_failure
		// SAFE GUARANTEE: strong
		// SIDE EFFECTS: -
		std::wstring to_wstring(const std::string& string_to_convert)
		{
			RAII::invalid_parameter_handler session(allow_execution);
			{
				std::vector<wchar_t> buffer(get_buffer_size(string_to_convert), L'\0');
				const errno_t code = mbstowcs_s(nullptr, &buffer[0], buffer.size(), string_to_convert.c_str(), _TRUNCATE);
				if(0 != code)
				{
					throw system_failure(__FUNCTIONW__, L"EXCEPTION: Unable to convert multibyte string to wide string.", code);
				}

				return std::wstring(&buffer[0]);
			}
		}
	}
}
