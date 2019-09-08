// Feb 13, 2014

#include "../include/windows_registry_key.h"

#include <vector>

#include "../include/exception/windows_api_failure.h"

namespace
{
	// THROWS: windows_api_failure
	// SAFE GUARANTEE: strong
	// SIDE EFFECTS: -
	// RETURNS: the size of the value_name's value in bytes
	size_t get_value_size(const HKEY key, const std::wstring& value_name)
	{
		DWORD value_size = 0;
		const LSTATUS code = ::RegQueryValueExW(key, value_name.c_str(), nullptr, nullptr, nullptr, &value_size);
		if(ERROR_SUCCESS != code)
		{
			throw KAA::windows_api_failure(__FUNCTIONW__, L"Unable to determine the system's registry value size.", code);
		}

		return value_size;
	}

	std::wstring query_string_value(const HKEY key, const std::wstring& value_name)
	{
		DWORD buffer_size = get_value_size(key, value_name) + sizeof(wchar_t); // the string may not have been stored with the proper terminating null character
		std::vector<wchar_t> buffer(buffer_size / sizeof(wchar_t), L'\0');
		buffer_size = buffer.size() * sizeof(wchar_t);
		DWORD value_type = REG_SZ;
		const LSTATUS code = ::RegQueryValueExW(key, value_name.c_str(), nullptr, &value_type, reinterpret_cast<LPBYTE>(&buffer[0]), &buffer_size);
		if(ERROR_SUCCESS != code)
		{
			throw KAA::windows_api_failure(__FUNCTIONW__, L"Unable to retrieve a string value from the system registry.", code);
		}

		if(REG_SZ != value_type)
		{
			throw KAA::windows_api_failure(__FUNCTIONW__, L"Unable to retrieve a string value from the system registry.", ERROR_DATATYPE_MISMATCH, FACILITY_NULL, KAA::windows_api_failure::S_WARNING, true); // ERROR_BAD_TOKEN_TYPE; ERROR_UNSUPPORTED_TYPE; ERROR_INVALID_DATATYPE; RPC_S_ENTRY_TYPE_MISMATCH; // FUTURE: this is not a win32 failure.
		}

		return std::wstring(&buffer[0]);
	}

	void set_string_value(const HKEY key, const std::wstring& value_name, const std::wstring& value)
	{
		const LSTATUS code = ::RegSetValueExW(key, value_name.c_str(), 0, REG_SZ, reinterpret_cast<const BYTE*>(value.c_str()), ( value.length() + 1 ) * sizeof(wchar_t));
		if(ERROR_SUCCESS != code)
		{
			throw KAA::windows_api_failure(__FUNCTIONW__, L"Unable to set the string value to the system registry.", code);
		}
	}

	DWORD query_dword_value(const HKEY key, const std::wstring& value_name)
	{
		DWORD value = 0;
		DWORD value_type = REG_DWORD;
		DWORD value_size = sizeof(DWORD);
		const LSTATUS code = ::RegQueryValueExW(key, value_name.c_str(), nullptr, &value_type, reinterpret_cast<LPBYTE>(&value), &value_size);
		if(ERROR_SUCCESS != code)
		{
			throw KAA::windows_api_failure(__FUNCTIONW__, L"Unable to retrieve a dword value from the system registry.", code);
		}

		if(REG_DWORD != value_type)
		{
			throw KAA::windows_api_failure(__FUNCTIONW__, L"Unable to retrieve a dword value from the system registry.", ERROR_DATATYPE_MISMATCH, FACILITY_NULL, KAA::windows_api_failure::S_WARNING, true); // FUTURE: this is not a win32 failure.
		}

		return value;
	}

	void set_dword_value(const HKEY key, const std::wstring& value_name, const DWORD value)
	{
		const LSTATUS code = ::RegSetValueExW(key, value_name.c_str(), 0, REG_DWORD, reinterpret_cast<const BYTE*>(&value), sizeof(DWORD));
		if(ERROR_SUCCESS != code)
		{
			throw KAA::windows_api_failure(__FUNCTIONW__, L"Unable to set the dword value to the system registry.", code);
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

		windows_registry_key::~windows_registry_key()
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
