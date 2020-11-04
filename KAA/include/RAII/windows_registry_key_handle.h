//
// File: windows_registry_key_handle.h
// Description: resource handle for windows registry key
// Created: January 26, 2014
// Author: Andrey A. Katentsev
//
// Copyright © Andrey A. Katentsev, 2014
//

#pragma once

#include <windows.h>

namespace KAA
{
	namespace RAII
	{
		class windows_registry_key_handle final
		{
		public:
			explicit windows_registry_key_handle(HKEY);
			windows_registry_key_handle(const windows_registry_key_handle&) = delete;
			windows_registry_key_handle(windows_registry_key_handle&&) = delete;
			windows_registry_key_handle& operator = (const windows_registry_key_handle&) = delete;
			windows_registry_key_handle& operator = (windows_registry_key_handle&&) = delete;
			~windows_registry_key_handle();

			operator HKEY (void) const noexcept;

		private:
			HKEY handle;
		};
	}
}
