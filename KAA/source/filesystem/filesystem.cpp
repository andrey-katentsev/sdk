//
// File: filesystem.cpp
// Description: basic file system commands and requests
// Created: February 22, 2014
// Author: Andrey A. Katentsev
//
// Copyright © Andrey A. Katentsev, 2014
//

#include "../../include/exception/system_failure.h"
#include "../../include/filesystem/driver.h"
#include "../../include/filesystem/filesystem.h"
#include "../../include/filesystem/path.h"

namespace KAA
{
	namespace filesystem
	{
		// TODO: KAA: consider the filesystem::driver to not throw in this case (or reimplement as a part of filesystem::driver).
		bool file_exists(const driver& filesystem, const path::file& path)
		try
		{
			return filesystem.get_file_permissions(path).m_exist;
		}
		catch (const KAA::system_failure& error)
		{
			if (ENOENT == error)
				return false;
			throw;
		}

		_fsize_t get_file_size(const driver& filesystem, const path::file& path)
		{
			const driver::mode query_attributes_only { false, false };
			const driver::share share_any_access;
			return filesystem.open_file(path, query_attributes_only, share_any_access)->get_size();
		}

		void set_file_size(const driver& filesystem, const path::file& path, const _fsize_t size)
		{
			const driver::mode write_only { true, false };
			const driver::share share_any_access;
			return filesystem.open_file(path, write_only, share_any_access)->set_size(size);
		}
	}
}
