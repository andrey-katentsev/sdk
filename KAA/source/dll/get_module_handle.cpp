//
// File: get_module_handle.h
// Description: dynamic-link library functions
// Created: August 17, 2014
// Author: Andrey A. Katentsev
//
// Copyright © Andrey A. Katentsev, 2014
//

#include "../../include/dll/get_module_handle.h"

#include "../../include/unicode.h"
#include "../../include/exception/windows_api_failure.h"

namespace KAA
{
	using namespace unicode;
	namespace dll
	{
		HINSTANCE get_calling_process_module_handle(void)
		{
			HINSTANCE handle = ::GetModuleHandleW(nullptr);
			if(nullptr == handle)
			{
				const DWORD error = ::GetLastError();
				throw windows_api_failure { __FUNCTION__, "cannot retrieve a module handle for the file used to create the calling process", error };
			}
			return handle;
		}

		HINSTANCE get_module_handle(const std::string& name)
		{
			HINSTANCE handle = ::GetModuleHandleW(to_UTF16(name).c_str());
			if(nullptr == handle)
			{
				const DWORD error = ::GetLastError();
				throw windows_api_failure { __FUNCTION__, "cannot retrieve a module handle for the specified module", error };
			}
			return handle;
		}
	}
}
