// 02/02/2014

#pragma once

#include <string>
#include <windows.h>

namespace KAA
{
	class module_context
	{
	public:
		std::wstring get_module_base_name(void) const;
		// FUTURE: KAA: C++11: throw() = noexcept.
		HINSTANCE get_module_handle(void) const throw();
		HINSTANCE m_module; // DEFECT: KAA: broken encapsulation.
	};
}
