#include "../../include/filesystem/directory_control.h"

namespace KAA
{
	namespace filesystem
	{
		path::directory directory_control::get_current_working_directory(void) const
		{
			return iget_current_working_directory();
		}

		void directory_control::set_current_working_directory(const path::directory& path)
		{
			return iset_current_working_directory(path);
		}
	}
}
