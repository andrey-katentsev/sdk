#include "../../include/filesystem/path.h"

#include <algorithm>

// TODO: KAA: remove separators dublicate (e.g. C://temp///file.dat)
// TODO: KAA: remove trailing separator for directories.
// TODO: KAA: directory + name + extension = file

namespace
{
	constexpr auto slash = L'/';
	constexpr auto backslash = L'\\';

	// Replaces all backslashes with slashes.
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
			drive::drive(const std::wstring& drive) : root(drive)
			{}

			std::wstring drive::to_wstring(void) const
			{
				return root;
			}

			directory::directory(const std::wstring& path) : path(make_consistent(path))
			{}

			std::wstring directory::to_wstring(void) const
			{
				return path;
			}

			file::file(const std::wstring& path) : path(make_consistent(path))
			{}

			std::wstring file::to_wstring(void) const
			{
				return path;
			}

			extension::extension(const std::wstring& extension) : ext(extension)
			{}

			std::wstring extension::to_wstring(void) const
			{
				return ext;
			}

			bool operator == (const directory& left, const directory& right)
			{
				return left.to_wstring() == right.to_wstring();
			}

			bool operator != (const directory& left, const directory& right)
			{
				return !(left == right);
			}

			file operator + (const directory& directory, const std::wstring& filename)
			{
				return file { append_trailing_backslash(directory.to_wstring()) + filename };
			}

			std::wstring append_trailing_backslash(const std::wstring& directory_path)
			{
				const auto append_backslash = (backslash != directory_path[directory_path.length() - 1]);
				return append_backslash ? directory_path + backslash : directory_path;
			}

			std::wstring remove_trailing_backslash(const std::wstring& directory_path)
			{
				const auto remove_backslash = (backslash == directory_path[directory_path.length() - 1]);
				return remove_backslash ? std::wstring { directory_path.begin(), directory_path.end() - 1 } : directory_path;
			}

			std::wstring make_WinAPI_directory_path(const std::wstring& directory_path)
			{
				return remove_trailing_backslash(directory_path);
			}

			std::wstring make_CRT_directory_path(const std::wstring& directory_path)
			{
				return append_trailing_backslash(directory_path);
			}
		}
	}
}
