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
		class driver;
		namespace path
		{
			class file;
		}

		_fsize_t get_file_size(const driver&, const path::file&);
		void set_file_size(const driver&, const path::file&, const _fsize_t);
	}
}
