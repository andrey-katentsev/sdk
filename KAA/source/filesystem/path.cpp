#include "../../include/filesystem/path.h"

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

			directory::directory(const std::wstring& path) : path(path)
			{}

			std::wstring directory::to_wstring(void) const
			{
				return path;
			}

			file::file(const std::wstring& path) : path(path)
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
		}
	}
}
