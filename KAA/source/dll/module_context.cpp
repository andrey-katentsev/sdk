#include "../../include/dll/module_context.h"
#include <vector>
#include "../../include/exception/windows_api_failure.h"
#include <psapi.h>
#pragma comment(lib, "psapi.lib")

namespace KAA
{
	namespace dll
	{
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
