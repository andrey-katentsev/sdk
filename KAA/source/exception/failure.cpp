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
	std::string failure::get_source(void) const
	{
		return iget_source();
	}

	std::string failure::get_description(void) const
	{
		return iget_description();
	}

	std::string failure::get_system_message(void) const
	{
		return iget_system_message();
	}
}
