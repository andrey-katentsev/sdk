//
// File: windows_api_failure.cpp
// Description: exception class for windows API
// Created: May 25, 2013
// Author: Andrey A. Katentsev
//
// Copyright � Andrey A. Katentsev, 2013
//

#include "../../include/exception/windows_api_failure.h"
#include "../../include/exception/operation_failure.h"

#include "../../include/unicode.h"
#include "../../include/RAII/local_memory.h"

#include <vector>

//
//  Values are 32 bit values laid out as follows:
//
//   3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
//   1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
//  +---+-+-+-----------------------+-------------------------------+
//  |Sev|C|R|     Facility          |               Code            |
//  +---+-+-+-----------------------+-------------------------------+
//
//  where
//
//      Sev - is the severity code
//
//          00 - Success
//          01 - Informational
//          10 - Warning
//          11 - Error
//
//      C - is the Customer code flag
//
//      R - is a reserved bit
//
//      Facility - is the facility code
//
//      Code - is the facility's status code
//

using namespace KAA::unicode;

namespace
{
	union win32_error_t
	{
		DWORD value;
		struct
		{
			DWORD status_code : 16;
			DWORD facility_code : 12;
			DWORD reserved : 1;
			DWORD customer_code_flag : 1;
			DWORD severity_code : 2;
		} layout;
	};

	KAA::windows_api_failure::severity_t to_severity(const WORD severity_code)
	{
		switch(severity_code)
		{
		case 0: return KAA::windows_api_failure::severity_t::success;
		case 1: return KAA::windows_api_failure::severity_t::information;
		case 2: return KAA::windows_api_failure::severity_t::warning;
		case 3: return KAA::windows_api_failure::severity_t::error;
		default:
			constexpr auto reason = KAA::operation_failure::status_code_t::invalid_argument;
			constexpr auto severity = KAA::operation_failure::severity_t::error;
			throw KAA::operation_failure { __FUNCTION__, "unknown severity code specified", reason, severity };
		}
	}

	WORD to_severity_code(const KAA::windows_api_failure::severity_t severity)
	{
		switch(severity)
		{
		case KAA::windows_api_failure::severity_t::success: return 0;
		case KAA::windows_api_failure::severity_t::information: return 1;
		case KAA::windows_api_failure::severity_t::warning: return 2;
		case KAA::windows_api_failure::severity_t::error: return 3;
		default:
			constexpr auto reason = KAA::operation_failure::status_code_t::invalid_argument;
			constexpr auto severity = KAA::operation_failure::severity_t::error;
			throw KAA::operation_failure { __FUNCTION__, "unknown failure severity specified", reason, severity };
		}
	}
}

namespace KAA
{
	windows_api_failure::windows_api_failure(std::string source, std::string description, const long error) : // defined in winerror.h
	source(std::move(source)),
	description(std::move(description)),
	status_code(ERROR_SUCCESS),
	facility_code(FACILITY_NULL),
	failure_severity(severity_t::success),
	custom(true)
	{
		parse_error(error);
	}

	windows_api_failure::windows_api_failure(std::string source, std::string description, const DWORD error) : // returned by ::GetLastError()
	source(std::move(source)),
	description(std::move(description)),
	status_code(ERROR_SUCCESS),
	facility_code(FACILITY_NULL),
	failure_severity(severity_t::success),
	custom(true)
	{
		parse_error(error);
	}

	windows_api_failure::windows_api_failure(std::string source, std::string description, const WORD status_code, const WORD facility_code, const severity_t severity, const bool custom) :
	source(std::move(source)),
	description(std::move(description)),
	status_code(status_code),
	facility_code(facility_code),
	failure_severity(severity),
	custom(custom)
	{}

	void windows_api_failure::parse_error(const DWORD error)
	{
		win32_error_t win32_api_error = { 0 };
		win32_api_error.value = error;
		status_code = win32_api_error.layout.status_code;
		facility_code = win32_api_error.layout.facility_code;
		failure_severity = to_severity(win32_api_error.layout.severity_code);
		custom = win32_api_error.layout.customer_code_flag == 1 ? true : false;
	}

	windows_api_failure::operator DWORD (void) const noexcept
	{
		return get_error();
	}

	DWORD windows_api_failure::get_error(void) const noexcept
	{
		win32_error_t win32_api_error = { 0 };
		win32_api_error.layout.status_code = status_code;
		win32_api_error.layout.facility_code = facility_code;
		win32_api_error.layout.severity_code = to_severity_code(failure_severity);
		win32_api_error.layout.customer_code_flag = custom ? 1 : 0;
		return win32_api_error.value;
	}

	std::string windows_api_failure::iget_source(void) const
	{
		return source;
	}

	std::string windows_api_failure::iget_description(void) const
	{
		return description;
	}

	std::string windows_api_failure::iget_system_message(void) const
	{
		enum { predefined_language_order = 0 };
		const DWORD options = FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS;
		std::vector<wchar_t> buffer(32 * 1024, L'\0'); // maximum supported buffer size - 64 KiB
		const DWORD length = ::FormatMessageW(options, nullptr, status_code, predefined_language_order, reinterpret_cast<LPWSTR>(buffer.data()), buffer.size(), nullptr);
		if(0 == length)
		{
			const DWORD error = ::GetLastError();
			throw windows_api_failure { __FUNCTION__, "cannot format a message string", error };
		}
		return to_UTF8(std::wstring(buffer.data(), length - 2)); // FIX: KAA: remove trailing \r\n
	}
}
