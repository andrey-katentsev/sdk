//
// File: notification_area.h
// Description: user interface helper to operate with notification area
// Created: May 23, 2015
// Author: Andrey A. Katentsev
//
// Copyright 2015 Andrey A. Katentsev
//

#pragma once

#include <string>

#include <windows.h>

namespace KAA
{
	namespace user_interface
	{
		namespace notification_area
		{
			unsigned int add_icon(const HWND owner, const HICON icon, const std::wstring& tip, const unsigned int window_notification_message_id);
			void remove_icon(HWND owner, unsigned int id);
			void update_icon(HWND owner, unsigned int id, HICON icon);
			void update_icon_tip(HWND owner, unsigned int id, const std::wstring& tip);
		}
	}
}
