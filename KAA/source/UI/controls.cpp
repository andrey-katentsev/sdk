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

#include "../../include/load_string.h"
#include "../../include/exception/windows_api_failure.h"

#include <commctrl.h>
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

	void show_ballon_tip(HWND edit_control, const EDITBALLOONTIP& information) noexcept
	{
		::SendMessageW(edit_control, EM_SHOWBALLOONTIP, 0, reinterpret_cast<LPARAM>(&information));
	}

	void show_ballon_tip(HWND edit_control, const std::wstring& title, const std::wstring& text, const INT icon_id) noexcept
	{
		::EDITBALLOONTIP information = { 0 };
		information.cbStruct = sizeof(information);
		information.pszTitle = title.c_str();
		information.pszText = text.c_str();
		information.ttiIcon = icon_id;
		show_ballon_tip(edit_control, information);
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

		void show_ballon_tip(HWND edit_control, const unsigned int title_id, const unsigned int text_id, const int icon_id)
		{
			const auto title = resources::load_string(title_id);
			const auto text = resources::load_string(text_id);
			::show_ballon_tip(edit_control, title, text, icon_id);
		}

		unsigned int get_items_count(HWND combo_box_control)
		{
			const auto number_of_items = ::SendMessageW(combo_box_control, CB_GETCOUNT, 0, 0);
			if (CB_ERR == number_of_items)
			{
				const auto code = ::GetLastError();
				throw KAA::windows_api_failure(__FUNCTIONW__, L"failed to get the number of items in the list box of a combo box", code);
			}
			return number_of_items;
		}

		unsigned int get_selected_item(HWND combo_box_control)
		{
			const auto item_index = ::SendMessageW(combo_box_control, CB_GETCURSEL, 0, 0);
			if (CB_ERR == item_index) // if no item is selected, it is CB_ERR
			{
				const auto code = ::GetLastError();
				throw KAA::windows_api_failure(__FUNCTIONW__, L"failed to retrieve the index of the currently selected item: no item is selected", code);
			}
			return item_index;
		}

		// THROWS: windows_api_failure
		// SAFE GUARANTEE: basic
		// SIDE EFFECTS: if 'item_index' is greater than the number of items in the list or if 'item_index' is –1, the return value is CB_ERR and the selection is cleared
		void set_selected_item(HWND combo_box_control, const unsigned int item_index)
		{
			if (CB_ERR == ::SendMessageW(combo_box_control, CB_SETCURSEL, item_index, 0))
			{
				const auto code = ::GetLastError();
				throw KAA::windows_api_failure(__FUNCTIONW__, L"failed to select a string in the list of a combo box", code);
			}
		}

		unsigned int add_string(HWND combo_box_control, const std::wstring& text)
		{
			const auto index = ::SendMessageW(combo_box_control, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(text.c_str()));
			if (CB_ERR == index)
			{
				const auto code = ::GetLastError();
				throw KAA::windows_api_failure(__FUNCTIONW__, L"failed to add a string to the list box of a combo box", code);
			}

			if (CB_ERRSPACE == index)
			{
				const auto code = ::GetLastError();
				throw KAA::windows_api_failure(__FUNCTIONW__, L"failed to add a string to the list box of a combo box: insufficient space is available to store the new string", code);
			}
			return index;
		}

		LRESULT get_item_data(HWND combo_box_control, const unsigned int item_index)
		{
			const auto assotiated_value = ::SendMessageW(combo_box_control, CB_GETITEMDATA, item_index, 0);
			if (CB_ERR == assotiated_value)
			{
				const auto code = ::GetLastError();
				throw KAA::windows_api_failure(__FUNCTIONW__, L"failed to retrieve the value associated with the item in a combo box", code);
			}
			return assotiated_value;
		}

		void set_item_data(HWND combo_box_control, const unsigned int item_index, const LRESULT data)
		{
			if (CB_ERR == ::SendMessageW(combo_box_control, CB_SETITEMDATA, item_index, data))
			{
				const auto code = ::GetLastError();
				throw KAA::windows_api_failure(__FUNCTIONW__, L"failed to set the value associated with the item in a combo box", code);
			}
		}
	}
}
