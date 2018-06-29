#include "../../include/filesystem/path.h"

#include <algorithm>

// TODO: KAA: remove separators dublicate (e.g. C://temp///file.dat)
// TODO: KAA: remove trailing separator for directories.
// TODO: KAA: directory + filename = file
// TODO: KAA: directory + name + extension = file

namespace
{
	// Replaces all backslashes [/] with slashes [\].
	std::wstring make_consistent(const std::wstring& path)
	{
		auto consistent_path = path;
		std::replace(consistent_path.begin(), consistent_path.end(), L'/', L'\\');
		return consistent_path;
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

			// EXAMPLE: 'D:\Temp'
			std::wstring make_WinAPI_directory_path(const std::wstring& directory_path)
			{
				const auto remove_trailing_backslash = (L'\\' == directory_path[directory_path.length() - 1]);
				return remove_trailing_backslash ? std::wstring(directory_path.begin(), directory_path.end() - 1) : directory_path;
			}

			// EXAMPLE: 'D:\Temp\'
			std::wstring make_CRT_directory_path(const std::wstring& directory_path)
			{
				const auto add_trailing_backslash = (L'\\' != directory_path[directory_path.length() - 1]);
				return add_trailing_backslash ? directory_path + L'\\' : directory_path;
			}
		}
	}
}
