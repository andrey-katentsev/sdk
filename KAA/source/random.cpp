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

#include "../include/exception/system_failure.h"
#include "../include/RAII/invalid_parameter_handler.h"

namespace
{
	void allow_execution(const wchar_t*, const wchar_t*, const wchar_t*, unsigned int, uintptr_t) { return; }
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
	}
}
