// Feb 12, 2014

#pragma once

#include <string>

#include "stdtypes.h"

namespace KAA
{
	namespace system
	{
		class registry_key
		{
		public:
			std::wstring query_string_value(const std::wstring& value_name) const;
			void set_string_value(const std::wstring& value_name, const std::wstring& value);

			uint32_t query_dword_value(const std::wstring& value_name) const;
			void set_dword_value(const std::wstring& value_name, uint32_t value);

		private:
			virtual std::wstring iquery_string_value(const std::wstring& value_name) const = 0;
			virtual void iset_string_value(const std::wstring& value_name, const std::wstring& value) = 0;

			virtual uint32_t iquery_dword_value(const std::wstring& value_name) const = 0;
			virtual void iset_dword_value(const std::wstring& value_name, uint32_t value) = 0;
		};
	}
}
