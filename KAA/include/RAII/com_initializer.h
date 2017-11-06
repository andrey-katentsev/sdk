//
// File: com.h
// Description: resource handle for windows component object model initialization
// Created: May 25, 2013
// Author: Andrey A. Katentsev
//
// Copyright © Andrey A. Katentsev, 2013
//

#include <windows.h>

namespace KAA
{
	namespace RAII
	{
		class com_initializer
		{
		public:
			com_initializer(DWORD);
			~com_initializer();

		private:
			// FUTURE: C++11: move semantics, = delete.
			com_initializer(const com_initializer&);
			com_initializer& operator = (const com_initializer&);
		};
	}
}
