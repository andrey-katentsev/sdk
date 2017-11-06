//
// File: invalid_parameter_handler.cpp
// Description: resource handle for invalid argument handler (CRT)
// Created: January 31, 2014
// Author: Andrey A. Katentsev
//
// Copyright © Andrey A. Katentsev, 2014
//

#include "../../include/RAII/invalid_parameter_handler.h"

namespace KAA
{
	namespace RAII
	{
		invalid_parameter_handler::invalid_parameter_handler(_invalid_parameter_handler new_handler) :
		previuos_handler(_set_invalid_parameter_handler(new_handler))
		{}

		invalid_parameter_handler::~invalid_parameter_handler()
		{
			_set_invalid_parameter_handler(previuos_handler);
		}
	}
}
