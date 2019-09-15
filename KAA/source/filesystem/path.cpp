#include "../../include/filesystem/path.h"
#include <algorithm>
#include "../../include/filesystem/split_path.h"

// TODO: KAA: throw if empty.
// TODO: KAA: remove separators dublicate (e.g. C://temp///file.dat)
// TODO: KAA: remove trailing separator for directories.
// TODO: KAA: directory + name + extension = file
// TODO: KAA: operator std::wstring (void) const;

namespace
{
	constexpr auto slash = L'/';
	constexpr auto backslash = L'\\';

	// Replaces all slashes with backslashes.
	// EXAMPLE: D:\Temp\file.dat
	std::wstring make_consistent(std::wstring path)
	{
		std::replace(path.begin(), path.end(), slash, backslash);
		return path;
	}
}

namespace KAA
{
	namespace filesystem
	{
		namespace path
		{
			drive::drive(std::wstring drive) : root(std::move(drive))
			{}

			std::wstring drive::to_wstring(void) const
			{
				return root;
			}

			directory::directory(std::wstring path) : path(make_consistent(std::move(path)))
			{}

			std::wstring directory::to_wstring(void) const
			{
				return path;
			}

			file::file(std::wstring path) : path(make_consistent(std::move(path)))
			{}

			directory file::get_directory(void) const
			{
				return split_directory(path);
			}

			std::wstring file::get_filename(void) const
			{
				return split_filename(path);
			}

			std::wstring file::to_wstring(void) const
			{
				return path;
			}

			extension::extension(std::wstring extension) : extension_(std::move(extension))
			{}

			std::wstring extension::to_wstring(void) const
			{
				return extension_;
			}

			bool operator == (const directory& left, const directory& right)
			{
				return left.to_wstring() == right.to_wstring();
			}

			bool operator != (const directory& left, const directory& right)
			{
				return !(left == right);
			}

			bool operator == (const file& left, const file& right)
			{
				return left.to_wstring() == right.to_wstring();
			}

			bool operator != (const file& left, const file& right)
			{
				return !(left == right);
			}

			file operator + (const directory& directory, std::wstring filename)
			{
				return append_trailing_backslash(directory.to_wstring()) + std::move(filename);
			}

			std::wstring append_trailing_backslash(std::wstring path)
			{
				if (backslash != path.back())
					path.push_back(backslash);
				return path;
			}

			std::wstring remove_trailing_backslash(std::wstring path)
			{
				if (backslash == path.back())
					path.pop_back();
				return path;
			}

			std::wstring make_WinAPI_directory_path(std::wstring directory_path)
			{
				return remove_trailing_backslash(std::move(directory_path));
			}

			std::wstring make_CRT_directory_path(std::wstring directory_path)
			{
				return append_trailing_backslash(std::move(directory_path));
			}
		}
	}
}
