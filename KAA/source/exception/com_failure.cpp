//
// File: com_failure.cpp
// Description: exception class for component object model
// Created: May 25, 2013
// Author: Andrey A. Katentsev
//
// Copyright © Andrey A. Katentsev, 2013
//

#include "../../include/exception/com_failure.h"
#include "../../include/exception/windows_api_failure.h"
#include "../../include/RAII/local_memory.h"

//
//  HRESULTs are 32 bit values layed out as follows:
//
//   3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
//   1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
//  +-+-+-+-+-+---------------------+-------------------------------+
//  |S|R|C|N|r|    Facility         |               Code            |
//  +-+-+-+-+-+---------------------+-------------------------------+
//
//  where
//
//      S - Severity - indicates success/fail
//
//          0 - Success
//          1 - Fail (COERROR)
//
//      R - reserved portion of the facility code, corresponds to NT's
//              second severity bit.
//
//      C - reserved portion of the facility code, corresponds to NT's
//              C field.
//
//      N - reserved portion of the facility code. Used to indicate a
//              mapped NT status value.
//
//      r - reserved portion of the facility code. Reserved for internal
//              use. Used to indicate HRESULT values that are not status
//              values, but are instead message ids for display strings.
//
//      Facility - is the facility code
//
//      Code - is the facility's status code
//

namespace
{
	union com_error_t
	{
		HRESULT value;
		struct
		{
			HRESULT status_code : 16;
			HRESULT facility_code : 11;
			HRESULT reserved : 4;
			HRESULT severity : 1;
		} layout;
	};
}

namespace KAA
{
	com_failure::com_failure(std::wstring source, std::wstring description, const HRESULT error) :
	source(std::move(source)),
	description(std::move(description)),
	status_code(S_OK),
	facility_code(FACILITY_NULL),
	success(true)
	{
		com_error_t com_error = { 0 };
		com_error.value = error;
		status_code = com_error.layout.status_code;
		facility_code = com_error.layout.facility_code;
		success = com_error.layout.severity == 0 ? true : false;
	}

	com_failure::com_failure(std::wstring source, std::wstring description, const WORD status_code, const WORD facility_code, const bool success) :
	source(std::move(source)),
	description(std::move(description)),
	status_code(status_code),
	facility_code(facility_code),
	success(success)
	{}

	com_failure::operator HRESULT (void) const throw()
	{
		return get_error();
	}

	HRESULT com_failure::get_error(void) const throw()
	{
		com_error_t com_error = { 0 };
		com_error.layout.status_code = status_code;
		com_error.layout.facility_code = facility_code;
		com_error.layout.severity = success ? 0 : 1;
		return com_error.value;
	}

	std::wstring com_failure::iget_source(void) const
	{
		return source;
	}

	std::wstring com_failure::iget_description(void) const
	{
		return description;
	}

	std::wstring com_failure::iget_system_message(void) const
	{
		enum { predefined_language_order = 0 };
		const DWORD options = FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS;
		HLOCAL buffer;
		if(0 == ::FormatMessageW(options, nullptr, status_code, predefined_language_order, reinterpret_cast<LPWSTR>(&buffer), 0, nullptr))
		{
			const DWORD error = ::GetLastError();
			throw windows_api_failure(__FUNCTIONW__, L"Unable to format message.", error);
		}

		const KAA::RAII::local_memory acquired_memory(buffer);
		return std::wstring(reinterpret_cast<wchar_t*>(buffer));
	}
}
