//
// File: controls.cpp
// Description: user interface helper to operate with controls
// Created: January 22, 2014
// Author: Andrey A. Katentsev
//
// Copyright © Andrey A. Katentsev, 2014
//

#include "../../include/UI/controls.h"

#include <vector>

#include "../../include/exception/windows_api_failure.h"

#include <windows.h>

namespace
{
	enum
	{
		continue_enumeration = TRUE,
		stop_enumeration = FALSE
	};

	struct find_by_window_id_context
	{
		HWND child_window;
		int child_window_identifier;
	};

	BOOL CALLBACK find_by_window_id(const HWND child_window, LPARAM search_context)
	{
		auto& context = *(reinterpret_cast<find_by_window_id_context*>(search_context));

		const auto child_window_identifier = ::GetWindowLongPtrW(child_window, GWLP_ID);
		if(child_window_identifier == context.child_window_identifier)
		{
			context.child_window = child_window;
			return stop_enumeration;
		}

		return continue_enumeration;
	}

	HWND get_child_window(const HWND parent_window, const int child_window_identifier)
	{
		find_by_window_id_context context = { nullptr, child_window_identifier };

		::EnumChildWindows(parent_window, find_by_window_id, reinterpret_cast<LPARAM>(&context));
		if(nullptr == context.child_window)
		{
			// FUTURE: this is not a win32 failure.
			throw KAA::windows_api_failure(__FUNCTIONW__, L"Unable to find control within a window.", ERROR_CONTROL_ID_NOT_FOUND, FACILITY_NULL, KAA::windows_api_failure::S_WARNING, true);
		}

		return context.child_window;
	}
}

namespace KAA
{
	namespace user_interface
	{
		std::wstring get_window_text(const HWND window)
		{
			std::vector<wchar_t> buffer(::GetWindowTextLengthW(window) + 1, L'\0');

			if(0 == ::GetWindowTextW(window, &buffer[0], buffer.size()))
			{
				const auto error = ::GetLastError();
				if(ERROR_SUCCESS != error) // the window has no title bar or text, or the title bar is empty
				{
					throw windows_api_failure(__FUNCTIONW__, L"Unable to retrieve the window's text.", error);
				}
			}

			return std::wstring(&buffer[0]);
		}

		std::wstring get_control_text(const HWND window, const int control_identifier)
		{
			const auto control = get_child_window(window, control_identifier);
			return get_window_text(control);
		}

		void set_control_text(const HWND window, const int control_identifier, const std::wstring& text)
		{
			const auto control = get_child_window(window, control_identifier);

			if(0 == ::SetWindowTextW(control, text.c_str()))
			{
				const auto error = ::GetLastError();
				throw windows_api_failure(__FUNCTIONW__, L"Unable to set the window's text.", error);
			}
		}
	}
}
