// 03/02/2014

#pragma once

#include "wiper.h"

#include <cstdint>

#include "../progress_state.h"

namespace KAA
{
	namespace filesystem
	{
		class driver;

		class simple_owerwrite_wiper : public wiper
		{
		public:
			simple_owerwrite_wiper(std::shared_ptr<driver>, uint8_t aggregate);

		private:
			std::shared_ptr<driver> m_filesystem;
			uint8_t m_aggregate;
			std::shared_ptr<file_progress_handler> progress_handler;

			void ioverwrite_file(const path::file&) override;
			void itruncate_file(const path::file&) override;
			path::file irename_file(const path::file&) override;
			void iremove_file(const path::file&) override;

			std::shared_ptr<file_progress_handler> iset_progress_handler(std::shared_ptr<file_progress_handler>) override;

			progress_state chunk_processed(_fsize_t total_processed, _fsize_t total_size);
		};
	}
}
