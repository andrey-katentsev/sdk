//
// File: registry.h
// Description: the registry is a system-defined database in which applications and system components store and retrieve configuration data
// Created: February 1, 2014
// Author: Andrey A. Katentsev
//
// Copyright © Andrey A. Katentsev, 2014
//

#pragma once

#include <memory>
#include <string>

namespace KAA
{
	namespace system
	{
		class registry_key;
		class registry
		{
		public:
			// FIX: KAA: provide with description.
			enum root_key
			{
				classes_root,
				current_configuration,
				current_user,
				local_machine,
				users
			};

			struct key_access
			{
				//all_access, // KEY_ALL_ACCESS : Combination of KEY_QUERY_VALUE, KEY_ENUMERATE_SUB_KEYS, KEY_NOTIFY, KEY_CREATE_SUB_KEY, KEY_CREATE_LINK, and KEY_SET_VALUE access.
				bool create_link; // KEY_CREATE_LINK : Permission to create a symbolic link.
				bool create_sub_key; // KEY_CREATE_SUB_KEY : Permission to create subkeys.
				bool enumerate_sub_keys; // KEY_ENUMERATE_SUB_KEYS : Permission to enumerate subkeys.
				//bool execute; // KEY_EXECUTE : Permission for read access.
				bool notify; // KEY_NOTIFY : Permission for change notification.
				bool query_value; // KEY_QUERY_VALUE : Permission to query subkey data.
				//read, // KEY_READ : Combination of KEY_QUERY_VALUE, KEY_ENUMERATE_SUB_KEYS, and KEY_NOTIFY access.
				bool set_value; // KEY_SET_VALUE : Permission to set subkey data.
				//write, // KEY_WRITE : Combination of KEY_SET_VALUE and KEY_CREATE_SUB_KEY access.
			};

			enum key_options
			{
				restore, // REG_OPTION_BACKUP_RESTORE : If this flag is set, the function ignores the samDesired parameter and attempts to open the key with the access required to backup or restore the key. If the calling thread has the SE_BACKUP_NAME privilege enabled, the key is opened with the ACCESS_SYSTEM_SECURITY and KEY_READ access rights. If the calling thread has the SE_RESTORE_NAME privilege enabled, the key is opened with the ACCESS_SYSTEM_SECURITY and KEY_WRITE access rights. If both privileges are enabled, the key has the combined access rights for both privileges. For more information, see Running with Special Privileges.
				persistent, // REG_OPTION_NON_VOLATILE : This key is not volatile; this is the default. The information is stored in a file and is preserved when the system is restarted. The RegSaveKey function saves keys that are not volatile.
				in_memory // REG_OPTION_VOLATILE : All keys created by the function are volatile. The information is stored in memory and is not preserved when the corresponding registry hive is unloaded. For HKEY_LOCAL_MACHINE, this occurs when the system is shut down. For registry keys loaded by the RegLoadKey function, this occurs when the corresponding RegUnLoadKey is performed. The RegSaveKey function does not save volatile keys. This flag is ignored for keys that already exist.
			};

			std::unique_ptr<registry_key> open_key(root_key section, const std::wstring& subkey, const key_access& desired_access);
			std::unique_ptr<registry_key> create_key(root_key section, const std::wstring& subkey, key_options options, const key_access& desired_access, const void* desired_security = nullptr);

			virtual ~registry() = default;

		private:
			virtual std::unique_ptr<registry_key> iopen_key(root_key section, const std::wstring& subkey, const key_access& desired_access) = 0;
			virtual std::unique_ptr<registry_key> icreate_key(root_key section, const std::wstring& subkey, key_options options, const key_access& desired_access, const void* desired_security) = 0;
		};
	}
}
