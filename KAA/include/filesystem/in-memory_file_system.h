//
// File: in-memory_file_system.h
// Description: in-memory [RAM] filesystem
// Created: June 30, 2018
// Author: Andrey A. Katentsev
//
// Copyright © Andrey A. Katentsev, 2018
//

#pragma once

#include <map>
#include <memory>
#include <string>
#include <vector>

#include <cstdint>

#include "driver.h"

namespace KAA
{
	namespace filesystem
	{
		class in_memory_file_system final : public driver
		{
		private:
			void icreate_directory(const path::directory&) override;
			void iremove_directory(const path::directory&) override;

			std::auto_ptr<file> iopen_file(const path::file&, const mode&, const share&) const override;
			std::auto_ptr<file> icreate_file(const path::file&, const create_mode&, const mode&, const share&, const permission&) override;

			std::wstring iget_temp_filename(void) const override;

			void irename_file(const path::file&, const path::file&) override;
			void iremove_file(const path::file&) override;

			void iset_file_permissions(const path::file&, const permission&) override;
			access iget_file_permissions(const path::file&) const override;

			std::map<std::wstring, std::shared_ptr<std::vector<uint8_t>>> vfs;
		};
	}
}
