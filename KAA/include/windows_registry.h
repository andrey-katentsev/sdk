//
// File: windows_registry.h
// Description: the registry is a system-defined database in which applications and system components store and retrieve configuration data
// Created: February 1, 2014
// Author: Andrey A. Katentsev
//
// Copyright � Andrey A. Katentsev, 2014
//

#pragma once

#include "registry.h"

namespace KAA
{
	namespace system
	{
		class windows_registry final : public registry
		{
		public:
			~windows_registry() override = default;

		private:
			std::unique_ptr<registry_key> iopen_key(root_key section, const std::string& subkey, const key_access& desired_access) override;
			std::unique_ptr<registry_key> icreate_key(root_key section, const std::string& subkey, key_options options, const key_access& desired_access, const void* desired_security) override;
		};
	}
}
