//
// File: cryptography.h
// Description: cryptography API (based on Windows CryptoAPI)
// Created: May 17, 2013
// Author: Andrey A. Katentsev
//
// Copyright (C) 2013, Hyperlink Software.
//

#pragma once

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
			~provider();

			operator HCRYPTPROV (void) const;

		private:
			HCRYPTPROV m_handle;

			provider(const provider&);
			provider& operator = (const provider&);

			#if(1500 < _MSC_VER)
			provider(provider&&);
			provider& operator = (provider&&);
			#endif
		};

		// FUTURE: KAA: complete.
		// Initiates the hashing of a stream of data.
		class hash
		{
		public:
			hash(const provider&, ALG_ID algorithm, HCRYPTKEY hKey, DWORD dwFlags);
			~hash();

			operator HCRYPTHASH (void) const;

		private:
			HCRYPTHASH m_hash;

			hash(const hash&);
			hash& operator = (const hash&);

			#if(1500 < _MSC_VER)
			hash(hash&&);
			hash& operator = (hash&&);
			#endif
		};

		void gamma(const void* source, const void* key, void* destination, size_t size);
		void generate(size_t, void*);
		void generate_random(_In_ const provider&, _Out_ byte* buffer, size_t buffer_size);
	}
}
