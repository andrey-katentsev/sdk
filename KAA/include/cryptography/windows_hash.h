//
// File: windows_hash.h
// Description: cryptography API (based on Windows CryptoAPI)
// Created: May 17, 2013
// Author: Andrey A. Katentsev
//
// Copyright © Andrey A. Katentsev, 2013
//

#pragma once

#include "hash.h"

#include <windows.h>
#include <wincrypt.h>

namespace KAA
{
	namespace cryptography
	{
		// Initiates the hashing of a stream of data.
		class windows_hash final : public hash
		{
		public:
			windows_hash(HCRYPTPROV csp, ALG_ID algorithm, HCRYPTKEY key, DWORD flags);
			windows_hash(const windows_hash&) = delete;
			windows_hash(windows_hash&&) = delete;
			~windows_hash();

			windows_hash& operator = (const windows_hash&) = delete;
			windows_hash& operator = (windows_hash&&) = delete;

			operator HCRYPTHASH (void) const noexcept;

		private:
			std::uintptr_t iget_handle(void) const noexcept override;
			HCRYPTHASH handle;
		};
	}
}
