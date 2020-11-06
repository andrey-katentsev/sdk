//
// File: windows_hash.cpp
// Description: cryptography API (based on Windows Crypto API)
// Created: May 17, 2013
// Author: Andrey A. Katentsev
//
// Copyright © Andrey A. Katentsev, 2013
//

#pragma comment(lib, "advapi32.lib")

#include "../../include/cryptography/windows_hash.h"
#include "../../include/exception/windows_api_failure.h"

namespace KAA
{
	namespace cryptography
	{
		windows_hash::windows_hash(HCRYPTPROV csp, const ALG_ID algorithm, HCRYPTKEY key, const DWORD flags)
		{
			if (FALSE == ::CryptCreateHash(csp, algorithm, key, flags, &handle))
			{
				const auto code = ::GetLastError();
				throw windows_api_failure { __FUNCTION__, "cannot create a windows hash object handle", code };
			}
		}

		windows_hash::~windows_hash()
		{
			if (FALSE == ::CryptDestroyHash(handle))
			{
				const auto code = ::GetLastError();
			}
		}

		windows_hash::operator HCRYPTHASH (void) const noexcept
		{
			return handle;
		}

		std::uintptr_t windows_hash::iget_handle(void) const noexcept
		{
			return handle;
		}
	}
}
