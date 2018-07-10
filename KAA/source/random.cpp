//
// File: random.cpp
// Description: pseudorandom number generator
// Created: August 18, 2013
// Author: Andrey A. Katentsev
//
// Copyright (C) 2013, Hyperlink Software.
//

#include "../include/random.h"

#define _CRT_RAND_S
#include <cstdlib>

#include <algorithm>
#include <vector>

#include <memory.h>

#include "../include/exception/system_failure.h"
#include "../include/RAII/invalid_parameter_handler.h"

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
					throw system_failure(__FUNCTIONW__, L"Unable to generate a pseudorandom number.", error);
				}

				return value;
			}
		}

		// Генерирование (криптографически) случайных данных.
		void generate(const size_t bytes_to_write, void* memory_write_to)
		{
			unsigned int value = 0;
			const size_t chunk_size = sizeof(value);

			std::vector<uint8_t> buffer(bytes_to_write, 0);
			uint8_t* random_data = &buffer[0];

			size_t bytes_written = 0;

			for (size_t i = 0; i < bytes_to_write; i += chunk_size)
			{
				value = random();
				bytes_written += copy_memory(&value, chunk_size, random_data + i, bytes_to_write - i);
			}

			copy_memory(random_data, bytes_written, memory_write_to, bytes_to_write);
		}
	}
}
