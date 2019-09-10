//
// File: operation_failure.h
// Description: exception class for custom (non-system) error
// Created: February 24, 2014
// Author: Andrey A. Katentsev
//
// Copyright © Andrey A. Katentsev, 2014
//

#include "failure.h"

namespace KAA
{
	class operation_failure final : public failure
	{
	public:
		enum status_code_t
		{
			R_INVALID_ARGUMENT,
			R_INVALID_PARAMETER = R_INVALID_ARGUMENT,
			R_NOT_FOUND,
			R_NOT_IMPLEMENTED
		};

		enum severity_t
		{
			S_SUCCESS = 0,
			S_INFORMATION = 1,
			S_WARNING = 2,
			S_ERROR = 3
		};

		operation_failure(std::wstring source, std::wstring description, status_code_t, severity_t);

	private:
		std::wstring source;
		std::wstring description;
		status_code_t status_code;
		severity_t severity;

		std::wstring iget_source(void) const override;
		std::wstring iget_description(void) const override;
		std::wstring iget_system_message(void) const override;
	};
}
