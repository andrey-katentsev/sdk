//
// File: path.h
// Description: drive, directory, file, and extension path class type
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
				drive(std::wstring drive);
				drive(const drive&) = default;
				drive(drive&&) = default;
				~drive() = default;

				drive& operator = (const drive&) = default;
				drive& operator = (drive&&) = default;

				std::wstring to_wstring(void) const;

			private:
				std::wstring root;
			};

			class directory
			{
			public:
				directory(std::wstring path);
				directory(const directory&) = default;
				directory(directory&&) = default;
				~directory() = default;

				directory& operator = (const directory&) = default;
				directory& operator = (directory&&) = default;

				std::wstring to_wstring(void) const;

			private:
				std::wstring path;
			};

			class file
			{
			public:
				file(std::wstring path);
				file(const file&) = default;
				file(file&&) = default;
				~file() = default;

				file& operator = (const file&) = default;
				file& operator = (file&&) = default;

				directory get_directory(void) const;
				std::wstring get_filename(void) const;

				std::wstring to_wstring(void) const;

			private:
				std::wstring path;
			};

			class extension
			{
			public:
				extension(std::wstring extension);
				extension(const extension&) = default;
				extension(extension&&) = default;
				~extension() = default;

				extension& operator = (const extension&) = default;
				extension& operator = (extension&&) = default;

				std::wstring to_wstring(void) const;

			private:
				std::wstring extension_;
			};

			// TODO: KAA: make a friend.
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
