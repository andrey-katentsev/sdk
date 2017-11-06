//
// File: md5.h
// Description: the MD5 message-digest algorithm
// Created: August 18, 2013
// Author: Andrey A. Katentsev
//
// Copyright (C) 2013, Hyperlink Software.
//

#pragma once

#include "../include/cryptography.h"
#include "../include/stdtypes.h"

#include <string>

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
		std::wstring to_wstring(const md5&);

		md5 calculate_md5(const provider&, const void* data, size_t data_size);
	}
}
