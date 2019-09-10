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
		system_failure(std::wstring source, std::wstring description, errno_t);

		operator errno_t (void) const noexcept;

	private:
		std::wstring source;
		std::wstring description;
		errno_t error_code;

		std::wstring iget_source(void) const override;
		std::wstring iget_description(void) const override;
		std::wstring iget_system_message(void) const override;
	};
}
