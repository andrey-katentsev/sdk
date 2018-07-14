//
// File: provider.h
// Description: cryptography API (based on Windows Crypto API)
// Created: May 17, 2013
// Author: Andrey A. Katentsev
//
// Copyright © Andrey A. Katentsev, 2013
//

#pragma once

#include <windows.h>
#include <wincrypt.h>

namespace KAA
{
	namespace cryptography
	{
		// FUTURE: KAA: abstract base class required.
		// FUTURE: KAA: complete (replace LPCWSTR, DWORD, etc).
		// Used to acquire a handle to a particular key container within a particular cryptographic service provider (CSP).
		class provider
		{
		public:
			provider(LPCWSTR container, LPCWSTR provider, DWORD type, DWORD flags);
			provider(const provider&) = delete;
			provider(provider&&) = delete;
			~provider();

			provider& operator = (const provider&) = delete;
			provider& operator = (provider&&) = delete;

			operator HCRYPTPROV (void) const noexcept;

		private:
			HCRYPTPROV handle;
		};
	}
}
