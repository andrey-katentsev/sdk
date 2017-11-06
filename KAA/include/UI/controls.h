//
// File: controls.h
// Description: user interface helper to operate with controls
// Created: January 22, 2014
// Author: Andrey A. Katentsev
//
// Copyright © Andrey A. Katentsev, 2014
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
	}
}
