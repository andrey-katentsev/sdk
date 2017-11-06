//
// File: calendar_date.cpp
// Description:
// Created: May 24, 2015
// Author: Andrey A. Katentsev
//
// Copyright 2015 Andrey A. Katentsev
//

#include "../../include/time/calendar_date.h"

namespace KAA
{
	namespace time
	{
		std::tm calendar_date(unsigned short day, unsigned short month, unsigned int year)
		{
			std::tm date = { 0 };

			date.tm_year = year - 1900; // years since 1900
			date.tm_mon = month - 1; // months since January - [0,11]
			date.tm_mday = day; // day of the month - [1,31]

			std::mktime(&date); // normalize (validate and fill) specified date

			return date;
		}
	}
}
