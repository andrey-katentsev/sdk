#include "../../include/filesystem/path.h"

namespace KAA
{
	namespace filesystem
	{
		namespace path
		{
			drive::drive(const std::wstring& drive) : root(drive)
			{}

			directory::directory(const std::wstring& path) : path(path)
			{}

			file::file(const std::wstring& path) : path(path)
			{}

			std::wstring file::to_wstring(void) const
			{
				return path;
			}

			extension::extension(const std::wstring& extension) : m_extension(extension)
			{}
		}
	}
}
