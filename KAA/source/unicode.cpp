//
// File: unicode.cpp
// Description: UTF8/UTF16 support
// Created: November 4, 2020
// Author: Andrey A. Katentsev
//
// Copyright © Andrey A. Katentsev, 2020
//

#include "../include/unicode.h"
#include "../include/exception/windows_api_failure.h"

#include <vector>

#include <windows.h>

namespace
{
	size_t get_UTF8_buffer_size(const std::wstring& UTF16)
	{
		const auto size = ::WideCharToMultiByte(CP_UTF8, 0, UTF16.c_str(), static_cast<int>(UTF16.length()), nullptr, 0, nullptr, nullptr);
		if (0 == size)
		{
			const auto error = ::GetLastError();
			throw KAA::windows_api_failure { __FUNCTIONW__, L"cannot determine the required buffer size for UTF8 string", error };
		}
		return size;
	}

	size_t get_UTF16_buffer_length(const std::string& UTF8)
	{
		const auto size = ::MultiByteToWideChar(CP_UTF8, 0, UTF8.c_str(), static_cast<int>(UTF8.length()), nullptr, 0);
		if (0 == size)
		{
			const auto error = ::GetLastError();
			throw KAA::windows_api_failure { __FUNCTIONW__, L"cannot determine the required buffer length for UTF16 string", error };
		}
		return size;
	}
}

namespace KAA
{
	namespace unicode
	{
		std::string to_UTF8(const std::wstring& UTF16)
		{
			auto UTF8 = std::vector<char>(get_UTF8_buffer_size(UTF16), '\0');
			const auto bytes_written = ::WideCharToMultiByte(CP_UTF8, 0, UTF16.c_str(), static_cast<int>(UTF16.length()), UTF8.data(), static_cast<int>(UTF8.size()), nullptr, nullptr);
			if (0 == bytes_written)
			{
				const auto error = ::GetLastError();
				throw KAA::windows_api_failure { __FUNCTIONW__, L"cannot map a UTF-16 (wide character) string to a UTF-8 (narrow character) string", error };
			}
			return { UTF8.data(), static_cast<size_t>(bytes_written) };
		}

		std::wstring to_UTF16(const std::string& UTF8)
		{
			auto UTF16 = std::vector<wchar_t>(get_UTF16_buffer_length(UTF8), L'\0');
			const auto characters_written = ::MultiByteToWideChar(CP_UTF8, 0, UTF8.c_str(), static_cast<int>(UTF8.length()), UTF16.data(), static_cast<int>(UTF16.size()));
			if (0 == characters_written)
			{
				const auto error = ::GetLastError();
				throw KAA::windows_api_failure { __FUNCTIONW__, L"cannot map a UTF-16 (wide character) string to a UTF-8 (narrow character) string", error };
			}
			return { UTF16.data(), static_cast<size_t>(characters_written) };
		}
	}
}
