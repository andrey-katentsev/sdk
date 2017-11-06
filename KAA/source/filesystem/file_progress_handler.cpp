//
// File: file_progress_handler.cpp
// Description: file progress callback
// Created: March 8, 2014
// Author: Andrey A. Katentsev
//
// Copyright © Andrey A. Katentsev, 2014
//

#include "../../include/filesystem/file_progress_handler.h"

namespace KAA
{
	namespace filesystem
	{
		progress_state file_progress_handler::chunk_processed(_fsize_t total_processed, _fsize_t total_size)
		{
			return ichunk_processed(total_processed, total_size);
		}
	}
}
