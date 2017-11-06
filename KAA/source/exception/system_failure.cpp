//
// File: system_failure.cpp
// Description: wrapper for system-level call error (CRT)
// Created: January 18, 2014
// Author: Andrey A. Katentsev
//
// Copyright © Andrey A. Katentsev, 2014
//

#include "../../include/exception/system_failure.h"
#include <vector>
#include "../../include/RAII/invalid_parameter_handler.h"

namespace
{
	void allow_execution(const wchar_t*, const wchar_t*, const wchar_t*, unsigned int, uintptr_t) { return; }
}

namespace KAA
{
	system_failure::system_failure(const std::wstring& source, const std::wstring& description, const errno_t error_code) :
	source(source),
	description(description),
	error_code(error_code)
	{}

	system_failure::operator errno_t (void) const
	{
		return error_code;
	}

	std::wstring system_failure::iget_source(void) const
	{
		return source;
	}

	std::wstring system_failure::iget_description(void) const
	{
		return description;
	}

	std::wstring system_failure::iget_system_message(void) const
	{
		const RAII::invalid_parameter_handler session(allow_execution);
		{
			std::vector<wchar_t> buffer(256, L'\0');
			const errno_t error = _wcserror_s(&buffer[0], buffer.size(), error_code);
			if(0 != error)
			{
				throw system_failure(__FUNCTIONW__, L"Unable to get a system error message.", error);
			}

			return std::wstring(&buffer[0]);
		}
	}
}
