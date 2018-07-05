#pragma once

#include "driver.h"
#include "../../include/keywords.h"

namespace KAA
{
	namespace filesystem
	{
		class crt_file_system final : public driver
		{
		private:
			void icreate_directory(const path::directory&) override;
			void iremove_directory(const path::directory&) override;

			std::auto_ptr<file> iopen_file(const std::wstring&, const mode&, const share&) const override;
			std::auto_ptr<file> icreate_file(const std::wstring&, const create_mode&, const mode&, const share&, const permission&) override;

			std::wstring iget_temp_filename(void) const override;

			//_fsize_t iget_file_size(const file&) const;

			void irename_file(const std::wstring&, const std::wstring&) override;
			void iremove_file(const std::wstring&) override;

			void iset_file_permissions(const std::wstring&, const permission&) override;
			access iget_file_permissions(const std::wstring&) const override;
		};
	}
}
