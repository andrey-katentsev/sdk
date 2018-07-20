//
// File: lock.h
// Description: synchronization point
// Created: July 19, 2018
// Author: Andrey A. Katentsev
//
// Copyright © Andrey A. Katentsev, 2018
//

#pragma once

namespace KAA
{
	namespace synchronization
	{
		class lock
		{
		public:
			virtual ~lock() = default;

			void seize(void);
			void release(void);

		private:
			virtual void iseize(void) = 0;
			virtual void irelease(void) = 0;
		};
	}
}
