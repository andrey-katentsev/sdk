//
// File: registry_key.h
// Description: retrieves and stores the data for the specified value name associated with an open registry key
// Created: February 12, 2014
// Author: Andrey A. Katentsev
//
// Copyright � Andrey A. Katentsev, 2014
//

#pragma once

#include <string>
#include <cstdint>

namespace KAA
{
	namespace system
	{
		class registry_key
		{
		public:
			std::wstring query_string_value(const std::wstring& name) const;
			void set_string_value(const std::wstring& name, const std::wstring& data);

			uint32_t query_dword_value(const std::wstring& name) const;
			void set_dword_value(const std::wstring& name, uint32_t data);

			virtual ~registry_key() = default;

		private:
			virtual std::wstring iquery_string_value(const std::wstring& name) const = 0;
			virtual void iset_string_value(const std::wstring& name, const std::wstring& data) = 0;

			virtual uint32_t iquery_dword_value(const std::wstring& name) const = 0;
			virtual void iset_dword_value(const std::wstring& name, uint32_t data) = 0;
		};
	}
}
