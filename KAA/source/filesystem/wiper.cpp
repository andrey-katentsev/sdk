//
// File: wiper.cpp
// Description: file wiper frame
// Created: February 3, 2014
// Author: Andrey A. Katentsev
//
// Copyright © Andrey A. Katentsev, 2014
//

#include "../../include/filesystem/wiper.h"

namespace KAA
{
	namespace filesystem
	{
		void wiper::wipe_file(const std::wstring& path)
		{
			ioverwrite_file(path);
			itruncate_file(path);
			return iremove_file(irename_file(path));
		}

		file_progress_handler* wiper::set_progress_handler(file_progress_handler* const handler)
		{
			return iset_progress_handler(handler);
		}

		void wiper::ioverwrite_file(const std::wstring&)
		{}

		void wiper::itruncate_file(const std::wstring&)
		{}

		std::wstring wiper::irename_file(const std::wstring& path)
		{
			return path;
		}
	}
}
