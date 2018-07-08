//
// File: cryptography.h
// Description: cryptography API (based on Windows CryptoAPI)
// Created: May 17, 2013
// Author: Andrey A. Katentsev
//
// Copyright © Andrey A. Katentsev, 2013
//

#pragma once

#include <vector>
#include <cstdint>
// FUTURE: KAA: consider to remove this header.
#include <windows.h>

namespace KAA
{
	namespace cryptography
	{
		// FUTURE: KAA: abstract base class required.
		// FUTURE: KAA: complete.
		// Used to acquire a handle to a particular key container within a particular cryptographic service provider (CSP).
		class provider
		{
		public:
			provider(LPCWSTR wzContainer, LPCWSTR wzProvider, DWORD dwProviderType, DWORD dwFlags);
			provider(const provider&) = delete;
			provider(provider&&) = delete;
			~provider();

			provider& operator = (const provider&) = delete;
			provider& operator = (provider&&) = delete;

			operator HCRYPTPROV (void) const;

		private:
			HCRYPTPROV m_handle;
		};

		// FUTURE: KAA: complete.
		// Initiates the hashing of a stream of data.
		class hash
		{
		public:
			hash(const provider&, ALG_ID algorithm, HCRYPTKEY hKey, DWORD dwFlags);
			hash(const hash&) = delete;
			hash(hash&&) = delete;
			~hash();

			hash& operator = (const hash&) = delete;
			hash& operator = (hash&&) = delete;

			operator HCRYPTHASH (void) const;

		private:
			HCRYPTHASH m_hash;
		};

		void gamma(const void* source, const void* key, void* destination, size_t size);
		void generate(size_t, void*);
		void generate_random(_In_ const provider&, _Out_ byte* buffer, size_t buffer_size);

		// Typically, only a user with the same logon credential as the user who encrypted the data can decrypt the data.
		// In addition, the encryption and decryption usually must be done on the same computer.
		// However, a user with a roaming profile can decrypt the data from another computer on the network.
		std::vector<uint8_t> protect_data(const void* source, size_t size);

		// Usually, the only user who can decrypt the data is a user with the same logon credentials as the user who encrypted the data.
		// In addition, the encryption and decryption must be done on the same computer.
		std::vector<uint8_t> unprotect_data(const void* source, size_t size);
	}
}
