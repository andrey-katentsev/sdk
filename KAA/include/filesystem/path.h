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
		}
	}
}
