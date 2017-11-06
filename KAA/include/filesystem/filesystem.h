// Feb 22, 2014

#include <string>

namespace KAA
{
	namespace filesystem
	{
		class driver;

		_fsize_t get_file_size(const driver&, const std::wstring& path);
	}
}
