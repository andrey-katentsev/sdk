//
// File: provider.h
// Description: handle to a cryptographic service provider (CSP)
// Created: September 22, 2019
// Author: Andrey A. Katentsev
//
// Copyright © Andrey A. Katentsev, 2019
//

#pragma once

#include <cstdint>

namespace KAA
{
	namespace cryptography
	{
		class provider
		{
		public:
			virtual ~provider() = default;
			std::uintptr_t get_handle(void) const noexcept;

		private:
			virtual std::uintptr_t iget_handle(void) const noexcept = 0;
		};
	}
}
