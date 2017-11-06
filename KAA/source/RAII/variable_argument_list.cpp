//
// File: variable_argument_list.cpp
// Description: resource handle for variable argument list (CRT)
// Created: February 2, 2014
// Author: Andrey A. Katentsev
//
// Copyright © Andrey A. Katentsev, 2014
//

#include "../../include/RAII/variable_argument_list.h"

namespace KAA
{
	namespace RAII
	{
		variable_argument_list::variable_argument_list(va_list& handle) :
		handle(handle)
		{}

		variable_argument_list::operator va_list (void) const
		{
			return handle;
		}

		variable_argument_list::~variable_argument_list()
		{
			va_end(handle);
		}
	}
}
