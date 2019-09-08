//
// File: cursor.cpp
// Description: user interface helper to operate with system cursor
// Created: May 24, 2015
// Author: Andrey A. Katentsev
//
// Copyright 2015 Andrey A. Katentsev
//

#include "../../include/UI/cursor.h"

#include "../../include/exception/windows_api_failure.h"

namespace KAA
{
	namespace user_interface
	{
		namespace cursor
		{
			// Retrieves the position of the mouse cursor, in screen coordinates.
			// THROWS: windows_api_failure
			// SAFE GUARANTEE: strong
			// SIDE EFFECTS: none
			::POINT get_coordinates(void)
			{
				::POINT position = { 0 };
				if(0 == ::GetCursorPos(&position))
				{
					const auto error = ::GetLastError();
					throw KAA::windows_api_failure(__FUNCTIONW__, L"Unable to retrieve the position of the mouse cursor.", error);
				}

				return position;
			}

			// FIX: KAA: unreferenced, incomplete.
			class WaitCursor
			{
			public:
				WaitCursor()
				{
					m_handle = ::LoadCursorW(::GetModuleHandleW(nullptr), IDC_WAIT);
					m_previous = ::SetCursor(m_handle);
				}

				~WaitCursor()
				{
					::SetCursor(m_previous);
				}

			private:
				HCURSOR m_handle;
				HCURSOR m_previous;
			};
		}
	}
}
