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
#include <string>
#include <vector>

#include "driver.h"

#include "../stdtypes.h"

namespace KAA
{
	namespace filesystem
	{
		class in_memory_file_system : public driver
		{
		private:
			void icreate_directory(const std::wstring&) override;
			void iremove_directory(const std::wstring&) override;

			std::auto_ptr<file> iopen_file(const std::wstring&, const mode&, const share&) const override;
			std::auto_ptr<file> icreate_file(const std::wstring&, const create_mode&, const mode&, const share&, const permission&) override;

			std::wstring iget_temp_filename(void) const override;

			void irename_file(const std::wstring&, const std::wstring&) override;
			void iremove_file(const std::wstring&) override;

			void iset_file_permissions(const std::wstring&, const permission&) override;
			access iget_file_permissions(const std::wstring&) const override;

			std::map<std::wstring, std::vector<uint8_t>> vfs;
		};
	}
}
