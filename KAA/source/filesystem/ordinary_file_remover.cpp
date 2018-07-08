#include "../../include/filesystem/ordinary_file_remover.h"
#include "../../include/filesystem/driver.h"

namespace KAA
{
	namespace filesystem
	{
		ordinary_file_remover::ordinary_file_remover(const std::shared_ptr<driver> filesystem) :
		m_filesystem(filesystem)
		{} // FIX: KAA: if(!filesystem) throw;

		void ordinary_file_remover::iremove_file(const path::file& path)
		{
			return m_filesystem->remove_file(path);
		}

		std::shared_ptr<file_progress_handler> ordinary_file_remover::iset_progress_handler(const std::shared_ptr<file_progress_handler>)
		{
			return nullptr;
		}
	}
}
