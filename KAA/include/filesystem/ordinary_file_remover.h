// 08/02/2014

#pragma once

#include "wiper.h"

namespace KAA
{
	namespace filesystem
	{
		class driver;

		// REMARKS: do not takes ownership over provided filesystem::driver.
		class ordinary_file_remover : public wiper
		{
		public:
			ordinary_file_remover(driver*);

		private:
			driver* m_filesystem;

			void iremove_file(const path::file&) override;

			file_progress_handler* iset_progress_handler(file_progress_handler*) override;
		};
	}
}
