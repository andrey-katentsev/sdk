//
// File: controls.h
// Description: user interface helper to operate with controls
// Created: January 22, 2014
// Author: Andrey A. Katentsev
//
// Copyright � Andrey A. Katentsev, 2014
//

#pragma once

#include <string>

#include <windows.h>

namespace KAA
{
	namespace user_interface
	{
		std::wstring get_window_text(HWND);
		std::wstring get_control_text(HWND, int);
		void set_control_text(HWND, int, const std::wstring&);

		// Displays a balloon tip associated with an edit control.
		// To use this function, you must provide a manifest specifying comclt32.dll version 6.0.
		void show_ballon_tip(HWND edit_control, unsigned int title_id, unsigned int text_id, int icon_id);

		// Gets the number of items in the list box of a combo box.
		unsigned int get_items_count(HWND combo_box_control);
		// Retrieves the index of the currently selected item, if any.
		unsigned int get_selected_item(HWND combo_box_control);
		// Selects a string in the list of a combo box. If necessary, the list scrolls the string into view.
		// The text in the edit control of the combo box changes to reflect the new selection, and any previous selection in the list is removed.
		void set_selected_item(HWND combo_box_control, unsigned int item_index);
		// Adds a string to the list box of a combo box.
		// If the combo box does not have the CBS_SORT style, the string is added to the end of the list.
		// Otherwise, the string is inserted into the list, and the list is sorted.
		unsigned int add_string(HWND combo_box_control, const std::wstring& text);
		// Retrieves the application-supplied value associated with the specified item in the combo box.
		LRESULT get_item_data(HWND combo_box_control, unsigned int item_index);
		// Sets the value associated with the specified item in a combo box.
		void set_item_data(HWND combo_box_control, unsigned int item_index, LRESULT data);
	}
}
