//
// File: com.cpp
// Description: resource handle for windows component object model initialization
// Created: May 25, 2013
// Author: Andrey A. Katentsev
//
// Copyright © Andrey A. Katentsev, 2013
//

#include "../../include/RAII/com_initializer.h"
#include "../../include/exception/com_failure.h"

#include <objbase.h>

namespace KAA
{
	namespace RAII
	{
		com_initializer::com_initializer(const DWORD options)
		{
			const HRESULT code = ::CoInitializeEx(nullptr, options);
			if(FAILED(code))
			{
				throw com_failure(__FUNCTIONW__, L"Unable to initialize the COM library.", code);
			}
		}

		com_initializer::~com_initializer()
		{
			::CoUninitialize();
		}
	}
}
