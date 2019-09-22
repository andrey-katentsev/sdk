#include "../../include/filesystem/driver.h"
#include <stdexcept>

namespace KAA
{
	namespace filesystem
	{
		void driver::create_directory(const path::directory& path)
		{
			return icreate_directory(path);
		}

		void driver::remove_directory(const path::directory& path)
		{
			return iremove_directory(path);
		}

		std::unique_ptr<file> driver::open_file(const path::file& path, const mode& operations_allowed, const share& sharing_allowed) const
		{
			return iopen_file(path, operations_allowed, sharing_allowed);
		}

		std::unique_ptr<file> driver::create_file(const path::file& path, const create_mode& lifetime, const mode& operations_allowed, const share& sharing_allowed, const permission& attributes)
		{
			return icreate_file(path, lifetime, operations_allowed, sharing_allowed, attributes);
		}

		path::file driver::get_temp_filename(const path::directory& path) const
		{
			return iget_temp_filename(path);
		}

		void driver::rename_file(const path::file& from, const path::file& to)
		{
			return irename_file(from, to);
		}

		void driver::remove_file(const path::file& path)
		{
			return iremove_file(path);
		}

		void driver::delete_file(const path::file& path)
		{
			return remove_file(path);
		}

		bool driver::file_exists(const path::file& path) const
		{
			return ifile_exists(path);
		}

		void driver::set_file_permissions(const path::file& path, const permission& attributes)
		{
			return iset_file_permissions(path, attributes);
		}

		driver::permission driver::get_file_permissions(const path::file& path) const
		{
			return iget_file_permissions(path);
		}
	}
}
