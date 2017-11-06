// Feb 12, 2014

#include "../include/registry_key.h"

namespace KAA
{
	namespace system
	{
		std::wstring registry_key::query_string_value(const std::wstring& value_name) const
		{
			return iquery_string_value(value_name);
		}

		void registry_key::set_string_value(const std::wstring& value_name, const std::wstring& value)
		{
			return iset_string_value(value_name, value);
		}

		uint32_t registry_key::query_dword_value(const std::wstring& value_name) const
		{
			return iquery_dword_value(value_name);
		}

		void registry_key::set_dword_value(const std::wstring& value_name, const uint32_t value)
		{
			return iset_dword_value(value_name, value);
		}
	}
}
