//
// File: windows_api_failure.h
// Description: exception class for windows API
// Created: May 25, 2013
// Author: Andrey A. Katentsev
//
// Copyright © Andrey A. Katentsev, 2013
//

#pragma once

#include "failure.h"
#include <windows.h>

namespace KAA
{
	class windows_api_failure final : public failure
	{
	public:
		enum severity_t
		{
			S_SUCCESS = 0,
			S_INFORMATION = 1,
			S_WARNING = 2,
			S_ERROR = 3
		};

		windows_api_failure(std::wstring source, std::wstring description, long);
		windows_api_failure(std::wstring source, std::wstring description, DWORD);
		windows_api_failure(std::wstring source, std::wstring description, WORD status_code, WORD facility_code, severity_t severity, bool is_custom);

		operator DWORD (void) const throw();

	private:
		std::wstring source;
		std::wstring description;
		WORD status_code;
		WORD facility_code;
		severity_t failure_severity;
		bool is_custom;

		void parse_error(DWORD);
		DWORD get_error(void) const throw();

		std::wstring iget_source(void) const override;
		std::wstring iget_description(void) const override;
		std::wstring iget_system_message(void) const override;
	};
}
