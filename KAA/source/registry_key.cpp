//
// File: registry_key.cpp
// Description: retrieves and stores the data for the specified value name associated with an open registry key
// Created: February 12, 2014
// Author: Andrey A. Katentsev
//
// Copyright © Andrey A. Katentsev, 2014
//

#include "../include/registry_key.h"

namespace KAA
{
	namespace system
	{
		std::string registry_key::query_string_value(const std::string& name) const
		{
			return iquery_string_value(name);
		}

		void registry_key::set_string_value(const std::string& name, const std::string& data)
		{
			return iset_string_value(name, data);
		}

		uint32_t registry_key::query_dword_value(const std::string& name) const
		{
			return iquery_dword_value(name);
		}

		void registry_key::set_dword_value(const std::string& name, const uint32_t data)
		{
			return iset_dword_value(name, data);
		}
	}
}
