//
// File: module_context.cpp
// Description: dynamic-link library tools
// Created: February 2, 2014
// Author: Andrey A. Katentsev
//
// Copyright © Andrey A. Katentsev, 2014
//

#include "../../include/dll/module_context.h"

#include "../../include/unicode.h"
#include "../../include/exception/windows_api_failure.h"

#include <stdexcept>
#include <vector>

#include <psapi.h>
#pragma comment(lib, "psapi.lib")

namespace KAA
{
	using namespace unicode;
	namespace dll
	{
		module_context::module_context() : m_module(nullptr)
		{}

		void module_context::initialize(HINSTANCE module)
		{
			if (!module)
				throw std::invalid_argument { "cannot initialize module context: invalid handle provided" };

			if (m_module)
				throw std::logic_error { "module context already initialized" };

			m_module = module;
		}

		// THROWS: windows_api_failure
		// SAFE GUARANTEE: strong
		// SIDE EFFECTS: -
		void module_context::disable_thread_notifications(void) const
		{
			if (0 == ::DisableThreadLibraryCalls(m_module))
			{
				const auto error = ::GetLastError();
				throw windows_api_failure { __FUNCTION__, "cannot disable the DLL_THREAD_ATTACH and DLL_THREAD_DETACH notifications for the dynamic-link library", error };
			}
		}

		// THROWS: windows_api_failure
		// SAFE GUARANTEE: strong
		// SIDE EFFECTS: -
		std::string module_context::get_module_base_name(void) const
		{
			std::vector<wchar_t> buffer(MAX_PATH);
			const DWORD name_length = ::GetModuleBaseNameW(::GetCurrentProcess(), m_module, buffer.data(), buffer.size());
			if(0 == name_length)
			{
				const DWORD error = ::GetLastError();
				throw windows_api_failure { __FUNCTION__, "cannot retrieve the base name of the specified module", error };
			}
			return to_UTF8(std::wstring(buffer.begin(), buffer.begin() + name_length));
		}

		HINSTANCE module_context::get_module_handle(void) const throw()
		{
			return m_module;
		}
	}
}
