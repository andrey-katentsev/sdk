//
// File: failure.h
// Description: base exception class type
// Created: May 16, 2013
// Author: Andrey A. Katentsev
//
// Copyright © Andrey A. Katentsev, 2013
//

#pragma once

#include <string>

namespace KAA
{
	class failure
	{
	public:
		virtual ~failure() = default;

		std::wstring get_source(void) const;
		std::wstring get_description(void) const;
		std::wstring get_system_message(void) const;

	private:
		virtual std::wstring iget_source(void) const = 0;
		virtual std::wstring iget_description(void) const = 0;
		virtual std::wstring iget_system_message(void) const = 0;
	};
}
