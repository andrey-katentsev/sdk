//
// File: md5.cpp
// Description: the MD5 message-digest algorithm
// Created: August 18, 2013
// Author: Andrey A. Katentsev
//
// Copyright © Andrey A. Katentsev, 2013
//

#include "../include/md5.h"

#include <iomanip>
#include <sstream>

#include "../include/cryptography.h"
#include "../include/exception/windows_api_failure.h"

#include <windows.h>

using std::wstring;
using std::wstringstream;

namespace KAA
{
	namespace cryptography
	{
		// THROWS: -
		// SAFE GUARANTEE: no fail
		// SIDE EFFECTS: -
		bool operator == (const md5& left, const md5& right)
		{
			return left.qword[0] == right.qword[0] && left.qword[1] == right.qword[1];
		}

		// THROWS: -
		// SAFE GUARANTEE: no fail
		// SIDE EFFECTS: -
		bool operator != (const md5& left, const md5& right)
		{
			return !(left == right);
		}

		// THROWS: -
		// SAFE GUARANTEE: strong
		// SIDE EFFECTS: -
		wstring to_wstring(const md5& digest)
		{
			wstringstream output;
			output << std::setfill(L'0');
			for(size_t i = 0; i < sizeof(digest); ++i)
			{
				output << std::hex << std::setw(2) << digest.byte[i];
			}

			return output.str();
		}

		// THROWS: windows_api_failure
		// SAFE GUARANTEE: strong
		// SIDE EFFECTS: -
		md5 calculate_md5(const void* data, const size_t data_size)
		{
			const provider csp { nullptr, MS_DEF_PROV, PROV_RSA_FULL, CRYPT_SILENT | CRYPT_VERIFYCONTEXT };
			const hash algorithm { csp, CALG_MD5, 0, 0 };

			if(FALSE == ::CryptHashData(algorithm, reinterpret_cast<const BYTE*>(data), data_size, 0))
			{
				const DWORD code = ::GetLastError();
				throw windows_api_failure(__FUNCTIONW__, L"Unable to add data to a specified hash object.", code);
			}

			md5 digest;
			DWORD digest_size = sizeof(digest);

			if(FALSE == ::CryptGetHashParam(algorithm, HP_HASHVAL, reinterpret_cast<BYTE*>(&digest), &digest_size, 0))
			{
				const DWORD code = ::GetLastError();
				throw windows_api_failure(__FUNCTIONW__, L"Unable to retrieve the actual hash value.", code);
			}

			return digest;
		}
	}
}
