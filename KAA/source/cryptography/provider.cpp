//
// File: provider.cpp
// Description: cryptography API (based on Windows Crypto API)
// Created: May 17, 2013
// Author: Andrey A. Katentsev
//
// Copyright © Andrey A. Katentsev, 2013
//

#pragma comment(lib, "advapi32.lib")

#include "../../include/cryptography/provider.h"
#include "../../include/exception/windows_api_failure.h"

namespace KAA
{
	namespace cryptography
	{
		provider::provider(const LPCWSTR container, const LPCWSTR provider, const DWORD type, const DWORD flags)
		{
			if (FALSE == ::CryptAcquireContextW(&handle, container, provider, type, flags))
			{
				// FUTURE: KAA: incorrect message from windows_api_failure::get_system_message (see MSDN: NTE_BAD_KEYSET etc.)
				const auto code = ::GetLastError();
				throw windows_api_failure(__FUNCTIONW__, L"failed to acquire a cryptographic service provider handle", code);
			}
		}

		provider::~provider()
		{
			if (FALSE == ::CryptReleaseContext(handle, 0))
			{
				const auto code = ::GetLastError();
			}
		}

		provider::operator HCRYPTPROV (void) const noexcept
		{
			return handle;
		}
	}
}
