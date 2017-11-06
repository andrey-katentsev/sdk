//
// File: get_module_handle.h
// Description: dynamic-link library functions
// Created: August 17, 2014
// Author: Andrey A. Katentsev
//
// Copyright © Andrey A. Katentsev, 2014
//

#pragma once

#include <string>
#include <windows.h>

namespace KAA
{
	namespace dll
	{
		// THROWS: windows_api_failure
		// SAFE GUARANTEE: strong
		// SIDE EFFECTS: -
		HINSTANCE get_calling_process_module_handle(void);

		// THROWS: windows_api_failure
		// SAFE GUARANTEE: strong
		// SIDE EFFECTS: -
		HINSTANCE get_module_handle(const std::wstring& name);
	}
}
