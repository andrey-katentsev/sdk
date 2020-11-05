//
// File: system_failure.h
// Description: wrapper for system-level call error (CRT)
// Created: January 18, 2014
// Author: Andrey A. Katentsev
//
// Copyright © Andrey A. Katentsev, 2014
//

#pragma once

#include <string>
#include <crtdefs.h>
#include "failure.h"

namespace KAA
{
	class system_failure final : public failure
	{
	public:
		system_failure(std::string source, std::string description, errno_t);

		operator errno_t (void) const noexcept;

	private:
		std::string source;
		std::string description;
		errno_t error_code;

		std::string iget_source(void) const override;
		std::string iget_description(void) const override;
		std::string iget_system_message(void) const override;
	};
}
