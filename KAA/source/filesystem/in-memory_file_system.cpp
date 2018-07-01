//
// File: in-memory_file_system.cpp
// Description: in-memory [RAM] filesystem
// Created: June 30, 2018
// Author: Andrey A. Katentsev
//
// Copyright © Andrey A. Katentsev, 2018
//

#include "../../include/filesystem/in-memory_file_system.h"

#include "../../include/convert.h"
#include "../../include/random.h"
#include "../../include/exception/operation_failure.h"
#include "../../include/filesystem/in-memory_file.h"

namespace KAA
{
	namespace filesystem
	{
		void in_memory_file_system::icreate_directory(const std::wstring& path)
		{
			if (vfs.end() == vfs.find(path))
				vfs[path];
			else
				throw std::logic_error { "directory already exists" };
		}

		void in_memory_file_system::iremove_directory(const std::wstring& path)
		{
			if (vfs.end() != vfs.find(path))
				vfs.erase(path);
			else
				throw std::logic_error { "directory does not exist" };
		}

		std::auto_ptr<file> in_memory_file_system::iopen_file(const std::wstring& path, const mode& operations_allowed, const share& sharing_allowed) const
		{
			throw std::logic_error { "not implemented" };
		}

		std::auto_ptr<file> in_memory_file_system::icreate_file(const std::wstring& path, const create_mode& lifetime, const mode& operations_allowed, const share& sharing_allowed, const permission& attributes)
		{
			if (vfs.end() == vfs.find(path))
			{
				auto& descriptor = vfs[path];
				descriptor.reset(new std::vector<uint8_t>());
				return std::auto_ptr<file>(new in_memory_file(descriptor));
			}
			else
				throw std::logic_error { "directory already exists" };
		}

		std::wstring in_memory_file_system::iget_temp_filename(void) const
		{
			return convert::to_wstring(static_cast<unsigned long>(cryptography::random()), 36);
		}

		void in_memory_file_system::irename_file(const std::wstring& present_filename, const std::wstring& new_filename)
		{
			if (vfs.end() != vfs.find(present_filename))
			{
				if (vfs.end() == vfs.find(new_filename))
				{
					vfs[new_filename].swap(vfs[present_filename]);
					vfs.erase(present_filename);
				}
				else
					throw std::logic_error { "file already exists" };
			}
			else
				throw std::logic_error { "file does not exist" };
		}

		void in_memory_file_system::iremove_file(const std::wstring& path)
		{
			if (vfs.end() != vfs.find(path))
				vfs.erase(path);
			else
				throw std::logic_error { "file does not exist" };
		}

		void in_memory_file_system::iset_file_permissions(const std::wstring& file_path, const permission& new_attributes)
		{
			throw std::logic_error { "not implemented" };
		}

		driver::access in_memory_file_system::iget_file_permissions(const std::wstring& file_path) const
		{
			throw std::logic_error { "not implemented" };
		}
	}
}
