// Feb 13, 2014

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

			std::wstring iquery_string_value(const std::wstring& value_name) const override;
			void iset_string_value(const std::wstring& value_name, const std::wstring& value) override;

			uint32_t iquery_dword_value(const std::wstring& value_name) const override;
			void iset_dword_value(const std::wstring& value_name, uint32_t value) override;
		};
	}
}
