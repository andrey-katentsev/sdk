//
// File: hash.cpp
// Description: handle to a cryptographic service provider (CSP) hash object
// Created: September 22, 2019
// Author: Andrey A. Katentsev
//
// Copyright © Andrey A. Katentsev, 2019
//

#include "../../include/cryptography/hash.h"

namespace KAA
{
	namespace cryptography
	{
		std::uintptr_t hash::get_handle(void) const noexcept
		{
			return iget_handle();
		}
	}
}
