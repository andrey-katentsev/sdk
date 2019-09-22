//
// File: provider.cpp
// Description: handle to a cryptographic service provider (CSP)
// Created: September 22, 2019
// Author: Andrey A. Katentsev
//
// Copyright © Andrey A. Katentsev, 2019
//

#include "../../include/cryptography/provider.h"

namespace KAA
{
	namespace cryptography
	{
		std::uintptr_t provider::get_handle(void) const noexcept
		{
			return iget_handle();
		}
	}
}
