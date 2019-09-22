//
// File: cryptography.cpp
// Description: cryptography API (based on Windows CryptoAPI)
// Created: May 17, 2013
// Author: Andrey A. Katentsev
//
// Copyright © Andrey A. Katentsev, 2013
//

#include "../../include/cryptography/cryptography.h"

#include <iso646.h>

#include "../../include/cryptography/provider.h"
#include "../../include/exception/windows_api_failure.h"
#include "../../include/RAII/local_memory.h"

#include <wincrypt.h>

#pragma comment(lib, "advapi32.lib")
#pragma comment(lib, "crypt32.lib")

namespace KAA
{
	namespace cryptography
	{
		// Шифрование путём наложениея гамма-последовательности на открытый текст.
		// Параметры:
		// [in]  source      - данные для шифрования (открытый текст)
		// [in]  key         - ключ шифрования (гамма-последовательность)
		// [out] destination - зашифрованные данные (зашифрованный текст)
		// [in]  size        - размер данных (для шифрования = размер ключа = зашифрованных данных)
		void gamma(const void* source, const void* key, void* destination, const size_t size)
		{
			for(size_t i = 0; i < size; ++i)
				(static_cast<uint8_t*>(destination))[i] = (static_cast<const uint8_t*>(source))[i] xor (static_cast<const uint8_t*>(key))[i];
		}

		// THROWS: windows_api_failure
		// SAFE GUARANTEE: basic
		// SIDE EFFECTS: -
		void generate_random(_In_ const provider& csp, void* buffer, const size_t size)
		{
			if(FALSE == ::CryptGenRandom(csp, size, static_cast<BYTE*>(buffer)))
			{
				const DWORD code = ::GetLastError();
				throw windows_api_failure(__FUNCTIONW__, L"Unable to fill a buffer with cryptographically random bytes.", code);
			}
		}

		std::vector<uint8_t> protect_data(const void* source, const size_t size)
		{
			const ::DATA_BLOB plaintext = { size, static_cast<BYTE*>(const_cast<void*>(source)) };
			::DATA_BLOB ciphertext = { 0 };
			// no description, no additional entropy, no prompt, no flags
			if (FALSE == ::CryptProtectData(const_cast<::DATA_BLOB*>(&plaintext), nullptr, nullptr, nullptr, nullptr, 0UL, &ciphertext))
			{
				const auto code = ::GetLastError();
				throw windows_api_failure(__FUNCTIONW__, L"failed to protect data with the user session key", code);
			}

			const RAII::local_memory memory { ciphertext.pbData };
			{
				// FUTURE: KAA: consider to use memcpy or etc.
				std::vector<uint8_t> data(ciphertext.cbData);
				for (auto i = 0U; i < ciphertext.cbData; ++i)
				{
					data[i] = ciphertext.pbData[i];
				}
				return data;
			}
		}

		std::vector<uint8_t> unprotect_data(const void* source, const size_t size)
		{
			const ::DATA_BLOB ciphertext = { size, static_cast<BYTE*>(const_cast<void*>(source)) };
			::DATA_BLOB plaintext = { 0 };
			// no description, no additional entropy, no prompt, no flags
			if (FALSE == ::CryptUnprotectData(const_cast<::DATA_BLOB*>(&ciphertext), nullptr, nullptr, nullptr, nullptr, 0UL, &plaintext))
			{
				const auto code = ::GetLastError();
				throw windows_api_failure(__FUNCTIONW__, L"failed to protect data with the user session key", code);
			}

			const RAII::local_memory memory { plaintext.pbData };
			{
				// FUTURE: KAA: consider to use memcpy or etc.
				std::vector<uint8_t> data(plaintext.cbData);
				for (auto i = 0U; i < plaintext.cbData; ++i)
				{
					data[i] = plaintext.pbData[i];
				}
				return data;
			}
		}
	}
}
