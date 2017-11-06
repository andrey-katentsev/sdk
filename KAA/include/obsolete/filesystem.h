//
// File: filesystem.h
// Description: file system helpers
// Created: April 25, 2013
// Author: Andrey A. Katentsev
//
// Copyright (C) 2013, Hyperlink Software.
//

#pragma once

#include <string>

namespace KAA
{
	namespace FileSystem
	{
		bool IsPathAvailable(const std::wstring& wstrPath);
	} // namespace FileSystem
} // namespace KAA