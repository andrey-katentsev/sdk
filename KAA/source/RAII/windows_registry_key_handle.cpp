//
// File: windows_registry_key_handle.cpp
// Description: resource handle for windows registry key
// Created: January 26, 2014
// Author: Andrey A. Katentsev
//
// Copyright © Andrey A. Katentsev, 2014
//

#include "../../include/RAII/windows_registry_key_handle.h"

#include <stdexcept>

namespace KAA
{
	namespace RAII
	{
		windows_registry_key_handle::windows_registry_key_handle(const HKEY handle) : handle(handle)
		{
			if(nullptr == handle)
				throw std::invalid_argument(__FUNCTION__);
		}

		windows_registry_key_handle::~windows_registry_key_handle()
		{
			::RegCloseKey(handle);
		}

		windows_registry_key_handle::operator HKEY (void) const noexcept
		{
			return handle;
		}
	}
}
