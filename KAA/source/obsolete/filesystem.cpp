//
// File: filesystem.cpp
// Description: file system helpers
// Created: April 25, 2013
// Author: Andrey A. Katentsev
//
// Copyright (C) 2013, Hyperlink Software.
//

#include "..\include\filesystem.h"
#include <windows.h>

namespace KAA
{
	namespace FileSystem
	{
		bool IsPathAvailable(const std::wstring& wstrPath)
		{
			return INVALID_FILE_ATTRIBUTES != GetFileAttributesW(wstrPath.c_str());
		}
	} // namespace FileSystem
} // namespace KAA