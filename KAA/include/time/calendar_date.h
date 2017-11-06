//
// File: calendar_date.h
// Description:
// Created: May 24, 2015
// Author: Andrey A. Katentsev
//
// Copyright 2015 Andrey A. Katentsev
//

#include <ctime>

namespace KAA
{
	namespace time
	{
		std::tm calendar_date(unsigned short day, unsigned short month, unsigned int year);
	}
}
