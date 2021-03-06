//
// File: windows_registry_key.h
// Description: retrieves and stores the data for the specified value name associated with an open registry key
// Created: February 13, 2014
// Author: Andrey A. Katentsev
//
// Copyright � Andrey A. Katentsev, 2014
//

#pragma once

#include "registry_key.h"
#include "./RAII/windows_registry_key_handle.h"

namespace KAA
{
	namespace system
	{
		class windows_registry_key final : public registry_key
		{
		public:
			explicit windows_registry_key(HKEY);
			windows_registry_key(windows_registry_key&&) = delete;
			windows_registry_key(const windows_registry_key&) = delete;
			windows_registry_key& operator = (windows_registry_key&&) = delete;
			windows_registry_key& operator = (const windows_registry_key&) = delete;
			~windows_registry_key() override = default;

		private:
			RAII::windows_registry_key_handle key;

			std::string iquery_string_value(const std::string& name) const override;
			void iset_string_value(const std::string& name, const std::string& value) override;

			uint32_t iquery_dword_value(const std::string& name) const override;
			void iset_dword_value(const std::string& name, uint32_t value) override;
		};
	}
}
