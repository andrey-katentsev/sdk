//
// File: in-memory_file_system.cpp
// Description: in-memory [RAM] filesystem
// Created: June 30, 2018
// Author: Andrey A. Katentsev
//
// Copyright © Andrey A. Katentsev, 2018
//

#include "../../include/filesystem/in-memory_file_system.h"

#include <stdexcept>

#include "../../include/convert.h"
#include "../../include/random.h"
#include "../../include/exception/operation_failure.h"
#include "../../include/filesystem/in-memory_file.h"

namespace KAA
{
	namespace filesystem
	{
		void in_memory_file_system::icreate_directory(const path::directory& path)
		{
			const auto directory = path.to_wstring();
			if (vfs.end() == vfs.find(directory))
				vfs[directory];
			else
				throw std::runtime_error { "directory already exists" };
		}

		void in_memory_file_system::iremove_directory(const path::directory& path)
		{
			const auto directory = path.to_wstring();
			if (vfs.end() != vfs.find(directory))
				vfs.erase(directory);
			else
				throw std::runtime_error { "directory does not exist" };
		}

		std::unique_ptr<file> in_memory_file_system::iopen_file(const path::file&, const mode&, const share&) const
		{
			throw std::runtime_error { "not implemented" };
		}

		std::unique_ptr<file> in_memory_file_system::icreate_file(const path::file& path, const create_mode& lifetime, const mode& operations_allowed, const share& sharing_allowed, const permission& attributes)
		{
			const auto filename = path.to_wstring();
			if (vfs.end() == vfs.find(filename))
			{
				auto& descriptor = vfs[filename];
				descriptor.reset(new std::vector<uint8_t>());
				return std::make_unique<in_memory_file>(descriptor);
			}
			else
				throw std::runtime_error { "directory already exists" };
		}

		path::file in_memory_file_system::iget_temp_filename(const path::directory& path) const
		{
			return path + convert::to_wstring(static_cast<unsigned long>(cryptography::random()), 36);
		}

		void in_memory_file_system::irename_file(const path::file& from, const path::file& to)
		{
			const auto present_filename = from.to_wstring();
			if (vfs.end() != vfs.find(present_filename))
			{
				const auto new_filename = to.to_wstring();
				if (vfs.end() == vfs.find(new_filename))
				{
					vfs[new_filename].swap(vfs[present_filename]);
					vfs.erase(present_filename);
				}
				else
					throw std::runtime_error { "file already exists" };
			}
			else
				throw std::runtime_error { "file does not exist" };
		}

		void in_memory_file_system::iremove_file(const path::file& path)
		{
			const auto filename = path.to_wstring();
			if (vfs.end() != vfs.find(filename))
				vfs.erase(filename);
			else
				throw std::runtime_error { "file does not exist" };
		}

		void in_memory_file_system::iset_file_permissions(const path::file& path, const permission& attributes)
		{
			throw std::runtime_error { "not implemented" };
		}

		driver::access in_memory_file_system::iget_file_permissions(const path::file& path) const
		{
			throw std::runtime_error { "not implemented" };
		}
	}
}
