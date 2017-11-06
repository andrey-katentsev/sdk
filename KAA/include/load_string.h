//
// File: load_string.h
// Description: windows string table resource helper
// Created: May 16, 2013
// Author: Andrey A. Katentsev
//
// Copyright © Andrey A. Katentsev, 2013
//

#pragma once

#include <string>
#include <windows.h>

namespace KAA
{
	namespace resources
	{
		// THROWS: windows_api_failure
		// SAFE GUARANTEE: strong
		// SIDE EFFECTS: -
		std::wstring load_string(UINT);

		// THROWS: windows_api_failure
		// SAFE GUARANTEE: strong
		// SIDE EFFECTS: -
		std::wstring load_string(UINT, HINSTANCE);
	}
}
