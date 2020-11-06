//
// File: load_string.cpp
// Description: windows string table resource helper
// Created: May 16, 2013
// Author: Andrey A. Katentsev
//
// Copyright © Andrey A. Katentsev, 2013
//

#include "../include/load_string.h"
#include "../include/dll/get_module_handle.h"
#include "../include/exception/windows_api_failure.h"

namespace KAA
{
	namespace resources
	{
		std::wstring load_string(const UINT string_resource_index)
		{
			HINSTANCE module = dll::get_calling_process_module_handle();
			return load_string(string_resource_index, module);
		}

		std::wstring load_string(const UINT string_resource_index, HINSTANCE module)
		{
			enum { receive_a_read_only_pointer_to_the_resource_itself = 0 };
			wchar_t* raw_string = nullptr;
			const int length = ::LoadStringW(module, string_resource_index, reinterpret_cast<LPWSTR>(&raw_string), receive_a_read_only_pointer_to_the_resource_itself);
			if(0 == length)
			{
				const DWORD error = ::GetLastError();
				throw windows_api_failure { __FUNCTION__, "cannot load a string resource from the executable file associated with a specified module", error };
			}
			return std::wstring(raw_string, length);
		}
	}
}
