// Feb 01, 2014

#pragma once

#include "keywords.h"
#include "registry.h"

namespace KAA
{
	namespace system
	{
		class windows_registry : public registry
		{
		private:
			std::auto_ptr<registry_key> iopen_key(root_key section, const std::wstring& sub_key, const key_access& desired_access) override;
			std::auto_ptr<registry_key> icreate_key(root_key section, const std::wstring& sub_key, key_options options, const key_access& desired_access, const void* desired_security) override;
		};
	}
}
