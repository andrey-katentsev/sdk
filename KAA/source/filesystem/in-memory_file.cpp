//
// File: in-memory_file.cpp
// Description: in-memory [RAM] file
// Created: July 1, 2018
// Author: Andrey A. Katentsev
//
// Copyright © Andrey A. Katentsev, 2018
//

#include "../../include/filesystem/in-memory_file.h"

#include <stdexcept>

namespace KAA
{
	namespace filesystem
	{
		in_memory_file::in_memory_file(const std::shared_ptr<std::vector<uint8_t>> descriptor) :
		descriptor(descriptor)
		{}

		size_t in_memory_file::iread(const size_t bytes_to_read, void* buffer) const
		{
			throw std::logic_error { "not implemented" };
		}

		size_t in_memory_file::iwrite(const void* buffer, const size_t bytes_to_write)
		{
			throw std::logic_error { "not implemented" };
		}

		void in_memory_file::icommit(void)
		{
			throw std::logic_error { "not implemented" };
		}

		_fsize_t in_memory_file::iget_size(void) const
		{
			throw std::logic_error { "not implemented" };
		}

		void in_memory_file::iset_size(const _fsize_t size)
		{
			throw std::logic_error { "not implemented" };
		}

		_off_t in_memory_file::itell(void) const
		{
			throw std::logic_error { "not implemented" };
		}

		void in_memory_file::iseek(const _off_t offset, const origin from)
		{
			throw std::logic_error { "not implemented" };
		}
	}
}
