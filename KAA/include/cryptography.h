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

namespace KAA
{
	namespace cryptography
	{
		class provider;

		void gamma(const void* source, const void* key, void* destination, size_t size);
		void generate_random(const provider&, void* buffer, size_t size);

		// Typically, only a user with the same logon credential as the user who encrypted the data can decrypt the data.
		// In addition, the encryption and decryption usually must be done on the same computer.
		// However, a user with a roaming profile can decrypt the data from another computer on the network.
		std::vector<uint8_t> protect_data(const void* source, size_t size);

		// Usually, the only user who can decrypt the data is a user with the same logon credentials as the user who encrypted the data.
		// In addition, the encryption and decryption must be done on the same computer.
		std::vector<uint8_t> unprotect_data(const void* source, size_t size);
	}
}
