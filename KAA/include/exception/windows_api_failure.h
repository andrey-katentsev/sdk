//
// File: windows_api_failure.h
// Description: exception class for windows API
// Created: May 25, 2013
// Author: Andrey A. Katentsev
//
// Copyright � Andrey A. Katentsev, 2013
//

#pragma once

#include "failure.h"
#include <windows.h>

namespace KAA
{
	class windows_api_failure final : public failure
	{
	public:
		enum class severity_t
		{
			success,
			information,
			warning,
			error
		};

		windows_api_failure(std::string source, std::string description, long);
		windows_api_failure(std::string source, std::string description, DWORD);
		windows_api_failure(std::string source, std::string description, WORD status_code, WORD facility_code, severity_t severity, bool custom);

		operator DWORD (void) const noexcept;

	private:
		std::string source;
		std::string description;
		WORD status_code;
		WORD facility_code;
		severity_t failure_severity;
		bool custom;

		void parse_error(DWORD);
		DWORD get_error(void) const noexcept;

		std::string iget_source(void) const override;
		std::string iget_description(void) const override;
		std::string iget_system_message(void) const override;
	};
}
