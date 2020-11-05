//
// File: notification_area.cpp
// Description: user interface helper to operate with notification area
// Created: May 23, 2015
// Author: Andrey A. Katentsev
//
// Copyright 2015 Andrey A. Katentsev
//

#include "../../include/UI/notification_area.h"

#include <atomic>

#include "../../include/exception/com_failure.h"
#include "../../include/exception/windows_api_failure.h"

#include <strsafe.h>

namespace KAA
{
	namespace user_interface
	{
		namespace notification_area
		{
			// TODO: KAA: replace raw HICON and HWND with class wrappers.
			unsigned int add_icon(const HWND owner, const HICON icon, const std::wstring& tip, const unsigned int window_notification_message_id)
			{
				static std::atomic<unsigned int> id = 0;

				NOTIFYICONDATAW properties = { 0 };
				properties.cbSize = sizeof(NOTIFYICONDATAW);
				properties.hWnd = owner;
				properties.uID = ++id;
				properties.uFlags = NIF_ICON | NIF_TIP | NIF_MESSAGE;
				properties.uCallbackMessage = window_notification_message_id;
				properties.hIcon = icon;
				const auto error = ::StringCchCopyW(properties.szTip, _countof(properties.szTip), tip.c_str());
				if(FAILED(error))
				{
					throw com_failure { __FUNCTION__, "cannot copy tip to the icon properties", error };
				}

				const auto success = ::Shell_NotifyIconW(NIM_ADD, &properties);
				if(TRUE != success)
				{
					const auto code = ::GetLastError();
					throw windows_api_failure(__FUNCTIONW__, L"Unable to add icon to the notification area.", code);
				}
				return id;
			}

			void remove_icon(HWND owner, unsigned int id)
			{
				NOTIFYICONDATAW properties = { 0 };
				properties.cbSize = sizeof(NOTIFYICONDATAW);
				properties.hWnd = owner;
				properties.uID = id;
				const auto success = ::Shell_NotifyIconW(NIM_DELETE, &properties);
				if(TRUE != success)
				{
					const auto code = ::GetLastError();
					throw windows_api_failure(__FUNCTIONW__, L"Unable to remove icon from the notification area.", code);
				}
			}

			void update_icon(HWND owner, unsigned int id, HICON icon)
			{
				NOTIFYICONDATAW properties = { 0 };
				properties.cbSize = sizeof(NOTIFYICONDATAW);
				properties.hWnd = owner;
				properties.uID = id;
				if(icon)
				{
					properties.hIcon = icon;
					properties.uFlags = NIF_ICON;
				}

				const auto success = ::Shell_NotifyIconW(NIM_MODIFY, &properties);
				if(TRUE != success)
				{
					const auto code = ::GetLastError();
					throw windows_api_failure(__FUNCTIONW__, L"Unable to update icon in the notification area.", code);
				}
			}

			void update_icon_tip(HWND owner, unsigned int id, const std::wstring& tip)
			{
				NOTIFYICONDATAW properties = { 0 };
				properties.cbSize = sizeof(NOTIFYICONDATAW);
				properties.hWnd = owner;
				properties.uID = id;
				properties.uFlags = NIF_TIP;
				const auto error = ::StringCchCopyW(properties.szTip, _countof(properties.szTip), tip.c_str());
				if(FAILED(error))
				{
					throw com_failure { __FUNCTION__, "cannot copy tip to the icon properties", error };
				}

				const auto success = ::Shell_NotifyIconW(NIM_MODIFY, &properties);
				if(TRUE != success)
				{
					const auto code = ::GetLastError();
					throw windows_api_failure(__FUNCTIONW__, L"Unable to update icon tip in the notification area.", code);
				}
			}
		}
	}
}
