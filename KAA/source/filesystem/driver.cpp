#include "../../include/filesystem/driver.h"

#include <stdexcept>

namespace KAA
{
	namespace filesystem
	{
		driver::access::access(bool read, bool write, bool exist) :
		m_exist(exist),
		m_permission(write, read)
		{}

		void driver::create_directory(const path::directory& path)
		{
			return icreate_directory(path);
		}

		void driver::remove_directory(const path::directory& path)
		{
			return iremove_directory(path);
		}

		std::auto_ptr<file> driver::open_file(const path::file& path, const mode& operations_allowed, const share& sharing_allowed) const
		{
			return iopen_file(path, operations_allowed, sharing_allowed);
		}

		std::auto_ptr<file> driver::create_file(const path::file& path, const create_mode& lifetime, const mode& operations_allowed, const share& sharing_allowed, const permission& attributes)
		{
			return icreate_file(path, lifetime, operations_allowed, sharing_allowed, attributes);
		}

		std::wstring driver::get_temp_filename(void) const
		{
			return iget_temp_filename();
		}

		/*_fsize_t driver::get_file_size(const std::wstring& path) const
		{
			const mode attributes_only(false, false);
			const share any_access;
			const std::auto_ptr<file> handle(open_file(path, attributes_only, any_access));
			return get_file_size(*handle);
		}

		_fsize_t driver::get_file_size(const file& handle) const
		{
			return iget_file_size(handle);
		}

		void driver::set_file_size(const std::wstring& path) const
		{
			const mode write_only(true, false);
			const share any_access;
			const std::auto_ptr<file> handle(open_file(path, write_only, any_access));
			return set_file_size(*handle);
		}

		void driver::set_file_size(const file& handle) const
		{
			return iset_file_size(handle);
		}*/

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

		void driver::set_file_permissions(const path::file& path, const permission& attributes)
		{
			return iset_file_permissions(path, attributes);
		}

		driver::access driver::get_file_permissions(const path::file& path) const
		{
			return iget_file_permissions(path);
		}

		// NOTES: KAA: excessive (but very useful).
		//bool driver::is_path_exists(const std::wstring& path)
		//{
			//return iis_path_exists(path);
		//}

		/*std::auto_ptr<driver> create_file_system(const file_system_t type)
		{
			switch(type)
			{
			case crt_api:
				return std::auto_ptr<driver>(new crt_file_system);
			default:
				throw std::invalid_argument(__FUNCTION__);
			}
		}*/
	}
}
