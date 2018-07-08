// 08/02/2014

#pragma once

#include "wiper.h"

namespace KAA
{
	namespace filesystem
	{
		class driver;

		class ordinary_file_remover : public wiper
		{
		public:
			explicit ordinary_file_remover(std::shared_ptr<driver>);

		private:
			std::shared_ptr<driver> m_filesystem;

			void iremove_file(const path::file&) override;
			std::shared_ptr<file_progress_handler> iset_progress_handler(std::shared_ptr<file_progress_handler>) override;
		};
	}
}
