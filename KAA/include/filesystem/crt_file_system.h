#pragma once

#include "driver.h"

namespace KAA
{
	namespace filesystem
	{
		class crt_file_system final : public driver
		{
		private:
			void icreate_directory(const path::directory&) override;
			void iremove_directory(const path::directory&) override;

			std::unique_ptr<file> iopen_file(const path::file&, const mode&, const share&) const override;
			std::unique_ptr<file> icreate_file(const path::file&, const create_mode&, const mode&, const share&, const permission&) override;

			path::file iget_temp_filename(const path::directory&) const override;

			void irename_file(const path::file&, const path::file&) override;
			void iremove_file(const path::file&) override;

			bool ifile_exists(const path::file&) const override;

			void iset_file_permissions(const path::file&, const permission&) override;
			permission iget_file_permissions(const path::file&) const override;
		};
	}
}
