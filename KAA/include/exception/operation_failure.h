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
		enum class status_code_t
		{
			invalid_argument,
			invalid_parameter = invalid_argument,
			not_found,
			not_implemented
		};

		enum class severity_t
		{
			success,
			information,
			warning,
			error
		};

		operation_failure(std::string source, std::string description, status_code_t, severity_t);

	private:
		std::string source;
		std::string description;
		status_code_t status_code;
		severity_t severity;

		std::string iget_source(void) const override;
		std::string iget_description(void) const override;
		std::string iget_system_message(void) const override;
	};
}
