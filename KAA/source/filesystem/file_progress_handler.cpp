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
		progress_state_t file_progress_handler::chunk_processed(size_t bytes_processed)
		{
			return ichunk_processed(bytes_processed);
		}
	}
}
