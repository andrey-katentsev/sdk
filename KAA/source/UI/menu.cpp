//
// File: menu.cpp
// Description: user interface helper to operate with menus
// Created: May 24, 2015
// Author: Andrey A. Katentsev
//
// Copyright 2015 Andrey A. Katentsev
//

#include "../../include/UI/cursor.h"

#include "../../include/exception/operation_failure.h"
#include "../../include/exception/windows_api_failure.h"

namespace
{
	// THROWS: operation_failure
	// SAFE GUARANTEE: strong
	// SIDE EFFECTS: none
	void enable_item(const ::HMENU menu, unsigned int item_identifier, const unsigned int mode)
	{
		if(-1 == ::EnableMenuItem(menu, item_identifier, MF_BYCOMMAND | mode))
		{
			constexpr auto reason = KAA::operation_failure::status_code_t::not_found;
			constexpr auto severity = KAA::operation_failure::severity_t::error;
			throw KAA::operation_failure { __FUNCTION__, "the menu item does not exist", reason, severity };
		}
	}
}

namespace KAA
{
	namespace user_interface
	{
		namespace menu
		{
			// Displays a shortcut menu at the specified location and tracks the selection of items on the menu.
			// THROWS: windows_api_failure
			// SAFE GUARANTEE: basic
			// SIDE EFFECTS: changes foreground window, posts WM_NULL message
			void track_popup(const ::HWND owner, const ::HMENU menu, const ::POINT& position)
			{
				// FUTURE: KAA: parameterize flags.
				const auto flags = TPM_LEFTALIGN | TPM_LEFTBUTTON;

				::SetForegroundWindow(owner);
				if(0 == ::TrackPopupMenu(menu, flags, position.x, position.y, 0, owner, nullptr))
				{
					const auto error = ::GetLastError();
					throw KAA::windows_api_failure(__FUNCTIONW__, L"Unable to display a shortcut menu at the specified location.", error);
				}
				::PostMessageW(owner, WM_NULL, 0, 0); // see MSDN TrackPopupMenu function remarks
			}

			// Sets the default menu item for the specified menu.
			// THROWS: windows_api_failure
			// SAFE GUARANTEE: strong
			// SIDE EFFECTS: none
			void set_default_item(const ::HMENU menu, unsigned int item_identifier)
			{
				if(0 == ::SetMenuDefaultItem(menu, item_identifier, FALSE))
				{
					const auto error = ::GetLastError();
					throw KAA::windows_api_failure(__FUNCTIONW__, L"Unable to set the default menu item for the specified menu.", error);
				}
			}

			// Enables the specified menu item.
			// Indicates that the menu item is enabled and restored from a grayed state so that it can be selected.
			// THROWS: operation_failure
			// SAFE GUARANTEE: strong
			// SIDE EFFECTS: none
			void enable_item(const ::HMENU menu, unsigned int item_identifier)
			{
				return ::enable_item(menu, item_identifier, MF_ENABLED);
			}

			// Disables the specified menu item.
			// Indicates that the menu item is disabled, but not grayed, so it cannot be selected.
			// THROWS: operation_failure
			// SAFE GUARANTEE: strong
			// SIDE EFFECTS: none
			void disable_item(const ::HMENU menu, unsigned int item_identifier)
			{
				return ::enable_item(menu, item_identifier, MF_DISABLED);
			}

			// Grays the specified menu item.
			// Indicates that the menu item is disabled and grayed so that it cannot be selected.
			// THROWS: operation_failure
			// SAFE GUARANTEE: strong
			// SIDE EFFECTS: none
			void gray_item(const ::HMENU menu, unsigned int item_identifier)
			{
				return ::enable_item(menu, item_identifier, MF_GRAYED);
			}
		}
	}
}
