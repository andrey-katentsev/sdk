//
// File: operation_failure.cpp
// Description: exception class for custom (non-system) error
// Created: February 24, 2014
// Author: Andrey A. Katentsev
//
// Copyright © Andrey A. Katentsev, 2014
//

#include "../../include/exception/operation_failure.h"
#include "../../include/exception/windows_api_failure.h"
#include "../../include/unicode.h"

using namespace KAA::unicode;

namespace
{
	KAA::windows_api_failure::severity_t to_windows_api_severity(const KAA::operation_failure::severity_t value)
	{
		switch(value)
		{
		case KAA::operation_failure::S_SUCCESS:
			return KAA::windows_api_failure::S_SUCCESS;
		case KAA::operation_failure::S_INFORMATION:
			return KAA::windows_api_failure::S_INFORMATION;
		case KAA::operation_failure::S_WARNING:
			return KAA::windows_api_failure::S_WARNING;
		case KAA::operation_failure::S_ERROR:
			return KAA::windows_api_failure::S_ERROR;
		default:
			throw KAA::operation_failure(__FUNCTIONW__, L"Unknown failure severity specified.", KAA::operation_failure::R_INVALID_PARAMETER, KAA::operation_failure::S_ERROR);
		}
	}

	WORD to_windows_api_status_code(const KAA::operation_failure::status_code_t value)
	{
		switch(value)
		{
		case KAA::operation_failure::R_INVALID_PARAMETER:
			return ERROR_INVALID_PARAMETER;
		case KAA::operation_failure::R_NOT_FOUND:
			return ERROR_NOT_FOUND;
		default:
			throw KAA::operation_failure(__FUNCTIONW__, L"Unknown status code specified.", KAA::operation_failure::R_INVALID_PARAMETER, KAA::operation_failure::S_ERROR);
		}
	}
}

namespace KAA
{
	operation_failure::operation_failure(std::wstring source, std::wstring description, const status_code_t status_code, const severity_t severity) :
	source(std::move(source)),
	description(std::move(description)),
	status_code(status_code),
	severity(severity)
	{}

	std::string operation_failure::iget_source(void) const
	{
		return to_UTF8(source);
	}

	std::string operation_failure::iget_description(void) const
	{
		return to_UTF8(description);
	}

	std::string operation_failure::iget_system_message(void) const
	{
		enum { custom_exception = true };
		const windows_api_failure error(source, description, to_windows_api_status_code(status_code), FACILITY_NULL, to_windows_api_severity(severity), custom_exception);
		return error.get_system_message();
	}
}
