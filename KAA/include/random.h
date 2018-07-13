//
// File: random.h
// Description: pseudorandom number generator
// Created: August 18, 2013
// Author: Andrey A. Katentsev
//
// Copyright © Andrey A. Katentsev, 2013
//

#include <vector>

namespace KAA
{
	namespace cryptography
	{
		unsigned int random(void);
		std::vector<uint8_t> generate(size_t);
		size_t generate(const size_t, void*);
	}
}
