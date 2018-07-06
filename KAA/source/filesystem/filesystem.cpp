//
// File: filesystem.cpp
// Description: basic file system commands and requests
// Created: February 22, 2014
// Author: Andrey A. Katentsev
//
// Copyright © Andrey A. Katentsev, 2014
//

#include "../../include/filesystem/driver.h"
#include "../../include/filesystem/filesystem.h"
#include "../../include/filesystem/path.h"

namespace KAA
{
	namespace filesystem
	{
		_fsize_t get_file_size(const driver& filesystem, const path::file& path)
		{
			const driver::mode query_attributes_only(false, false);
			const driver::share share_any_access;
			return filesystem.open_file(path, query_attributes_only, share_any_access)->get_size();
		}
	}
}
