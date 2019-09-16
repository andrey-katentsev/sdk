#include "../../include/dll/module_context.h"

#include <stdexcept>
#include <vector>

#include "../../include/exception/windows_api_failure.h"

#include <psapi.h>
#pragma comment(lib, "psapi.lib")

namespace KAA
{
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
				throw windows_api_failure(__FUNCTIONW__, L"failed to disable the DLL_THREAD_ATTACH and DLL_THREAD_DETACH notifications for the dynamic-link library.", error);
			}
		}

		// THROWS: windows_api_failure
		// SAFE GUARANTEE: strong
		// SIDE EFFECTS: -
		std::wstring module_context::get_module_base_name(void) const
		{
			std::vector<wchar_t> buffer(MAX_PATH);
			const DWORD name_length = ::GetModuleBaseNameW(::GetCurrentProcess(), m_module, &buffer[0], buffer.size());
			if(0 == name_length)
			{
				const DWORD error = ::GetLastError();
				throw windows_api_failure(__FUNCTIONW__, L"Unable to retrieve the module base name.", error);
			}
			return std::wstring(buffer.begin(), buffer.begin() + name_length);
		}

		HINSTANCE module_context::get_module_handle(void) const throw()
		{
			return m_module;
		}
	}
}
