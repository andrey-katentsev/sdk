// 02/02/2014

#pragma once

#include <string>
#include <windows.h>

namespace KAA
{
	namespace dll
	{
		class module_context
		{
		public:
			// Do not call this function from a DLL that is linked to the static C run-time library (CRT).
			// The static CRT requires DLL_THREAD_ATTACH and DLL_THREAD_DETATCH notifications to function properly.
			void disable_thread_notifications(void) const;
			std::wstring get_module_base_name(void) const;
			// FUTURE: KAA: C++11: throw() = noexcept.
			HINSTANCE get_module_handle(void) const throw();
			HINSTANCE m_module; // DEFECT: KAA: broken encapsulation.
		};
	}
}
