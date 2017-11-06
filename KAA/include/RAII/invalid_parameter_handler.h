//
// File: invalid_parameter_handler.h
// Description: resource handle for invalid argument handler (CRT)
// Created: January 31, 2014
// Author: Andrey A. Katentsev
//
// Copyright © Andrey A. Katentsev, 2014
//

#pragma once

#include <cstdlib>

namespace KAA
{
	namespace RAII
	{
		// THROWS: -
		// SAFE GUARANTEE: no throw
		// SIDE EFFECTS: -
		// PURPOSE: sets a function to be called when the CRT detects an invalid argument
		class invalid_parameter_handler
		{
		public:
			explicit invalid_parameter_handler(_invalid_parameter_handler);
			invalid_parameter_handler(const invalid_parameter_handler&) = delete;
			invalid_parameter_handler(invalid_parameter_handler&&) = delete;
			invalid_parameter_handler& operator = (const invalid_parameter_handler&) = delete;
			invalid_parameter_handler& operator = (invalid_parameter_handler&&) = delete;
			~invalid_parameter_handler();

		private:
			_invalid_parameter_handler previuos_handler;
		};
	}
}
