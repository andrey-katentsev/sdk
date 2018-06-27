#include "../../include/filesystem/path.h"

#include <algorithm>

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
		}
	}
}
