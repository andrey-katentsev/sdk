//
// File: filesystem.h
// Description: basic file system commands and requests
// Created: February 22, 2014
// Author: Andrey A. Katentsev
//
// Copyright © Andrey A. Katentsev, 2014
//

namespace KAA
{
	namespace filesystem
	{
		namespace path
		{
			class file;
		}

		class driver;

		_fsize_t get_file_size(const driver&, const path::file&);
	}
}
