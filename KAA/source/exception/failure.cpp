//
// File: failure.cpp
// Description: base exception class type
// Created: May 16, 2013
// Author: Andrey A. Katentsev
//
// Copyright © Andrey A. Katentsev, 2013
//

#include "../../include/exception/failure.h"

namespace KAA
{
	std::wstring failure::get_source(void) const
	{
		return iget_source();
	}

	std::wstring failure::get_description(void) const
	{
		return iget_description();
	}

	std::wstring failure::get_system_message(void) const
	{
		return iget_system_message();
	}
}
