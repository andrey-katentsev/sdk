//
// File: md5.h
// Description: the MD5 message-digest algorithm
// Created: August 18, 2013
// Author: Andrey A. Katentsev
//
// Copyright © Andrey A. Katentsev, 2013
//

#pragma once

#include <string>
#include <cstdint>

namespace KAA
{
	namespace cryptography
	{
		struct md5
		{
			union
			{
				uint64_t qword[2];
				uint32_t dword[4];
				uint16_t word[8];
				uint8_t byte[16];
			};
		};

		bool operator == (const md5&, const md5&);
		bool operator != (const md5&, const md5&);

		// TODO: KAA: support multiple times call to compute the hash of long or discontinuous data streams.
		md5 calculate_md5(const void* data, size_t data_size);
	}

	namespace convert
	{
		std::wstring to_wstring(const cryptography::md5&);
	}
}
