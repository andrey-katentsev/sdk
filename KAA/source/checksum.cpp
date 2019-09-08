//
// File: checksum.cpp
// Description: cyclic redundancy check
// Created: July 16, 2018
// Author: Andrey A. Katentsev
//
// Copyright © Andrey A. Katentsev, 2018
//

#include "../include/checksum.h"

#include <iso646.h>

namespace KAA
{
	namespace checksum
	{
		uint32_t crc32(const void* data, const size_t size, const uint32_t polynomial)
		{
			uint32_t checksum = 0xffffffff;
			for (register size_t i = 0; i < size; ++i)
			{
				checksum ^= static_cast<const uint8_t*>(data)[i];
				for (register auto bit = 0; bit < 8; ++bit)
					checksum = (checksum & 0x00000001) ? (checksum >> 1) xor polynomial : checksum >> 1;
			}
			return ~checksum;
		}

		// FUTURE: KAA: unreferenced (see polynomial).
		uint32_t append_crc32(const uint8_t* data, size_t size, uint32_t checksum)
		{
			checksum = ~checksum;
			while (size-- != 0)
			{
				unsigned long c = *data++;
				for (unsigned long i = 0; i < 8; ++i)
				{
					if (((checksum ^ c) & 1) != 0)
						checksum = (checksum >> 1) ^ 0xEDB88320;
					else
						checksum = (checksum >> 1);
					c >>= 1;
				}
			}
			return ~checksum;
		}
	}
}
