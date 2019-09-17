//
// File: checksum.h
// Description: cyclic redundancy check
// Created: July 16, 2018
// Author: Andrey A. Katentsev
//
// Copyright © Andrey A. Katentsev, 2018
//

#pragma once

#include <cstdint>

namespace KAA
{
	namespace checksum
	{
		// Normal / Reversed / Reverse of Reciprocal
		// CRC-32-IEEE 802.3: 0x04c11db7 / 0xedb88320 / 0x82608edb
		uint32_t crc32(const void* data, size_t size, uint32_t polynomial);
	}
}
