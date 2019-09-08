//
// File: critical_section.h
// Description: synchronization point
// Created: July 20, 2018
// Author: Andrey A. Katentsev
//
// Copyright © Andrey A. Katentsev, 2018
//

#pragma once

#include "lock.h"

#include <windows.h>

namespace KAA
{
	namespace synchronization
	{
		class critical_section final : public lock
		{
		public:
			critical_section();
			critical_section(unsigned int spin_count, bool debug = false);
			~critical_section();

			critical_section(const critical_section&) = delete;
			critical_section(critical_section&&) = delete;

			critical_section& operator = (const critical_section&) = delete;
			critical_section& operator = (critical_section&&) = delete;

		private:
			void iseize(void) override;
			void irelease(void) override;

			::CRITICAL_SECTION mutex;
		};
	}
}
