//
// File: wiper.h
// Description: file wiper frame
// Created: February 3, 2014
// Author: Andrey A. Katentsev
//
// Copyright © Andrey A. Katentsev, 2014
//

#pragma once

#include <string>

namespace KAA
{
	namespace filesystem
	{
		class file_progress_handler;

		class wiper
		{
		public:
			virtual ~wiper();

			// ALGORITHM FRAME:
			// 1. overwrite file content
			// 2. truncate file (to zero size)
			// 3. rename file (to random name)
			// 4. remove renamed file
			void wipe_file(const std::wstring& path);

			file_progress_handler* set_progress_handler(file_progress_handler*);

		private:
			virtual void ioverwrite_file(const std::wstring& path);
			virtual void itruncate_file(const std::wstring& path);
			virtual std::wstring irename_file(const std::wstring& path);
			virtual void iremove_file(const std::wstring& path) = 0;

			virtual file_progress_handler* iset_progress_handler(file_progress_handler*) = 0;
		};
	}
}
