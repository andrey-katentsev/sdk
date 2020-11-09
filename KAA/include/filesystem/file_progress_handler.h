//
// File: file_progress_handler.h
// Description: file progress callback
// Created: March 8, 2014
// Author: Andrey A. Katentsev
//
// Copyright © Andrey A. Katentsev, 2014
//

#pragma once

#include <io.h>

#include "../../include/progress_state.h"

namespace KAA
{
	namespace filesystem
	{
		class file_progress_handler
		{
		public:
			progress_state_t chunk_processed(size_t bytes_processed);

		private:
			virtual progress_state_t ichunk_processed(size_t bytes_processed) = 0;
		};
	}
}
