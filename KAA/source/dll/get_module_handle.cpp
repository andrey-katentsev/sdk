//
// File: get_module_handle.h
// Description: dynamic-link library functions
// Created: August 17, 2014
// Author: Andrey A. Katentsev
//
// Copyright © Andrey A. Katentsev, 2014
//

#include "../../include/dll/get_module_handle.h"
#include "../../include/exception/windows_api_failure.h"

namespace KAA
{
	namespace dll
	{
		HINSTANCE get_calling_process_module_handle(void)
		{
			HINSTANCE handle = ::GetModuleHandleW(nullptr);
			if(nullptr == handle)
			{
				const DWORD error = ::GetLastError();
				throw windows_api_failure(__FUNCTIONW__, L"Unable to retrieve a module handle for the file used to create the calling process.", error);
			}
			return handle;
		}

		// TODO: KAA: consider to replace const std::wstring& with the std::move(std::wstring).
		HINSTANCE get_module_handle(const std::wstring& name)
		{
			HINSTANCE handle = ::GetModuleHandleW(name.c_str());
			if(nullptr == handle)
			{
				const DWORD error = ::GetLastError();
				throw windows_api_failure(__FUNCTIONW__, L"Unable to retrieve a module handle for the specified module.", error);
			}
			return handle;
		}
	}
}
