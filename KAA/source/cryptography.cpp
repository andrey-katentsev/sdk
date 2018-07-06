//
// File: cryptography.cpp
// Description: cryptography API (based on Windows CryptoAPI)
// Created: May 17, 2013
// Author: Andrey A. Katentsev
//
// Copyright © Andrey A. Katentsev, 2013
//

#include "../include/cryptography.h"

#undef max
#undef min

#include <algorithm>
#include <vector>

#include <iso646.h>
#include <memory.h>

#include "../include/random.h"
#include "../include/stdtypes.h"
#include "../include/exception/system_failure.h"
#include "../include/exception/windows_api_failure.h"
#include "../include/RAII/invalid_parameter_handler.h"

#pragma comment(lib, "advapi32.lib")

namespace
{
	void allow_execution(const wchar_t*, const wchar_t*, const wchar_t*, unsigned int, uintptr_t) { return; }

	// THROWS: system_failure
	// SAFE GUARANTEE: basic
	// SIDE EFFECTS: -
	size_t copy_memory(const void* source, size_t bytes_to_read, void* destination, size_t size)
	{
		KAA::RAII::invalid_parameter_handler session(allow_execution);
		{
			const size_t& bytes_to_write = std::min(bytes_to_read, size);
			const errno_t error = memcpy_s(destination, size, source, bytes_to_write);
			if(0 != error)
			{
				throw KAA::system_failure(__FUNCTIONW__, L"Unable to copy bytes between buffers.", error);
			}

			return bytes_to_write;
		}
	}
}

namespace KAA
{
	namespace cryptography
	{
		provider::provider(LPCWSTR wzContainer, LPCWSTR wzProvider, DWORD dwProviderType, DWORD dwFlags)
		{
			if(FALSE == ::CryptAcquireContextW(&m_handle, wzContainer, wzProvider, dwProviderType, dwFlags))
			{
				// FUTURE: KAA: incorrect message from windows_api_failure::get_system_message (see MSDN: NTE_BAD_KEYSET etc.)
				const DWORD code = ::GetLastError();
				throw windows_api_failure(__FUNCTIONW__, L"Unable to acquire a handle to a particular key container within a particular cryptographic service provider.", code);
			}
		}

		provider::~provider()
		{
			::CryptReleaseContext(m_handle, 0);
		}

		provider::operator HCRYPTPROV (void) const
		{
			return m_handle;
		}

		hash::hash(const provider& csp, ALG_ID algorithm, HCRYPTKEY hKey, DWORD dwFlags)
		{
			if(FALSE == ::CryptCreateHash(csp, algorithm, hKey, dwFlags, &m_hash))
			{
				const DWORD code = ::GetLastError();
				throw windows_api_failure(__FUNCTIONW__, L"Unable to create a handle to a cryptographic service provider hash object.", code);
			}
		}

		hash::~hash()
		{
			::CryptDestroyHash(m_hash);
		}

		hash::operator HCRYPTHASH (void) const
		{
			return m_hash;
		}

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

		// Генерирование (криптографически) случайных данных.
		void generate(const size_t bytes_to_write, void* memory_write_to)
		{
			unsigned int value = 0;
			const size_t chunk_size = sizeof(value);

			std::vector<uint8_t> buffer(bytes_to_write, 0);
			uint8_t* random_data = &buffer[0];

			size_t bytes_written = 0;

			for(size_t i = 0; i < bytes_to_write; i += chunk_size)
			{
				value = random();
				bytes_written += copy_memory(&value, chunk_size, random_data + i, bytes_to_write - i);
			}

			copy_memory(random_data, bytes_written, memory_write_to, bytes_to_write);
		}

		// THROWS: windows_api_failure
		// SAFE GUARANTEE: basic
		// SIDE EFFECTS: -
		void generate_random(_In_ const provider& csp, _Out_ byte* buffer, size_t buffer_size)
		{
			if(FALSE == ::CryptGenRandom(csp, buffer_size, buffer))
			{
				const DWORD code = ::GetLastError();
				throw windows_api_failure(__FUNCTIONW__, L"Unable to fill a buffer with cryptographically random bytes.", code);
			}
		}
	}
}
