//
// File: windows_registry_key.cpp
// Description: retrieves and stores the data for the specified value name associated with an open registry key
// Created: February 13, 2014
// Author: Andrey A. Katentsev
//
// Copyright © Andrey A. Katentsev, 2014
//

#include "../include/windows_registry_key.h"

#include "../include/unicode.h"
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
		throw KAA::windows_api_failure { __FUNCTION__, "cannot retrieve the type for the specified value name associated with an open registry key", error };
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
			throw KAA::windows_api_failure { __FUNCTION__, "cannot retrieve the data for the specified value name associated with an open registry key", error };
		}
		constexpr auto severity = KAA::windows_api_failure::severity_t::warning;
		// ERROR_BAD_TOKEN_TYPE; ERROR_UNSUPPORTED_TYPE; ERROR_INVALID_DATATYPE; RPC_S_ENTRY_TYPE_MISMATCH;
		throw KAA::windows_api_failure { __FUNCTION__, "cannot retrieve the data for the specified value name associated with an open registry key", ERROR_DATATYPE_MISMATCH, FACILITY_NULL, severity, true }; // FUTURE: this is not a win32 failure.
	}

	void set_string_value(const HKEY key, const std::wstring& name, const std::wstring& data)
	{
		const auto error = ::RegSetValueExW(key, name.c_str(), 0, REG_SZ, reinterpret_cast<const BYTE*>(data.c_str()), static_cast<::DWORD>((data.length() + 1) * sizeof(wchar_t)));
		if(error != ERROR_SUCCESS) [[unlikely]]
		{
			throw KAA::windows_api_failure { __FUNCTION__, "cannot set the data and type of a specified value under a registry key", error };
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
			throw KAA::windows_api_failure { __FUNCTION__, "cannot retrieve the data for the specified value name associated with an open registry key", error };
		}
		if(REG_DWORD == type)
		{
			return data;
		}
		constexpr auto severity = KAA::windows_api_failure::severity_t::warning;
		throw KAA::windows_api_failure { __FUNCTION__, "cannot retrieve the data for the specified value name associated with an open registry key", ERROR_DATATYPE_MISMATCH, FACILITY_NULL, severity, true }; // FUTURE: this is not a win32 failure.
	}

	void set_dword_value(const HKEY key, const std::wstring& name, const DWORD data)
	{
		const auto error = ::RegSetValueExW(key, name.c_str(), 0, REG_DWORD, reinterpret_cast<const BYTE*>(&data), sizeof(data));
		if(error != ERROR_SUCCESS) [[unlikely]]
		{
			throw KAA::windows_api_failure { __FUNCTION__, "cannot set the data and type of a specified value under a registry key", error };
		}
	}
}

namespace KAA
{
	using namespace unicode;
	namespace system
	{
		windows_registry_key::windows_registry_key(const HKEY handle) :
		key(handle)
		{}

		std::string windows_registry_key::iquery_string_value(const std::string& name) const
		{
			return to_UTF8(::query_string_value(key, to_UTF16(name)));
		}

		void windows_registry_key::iset_string_value(const std::string& name, const std::string& data)
		{
			return ::set_string_value(key, to_UTF16(name), to_UTF16(data));
		}

		uint32_t windows_registry_key::iquery_dword_value(const std::string& name) const
		{
			return ::query_dword_value(key, to_UTF16(name));
		}

		void windows_registry_key::iset_dword_value(const std::string& name, uint32_t data)
		{
			return ::set_dword_value(key, to_UTF16(name), data);
		}
	}
}
