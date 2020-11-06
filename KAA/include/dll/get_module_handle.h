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
		// Returns a handle to the file used to create the calling process (.exe file).
		HINSTANCE get_calling_process_module_handle(void);

		// THROWS: windows_api_failure
		// SAFE GUARANTEE: strong
		// SIDE EFFECTS: -
		// Retrieves a module handle for the specified module.
		// The module must have been loaded by the calling process.
		HINSTANCE get_module_handle(const std::string& name);
	}
}
