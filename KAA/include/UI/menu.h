//
// File: menu.h
// Description: user interface helper to operate with menus
// Created: May 24, 2015
// Author: Andrey A. Katentsev
//
// Copyright 2015 Andrey A. Katentsev
//

#pragma once

#include <windows.h>

namespace KAA
{
	namespace user_interface
	{
		namespace menu
		{
			void track_popup(const ::HWND owner, const ::HMENU menu, const ::POINT& position);
			void set_default_item(const ::HMENU menu, unsigned int item_identifier);
			void enable_item(const ::HMENU menu, unsigned int item_identifier);
			void disable_item(const ::HMENU menu, unsigned int item_identifier);
			void gray_item(const ::HMENU menu, unsigned int item_identifier);
		}
	}
}
