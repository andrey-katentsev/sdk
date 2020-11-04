//
// File: windows_registry_key_handle.cpp
// Description: resource handle for windows registry key
// Created: January 26, 2014
// Author: Andrey A. Katentsev
//
// Copyright © Andrey A. Katentsev, 2014
//

#include "../../include/RAII/windows_registry_key_handle.h"
#include "../../include/exception/windows_api_failure.h"

#include <stdexcept>

namespace
{
	void close_handle(::HKEY handle)
	{
		const auto error = ::RegCloseKey(handle);
		if (error != ERROR_SUCCESS) [[unlikely]]
		{
			throw KAA::windows_api_failure { __FUNCTIONW__, L"cannot close a handle to the specified registry key", error };
		}
	}
}

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
			try
			{
				close_handle(handle);
			}
			catch (const windows_api_failure&)
			{ }
		}

		windows_registry_key_handle::operator HKEY (void) const noexcept
		{
			return handle;
		}
	}
}
