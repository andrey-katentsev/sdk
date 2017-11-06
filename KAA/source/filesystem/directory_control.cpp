#include "../../include/filesystem/directory_control.h"

namespace KAA
{
	namespace filesystem
	{
		directory_control::~directory_control()
		{}

		std::wstring directory_control::get_current_working_directory(void) const
		{
			return iget_current_working_directory();
		}

		void directory_control::set_current_working_directory(const std::wstring& path)
		{
			return iset_current_working_directory(path);
		}
	}
}
