// 01/02/2014

#include "../include/windows_registry.h"

#include <stdexcept>

#include "../include/windows_registry_key.h"
#include "../include/exception/windows_api_failure.h"

#include <windows.h>

namespace
{
	HKEY get_windows_registry_root_key(const KAA::system::registry::root_key section)
	{
		switch(section)
		{
		case KAA::system::registry::classes_root:
			return HKEY_CLASSES_ROOT;
		case KAA::system::registry::current_configuration:
			return HKEY_CURRENT_CONFIG;
		case KAA::system::registry::current_user:
			return HKEY_CURRENT_USER;
		case KAA::system::registry::local_machine:
			return HKEY_LOCAL_MACHINE;
		case KAA::system::registry::users:
			return HKEY_USERS;
		default:
			throw std::invalid_argument(__FUNCTION__);
		}
	}

	REGSAM get_windows_registry_key_security_access_mask(const KAA::system::registry::key_access& desired_access)
	{
		REGSAM sam = 0;
		sam |= desired_access.create_link ? KEY_CREATE_LINK : 0;
		sam |= desired_access.create_sub_key ? KEY_CREATE_SUB_KEY : 0;
		sam |= desired_access.enumerate_sub_keys ? KEY_ENUMERATE_SUB_KEYS : 0;
		sam |= desired_access.notify ? KEY_NOTIFY : 0;
		sam |= desired_access.query_value ? KEY_QUERY_VALUE : 0;
		sam |= desired_access.set_value ? KEY_SET_VALUE : 0;
		// FUTURE: KAA: support WOW64 flags.
		//KEY_WOW64_32KEY : Indicates that an application on 64-bit Windows should operate on the 32-bit registry view.
		//KEY_WOW64_64KEY : Indicates that an application on 64-bit Windows should operate on the 64-bit registry view.
		return sam;
	}

	DWORD get_windows_registry_key_options(const KAA::system::registry::key_options options)
	{
		switch(options)
		{
		case KAA::system::registry::restore:
			return REG_OPTION_BACKUP_RESTORE;
		case KAA::system::registry::persistent:
			return REG_OPTION_NON_VOLATILE;
		case KAA::system::registry::in_memory:
			return REG_OPTION_VOLATILE;
		default:
			throw std::invalid_argument(__FUNCTION__);
		}
	}

	// THROWS: windows_api_failure
	// SAFE GUARANTEE: strong
	// SIDE EFFECTS: -
	HKEY open_key(const HKEY key, const std::wstring& sub_key, const REGSAM desired_access)
	{
		HKEY requested_key = nullptr;
		const LSTATUS code = ::RegOpenKeyExW(key, sub_key.c_str(), 0, desired_access, &requested_key);
		if(ERROR_SUCCESS != code)
		{
			throw KAA::windows_api_failure(__FUNCTIONW__, L"Unable to open system registry key.", code);
		}
		return requested_key;
	}

	// FUTURE: KAA: generalize query / set.

	// THROWS: windows_api_failure
	// SAFE GUARANTEE: strong
	// SIDE EFFECTS: -
	// RETURNS: <handle to the opened or created key, disposition> (see MSDN for RegCreateKeyEx for details)
	std::pair<HKEY, DWORD> create_key(const HKEY key, const std::wstring& sub_key, const DWORD options, const REGSAM desired_access, const SECURITY_ATTRIBUTES* desired_security)
	{
		HKEY requested_key = nullptr;
		DWORD disposition = 0;
		const LSTATUS code = ::RegCreateKeyExW(key, sub_key.c_str(), 0, nullptr, options, desired_access, const_cast<LPSECURITY_ATTRIBUTES>(desired_security), &requested_key, &disposition);
		if(ERROR_SUCCESS != code)
		{
			throw KAA::windows_api_failure(__FUNCTIONW__, L"Unable to create system registry key.", code);
		}
		return std::make_pair(requested_key, disposition);
	}
}

namespace KAA
{
	namespace system
	{
		std::auto_ptr<registry_key> windows_registry::iopen_key(const root_key section, const std::wstring& sub_key, const key_access& desired_access)
		{
			const HKEY windows_section = get_windows_registry_root_key(section);
			const REGSAM windows_desired_access = get_windows_registry_key_security_access_mask(desired_access);
			return std::auto_ptr<registry_key>(new windows_registry_key(::open_key(windows_section, sub_key, windows_desired_access)));
		}

		std::auto_ptr<registry_key> windows_registry::icreate_key(const root_key section, const std::wstring& sub_key, const key_options options, const key_access& desired_access, const void* const desired_security)
		{
			const HKEY windows_section = get_windows_registry_root_key(section);
			const DWORD windows_options = get_windows_registry_key_options(options);
			const REGSAM windows_desired_access = get_windows_registry_key_security_access_mask(desired_access);
			const SECURITY_ATTRIBUTES* windows_desired_security = reinterpret_cast<const SECURITY_ATTRIBUTES*>(desired_security);
			return std::auto_ptr<registry_key>(new windows_registry_key(::create_key(windows_section, sub_key, windows_options, windows_desired_access, windows_desired_security).first));
		}
	}
}
