//
// File: windows_crypto_api.h
// Description: this handle is used in calls to Windows CryptoAPI functions
// Created: May 17, 2013
// Author: Andrey A. Katentsev
//
// Copyright © Andrey A. Katentsev, 2013
//

#pragma once

#include "provider.h"

#include <windows.h>
#include <wincrypt.h>

namespace KAA
{
	namespace cryptography
	{
		// Acquires a handle to a particular key container within a particular cryptographic service provider (CSP).
		class windows_crypto_api final : public provider
		{
		public:
			windows_crypto_api(LPCWSTR container, LPCWSTR provider, DWORD type, DWORD flags);
			windows_crypto_api(const windows_crypto_api&) = delete;
			windows_crypto_api(windows_crypto_api&&) = delete;
			~windows_crypto_api();

			windows_crypto_api& operator = (const windows_crypto_api&) = delete;
			windows_crypto_api& operator = (windows_crypto_api&&) = delete;

			operator HCRYPTPROV (void) const noexcept;

		private:
			std::uintptr_t iget_handle(void) const noexcept override;
			HCRYPTPROV handle;
		};
	}
}
