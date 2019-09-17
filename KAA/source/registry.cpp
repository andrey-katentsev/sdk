// 01/02/2014

#include "../include/registry.h"
#include "../include/registry_key.h"

namespace KAA
{
	namespace system
	{
		std::unique_ptr<registry_key> registry::open_key(const root_key section, const std::wstring& sub_key, const key_access& desired_access)
		{
			return iopen_key(section, sub_key, desired_access);
		}
		
		std::unique_ptr<registry_key> registry::create_key(const root_key section, const std::wstring& sub_key, const key_options options, const key_access& desired_access, const void* desired_security)
		{
			return icreate_key(section, sub_key, options, desired_access, desired_security);
		}
	}
}
