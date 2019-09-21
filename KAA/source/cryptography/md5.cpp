//
// File: md5.cpp
// Description: the MD5 message-digest algorithm
// Created: August 18, 2013
// Author: Andrey A. Katentsev
//
// Copyright © Andrey A. Katentsev, 2013
//

#include "../../include/cryptography/md5.h"

#include <iomanip>
#include <sstream>
#include <cassert>

#include "../../include/cryptography/hash.h"
#include "../../include/cryptography/provider.h"
#include "../../include/exception/windows_api_failure.h"

namespace
{
	void add_data_to_hash(HCRYPTHASH hash, const BYTE* data, DWORD size)
	{
		if (FALSE == ::CryptHashData(hash, data, size, 0U))
		{
			const auto error = ::GetLastError();
			throw KAA::windows_api_failure(__FUNCTIONW__, L"cannot add data to a specified hash object", error);
		}
	}

	KAA::cryptography::md5_t complete_hash(HCRYPTHASH hash)
	{
		KAA::cryptography::md5_t digest;
		DWORD size = sizeof(digest);
		if (FALSE == ::CryptGetHashParam(hash, HP_HASHVAL, reinterpret_cast<BYTE*>(&digest), &size, 0U))
		{
			const auto error = ::GetLastError();
			throw KAA::windows_api_failure(__FUNCTIONW__, L"cannot retrieve the actual hash value", error);
		}
		assert(sizeof(digest) == size);
		return digest;
	}
}

namespace KAA
{
	namespace convert
	{
		// THROWS: -
		// SAFE GUARANTEE: strong
		// SIDE EFFECTS: -
		std::wstring to_wstring(const cryptography::md5_t& digest)
		{
			std::wostringstream output;
			output << std::setfill(L'0');
			for (size_t i = 0; i < sizeof(digest); ++i)
			{
				output << std::hex << std::setw(2) << digest.byte[i];
			}
			return output.str();
		}
	}

	namespace cryptography
	{
		// THROWS: -
		// SAFE GUARANTEE: no fail
		// SIDE EFFECTS: -
		bool operator == (const md5_t& left, const md5_t& right)
		{
			return left.qword[0] == right.qword[0] && left.qword[1] == right.qword[1];
		}

		// THROWS: -
		// SAFE GUARANTEE: no fail
		// SIDE EFFECTS: -
		bool operator != (const md5_t& left, const md5_t& right)
		{
			return !(left == right);
		}

		// THROWS: windows_api_failure
		// SAFE GUARANTEE: strong
		// SIDE EFFECTS: -
		md5_t calculate_md5(const void* data, const size_t data_size)
		{
			const provider csp { nullptr, MS_DEF_PROV, PROV_RSA_FULL, CRYPT_SILENT | CRYPT_VERIFYCONTEXT };
			const hash algorithm { csp, CALG_MD5, 0, 0 };
			add_data_to_hash(algorithm, reinterpret_cast<const BYTE*>(data), data_size);
			return complete_hash(algorithm);
		}
	}
}
