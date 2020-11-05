//
// File: random.cpp
// Description: pseudorandom number generator
// Created: August 18, 2013
// Author: Andrey A. Katentsev
//
// Copyright © Andrey A. Katentsev, 2013
//

#define _CRT_RAND_S

#include "../../include/cryptography/random.h"

#include <algorithm>

#include <memory.h>
#include <stdlib.h>

#include "../../include/exception/operation_failure.h"
#include "../../include/exception/system_failure.h"
#include "../../include/RAII/invalid_parameter_handler.h"

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
			if (0 != error)
			{
				throw KAA::system_failure { __FUNCTION__, "failed to copy bytes between buffers", error };
			}
			return bytes_to_write;
		}
	}
}

namespace KAA
{
	namespace cryptography
	{
		// THROWS: system_failure
		// SAFE GUARANTEE: basic
		// SIDE EFFECTS: -
		// REMARKS: rand_s depends on the RtlGenRandom API, which is only available in Windows XP and later.
		unsigned int random(void)
		{
			KAA::RAII::invalid_parameter_handler session(allow_execution);
			{
				unsigned int value = 0;
				const errno_t error = ::rand_s(&value);
				if(0 != error)
				{
					throw system_failure { __FUNCTION__, "cannot generate a pseudorandom number", error };
				}
				return value;
			}
		}

		std::vector<uint8_t> generate(const size_t bytes_to_generate)
		{
			std::vector<uint8_t> data(bytes_to_generate);
			if (0 < bytes_to_generate)
				generate(bytes_to_generate, &data[0]);
			return data;
		}

		size_t generate(const size_t bytes_to_generate, void* memory_write_to)
		{
			if (!memory_write_to)
			{
				constexpr auto reason = operation_failure::status_code_t::invalid_argument;
				constexpr auto severity = operation_failure::severity_t::error;
				throw operation_failure { __FUNCTION__, "failed to generate random bytes", reason, severity };
			}

			size_t bytes_written = 0U;
			if (0 < bytes_to_generate)
			{
				unsigned int random_data = 0U;
				constexpr auto chunk_size = sizeof(random_data);
				for (size_t offset = 0U; offset < bytes_to_generate; offset += chunk_size)
				{
					random_data = KAA::cryptography::random();
					bytes_written += copy_memory(&random_data, chunk_size, static_cast<uint8_t*>(memory_write_to) + offset, bytes_to_generate - offset);
				}
			}
			return bytes_written;
		}
	}
}
