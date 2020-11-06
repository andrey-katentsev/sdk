//
// File: windows_crypto_api.cpp
// Description: this handle is used in calls to Windows CryptoAPI functions
// Created: May 17, 2013
// Author: Andrey A. Katentsev
//
// Copyright © Andrey A. Katentsev, 2013
//

#pragma comment(lib, "advapi32.lib")

#include "../../include/cryptography/windows_crypto_api.h"
#include "../../include/exception/windows_api_failure.h"

namespace KAA
{
	namespace cryptography
	{
		windows_crypto_api::windows_crypto_api(const LPCWSTR container, const LPCWSTR provider, const DWORD type, const DWORD flags)
		{
			if (FALSE == ::CryptAcquireContextW(&handle, container, provider, type, flags))
			{
				// FUTURE: KAA: incorrect message from windows_api_failure::get_system_message (see MSDN: NTE_BAD_KEYSET etc.)
				const auto code = ::GetLastError();
				throw windows_api_failure { __FUNCTION__, "cannot acquire a windows cryptographic service provider handle", code };
			}
		}

		windows_crypto_api::~windows_crypto_api()
		{
			if (FALSE == ::CryptReleaseContext(handle, 0))
			{
				const auto code = ::GetLastError();
			}
		}

		windows_crypto_api::operator HCRYPTPROV (void) const noexcept
		{
			return handle;
		}

		std::uintptr_t windows_crypto_api::iget_handle(void) const noexcept
		{
			return handle;
		}
	}
}
