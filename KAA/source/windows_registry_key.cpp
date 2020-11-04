// Feb 13, 2014

#include "../include/windows_registry_key.h"
#include "../include/exception/windows_api_failure.h"

#include <vector>

namespace
{
	struct value_attributes_t
	{
		::DWORD size = 0;
		::DWORD type = REG_NONE;
	};

	// THROWS: windows_api_failure
	// SAFE GUARANTEE: strong
	// SIDE EFFECTS: -
	// RETURNS: type and size of the value in bytes
	value_attributes_t get_value_attributes(const HKEY key, const std::wstring& name)
	{
		::DWORD size = 0;
		::DWORD type = REG_NONE;
		const auto error = ::RegQueryValueExW(key, name.c_str(), nullptr, &type, nullptr, &size);
		if(ERROR_SUCCESS == error) [[likely]]
		{
			return { size, type };
		}
		throw KAA::windows_api_failure { __FUNCTIONW__, L"cannot determine the system registry value's size", error };
	}

	std::wstring query_string_value(const HKEY key, const std::wstring& name)
	{
		const auto attributes = get_value_attributes(key, name);
		if (REG_SZ == attributes.type) [[likely]]
		{
			::DWORD size = attributes.size + sizeof(wchar_t); // the string may not have been stored with the proper terminating null character
			std::vector<wchar_t> buffer(size / sizeof(wchar_t), L'\0');
			size = attributes.size;
			const auto error = ::RegQueryValueExW(key, name.c_str(), nullptr, nullptr, reinterpret_cast<LPBYTE>(buffer.data()), &size);
			if (ERROR_SUCCESS == error) [[likely]]
			{
				return buffer.data();
			}
			throw KAA::windows_api_failure { __FUNCTIONW__, L"cannot retrieve the string value from the system registry", error };
		}
		// ERROR_BAD_TOKEN_TYPE; ERROR_UNSUPPORTED_TYPE; ERROR_INVALID_DATATYPE; RPC_S_ENTRY_TYPE_MISMATCH;
		throw KAA::windows_api_failure { __FUNCTIONW__, L"cannot retrieve the string value from the system registry", ERROR_DATATYPE_MISMATCH, FACILITY_NULL, KAA::windows_api_failure::S_WARNING, true }; // FUTURE: this is not a win32 failure.
	}

	void set_string_value(const HKEY key, const std::wstring& name, const std::wstring& data)
	{
		const auto error = ::RegSetValueExW(key, name.c_str(), 0, REG_SZ, reinterpret_cast<const BYTE*>(data.c_str()), static_cast<::DWORD>((data.length() + 1) * sizeof(wchar_t)));
		if(error != ERROR_SUCCESS) [[unlikely]]
		{
			throw KAA::windows_api_failure { __FUNCTIONW__, L"cannot write the string value to the system registry", error };
		}
	}

	DWORD query_dword_value(const HKEY key, const std::wstring& name)
	{
		::DWORD data = 0;
		::DWORD type = REG_NONE;
		::DWORD size = sizeof(data);
		const auto error = ::RegQueryValueExW(key, name.c_str(), nullptr, &type, reinterpret_cast<LPBYTE>(&data), &size);
		if(error != ERROR_SUCCESS) [[unlikely]]
		{
			throw KAA::windows_api_failure { __FUNCTIONW__, L"cannot retrieve the dword value from the system registry", error };
		}
		if(REG_DWORD == type)
		{
			return data;
		}
		throw KAA::windows_api_failure { __FUNCTIONW__, L"cannot retrieve the dword value from the system registry", ERROR_DATATYPE_MISMATCH, FACILITY_NULL, KAA::windows_api_failure::S_WARNING, true }; // FUTURE: this is not a win32 failure.
	}

	void set_dword_value(const HKEY key, const std::wstring& name, const DWORD data)
	{
		const auto error = ::RegSetValueExW(key, name.c_str(), 0, REG_DWORD, reinterpret_cast<const BYTE*>(&data), sizeof(data));
		if(error != ERROR_SUCCESS) [[unlikely]]
		{
			throw KAA::windows_api_failure { __FUNCTIONW__, L"Unable to set the dword value to the system registry.", error };
		}
	}
}

namespace KAA
{
	namespace system
	{
		windows_registry_key::windows_registry_key(const HKEY handle) :
		key(handle)
		{}

		std::wstring windows_registry_key::iquery_string_value(const std::wstring& value_name) const
		{
			return ::query_string_value(key, value_name);
		}

		void windows_registry_key::iset_string_value(const std::wstring& value_name, const std::wstring& value)
		{
			return ::set_string_value(key, value_name, value);
		}

		uint32_t windows_registry_key::iquery_dword_value(const std::wstring& value_name) const
		{
			return ::query_dword_value(key, value_name);
		}

		void windows_registry_key::iset_dword_value(const std::wstring& value_name, uint32_t value)
		{
			return ::set_dword_value(key, value_name, value);
		}
	}
}
