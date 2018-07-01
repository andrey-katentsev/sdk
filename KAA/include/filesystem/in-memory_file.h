//
// File: in-memory_file.h
// Description: in-memory [RAM] file
// Created: July 1, 2018
// Author: Andrey A. Katentsev
//
// Copyright © Andrey A. Katentsev, 2018
//

#pragma once

#include <memory>
#include <vector>

#include "file.h"

namespace KAA
{
	namespace filesystem
	{
		class in_memory_file final : public file
		{
		public:
			explicit in_memory_file(std::shared_ptr<std::vector<uint8_t>> descriptor);

		private:
			std::shared_ptr<std::vector<uint8_t>> descriptor;

			size_t iread(size_t, void*) const override;
			size_t iwrite(const void*, size_t) override;

			void icommit(void) override;

			_fsize_t iget_size(void) const override;
			void iset_size(_fsize_t) override;

			_off_t itell(void) const override;
			void iseek(_off_t, origin) override;
		};
	}
}
