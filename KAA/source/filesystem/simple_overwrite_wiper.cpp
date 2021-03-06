#include "../../include/filesystem/simple_overwrite_wiper.h"

#include <stdexcept>
#include <vector>

#include "../../include/filesystem/driver.h"
#include "../../include/filesystem/file.h"
#include "../../include/filesystem/file_progress_handler.h"

namespace
{
	const KAA::filesystem::driver::share exclusive_access(false, false);
}

namespace KAA
{
	namespace filesystem
	{
		simple_owerwrite_wiper::simple_owerwrite_wiper(std::shared_ptr<driver> filesystem, const uint8_t aggregate) :
		m_filesystem(std::move(filesystem)),
		m_aggregate(aggregate),
		progress_handler(nullptr)
		{
			if(!m_filesystem)
				throw std::invalid_argument(__FUNCTION__);
		}

		// TODO: KAA: void simple_owerwrite_wiper::ioverwrite_file(std::unique_ptr<file>);
		void simple_owerwrite_wiper::ioverwrite_file(const path::file& path)
		{
			const driver::mode binary_sequential_overwrite(true, false, true, false);
			const auto file_to_overwrite = m_filesystem->open_file(path, binary_sequential_overwrite, exclusive_access);
			{
				const size_t chunk_size = (64 * 1024) - 1;
				const std::vector<uint8_t> chunk_data(chunk_size, m_aggregate);
				{
					const _fsize_t file_size = file_to_overwrite->get_size();
					{
						const unsigned total_chunks = file_size / chunk_size;
						for(unsigned chunk = 0; chunk < total_chunks; ++chunk)
						{
							chunk_processed(file_to_overwrite->write(chunk_data.data(), chunk_size)); // FUTURE: KAA: provide with progres_quiet support and etc.
						}
					}
					{
						const size_t last_chunk_size = file_size % chunk_size;
						chunk_processed(file_to_overwrite->write(chunk_data.data(), last_chunk_size));
					}
				}
			}
			file_to_overwrite->commit();
		}

		void simple_owerwrite_wiper::itruncate_file(const path::file& path)
		{
			const driver::mode truncate(true, false, true, false, false, true);
			const auto file_to_remove = m_filesystem->open_file(path, truncate, exclusive_access);
			file_to_remove->commit();
		}

		path::file simple_owerwrite_wiper::irename_file(const path::file& path)
		{
			const auto temporary_path = m_filesystem->get_temp_filename(path.get_directory());
			m_filesystem->rename_file(path, temporary_path);
			return temporary_path;
		}

		void simple_owerwrite_wiper::iremove_file(const path::file& path)
		{
			return m_filesystem->remove_file(path);
		}

		std::shared_ptr<file_progress_handler> simple_owerwrite_wiper::iset_progress_handler(std::shared_ptr<file_progress_handler> handler)
		{
			progress_handler.swap(handler);
			return handler;
		}

		progress_state_t simple_owerwrite_wiper::chunk_processed(size_t bytes_processed)
		{
			if(nullptr != progress_handler)
				return progress_handler->chunk_processed(bytes_processed);
			return progress_state_t::quiet;
		}
	}
}
