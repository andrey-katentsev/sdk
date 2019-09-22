//
// File: hash.cpp
// Description: cryptography API (based on Windows Crypto API)
// Created: May 17, 2013
// Author: Andrey A. Katentsev
//
// Copyright © Andrey A. Katentsev, 2013
//

#pragma comment(lib, "advapi32.lib")

#include "../../include/cryptography/hash.h"
#include "../../include/cryptography/windows_crypto_api.h"
#include "../../include/exception/windows_api_failure.h"

namespace KAA
{
	namespace cryptography
	{
		hash::hash(const provider& csp, const ALG_ID algorithm, HCRYPTKEY key, const DWORD flags)
		{
			if (FALSE == ::CryptCreateHash(csp.get_handle(), algorithm, key, flags, &handle))
			{
				const auto code = ::GetLastError();
				throw windows_api_failure(__FUNCTIONW__, L"failed to create a hash object handle.", code);
			}
		}

		hash::~hash()
		{
			if (FALSE == ::CryptDestroyHash(handle))
			{
				const auto code = ::GetLastError();
			}
		}

		hash::operator HCRYPTHASH (void) const noexcept
		{
			return handle;
		}
	}
}
