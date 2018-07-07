//
// File: path.h
// Description: drive, directory, and file_path class type
// Created: June 24, 2018
// Author: Andrey A. Katentsev
//
// Copyright © Andrey A. Katentsev, 2018
//

#pragma once

#include <string>

namespace KAA
{
	namespace filesystem
	{
		namespace path
		{
			class drive
			{
			public:
				explicit drive(const std::wstring& drive);

				std::wstring to_wstring(void) const;

			private:
				std::wstring root;
			};

			class directory
			{
			public:
				explicit directory(const std::wstring& path);

				std::wstring to_wstring(void) const;

			private:
				std::wstring path;
			};

			class file
			{
			public:
				explicit file(const std::wstring& path);

				directory get_directory(void) const;
				std::wstring get_filename(void) const;

				std::wstring to_wstring(void) const;

			private:
				std::wstring path;
			};

			class extension
			{
			public:
				explicit extension(const std::wstring& extension);

				std::wstring to_wstring(void) const;

			private:
				std::wstring ext;
			};

			bool operator == (const directory&, const directory&);
			bool operator != (const directory&, const directory&);

			// EXAMPLE: D:\Temp + file.dat = D:\Temp\file.dat
			file operator + (const directory&, const std::wstring& filename);

			// EXAMPLE: 'D:\Temp\'
			std::wstring append_trailing_backslash(const std::wstring& directory_path);
			// EXAMPLE: 'D:\Temp'
			std::wstring remove_trailing_backslash(const std::wstring& directory_path);

			// EXAMPLE: 'D:\Temp'
			std::wstring make_WinAPI_directory_path(const std::wstring& directory_path);
			// EXAMPLE: 'D:\Temp\'
			std::wstring make_CRT_directory_path(const std::wstring& directory_path);
		}
	}
}
