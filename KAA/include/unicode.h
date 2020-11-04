//
// File: unicode.h
// Description: UTF8/UTF16 support
// Created: November 4, 2020
// Author: Andrey A. Katentsev
//
// Copyright © Andrey A. Katentsev, 2020
//

#include <string>

namespace KAA
{
	namespace unicode
	{
		std::string to_UTF8(const std::wstring& UTF16);
		std::wstring to_UTF16(const std::string& UTF8);
	}
}
