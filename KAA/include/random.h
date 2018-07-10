//
// File: random.h
// Description: pseudorandom number generator
// Created: August 18, 2013
// Author: Andrey A. Katentsev
//
// Copyright © Andrey A. Katentsev, 2013
//

namespace KAA
{
	namespace cryptography
	{
		unsigned int random(void);
		void generate(size_t, void*);
	}
}
