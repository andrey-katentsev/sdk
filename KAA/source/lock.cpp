//
// File: lock.cpp
// Description: synchronization point
// Created: July 19, 2018
// Author: Andrey A. Katentsev
//
// Copyright © Andrey A. Katentsev, 2018
//

#include "../include/lock.h"

namespace KAA
{
	namespace synchronization
	{
		void lock::seize(void)
		{
			return iseize();
		}

		void lock::release(void)
		{
			return irelease();
		}
	}
}
