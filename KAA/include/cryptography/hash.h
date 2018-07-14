//
// File: hash.h
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
		class provider;

		// FUTURE: KAA: complete (replace LPCWSTR, DWORD, etc).
		// Initiates the hashing of a stream of data.
		class hash
		{
		public:
			hash(const provider&, ALG_ID algorithm, HCRYPTKEY key, DWORD flags);
			hash(const hash&) = delete;
			hash(hash&&) = delete;
			~hash();

			hash& operator = (const hash&) = delete;
			hash& operator = (hash&&) = delete;

			operator HCRYPTHASH (void) const noexcept;

		private:
			HCRYPTHASH handle;
		};
	}
}
