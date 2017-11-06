//
// File: variable_argument_list.h
// Description: resource handle for variable argument list (CRT)
// Created: February 2, 2014
// Author: Andrey A. Katentsev
//
// Copyright © Andrey A. Katentsev, 2014
//

#pragma once

#include <cstdarg>

namespace KAA
{
	namespace RAII
	{
		// THROWS: -
		// SAFE GUARANTEE: no throw
		// SIDE EFFECTS: -
		class variable_argument_list
		{
		public:
			explicit variable_argument_list(va_list&);
			variable_argument_list(const variable_argument_list&) = delete;
			variable_argument_list(variable_argument_list&&) = delete;
			variable_argument_list& operator = (const variable_argument_list&) = delete;
			variable_argument_list& operator = (variable_argument_list&&) = delete;
			~variable_argument_list();

			operator va_list (void) const;

		private:
			va_list& handle;
		};
	}
}
