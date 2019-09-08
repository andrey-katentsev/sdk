//
// File: cursor.h
// Description: user interface helper to operate with system cursor
// Created: May 24, 2015
// Author: Andrey A. Katentsev
//
// Copyright 2015 Andrey A. Katentsev
//

#pragma once

// FUTURE: KAA: consider to remove this header.
#include <windows.h>

namespace KAA
{
	namespace user_interface
	{
		namespace cursor
		{
			::POINT get_coordinates(void);
		}
	}
}
