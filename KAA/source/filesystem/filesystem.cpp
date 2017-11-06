// Feb 22, 2014

#include "../../include/filesystem/driver.h"
#include "../../include/filesystem/filesystem.h"

namespace KAA
{
	namespace filesystem
	{
		_fsize_t get_file_size(const driver& filesystem, const std::wstring& path)
		{
			const driver::mode query_attributes_only(false, false);
			const driver::share share_any_access;
			return filesystem.open_file(path, query_attributes_only, share_any_access)->get_size();
		}
	}
}
