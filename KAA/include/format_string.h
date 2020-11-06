//
// File: format_string.h
// Description: string format helper
// Created: April 24, 2013
// Author: Andrey A. Katentsev
//
// Copyright © Andrey A. Katentsev, 2013
//

#pragma once

#include <string>

namespace KAA
{
	std::string format_string(std::string format, ...);
	std::wstring format_string(std::wstring format, ...);
}
