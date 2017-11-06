#include "../../include/exception/wait_timeout.h"

namespace KAA
{
	wait_timeout::wait_timeout(const std::wstring& source, const std::wstring& description) :
	base(source, description, WAIT_TIMEOUT)
	{}

	std::wstring wait_timeout::iget_source(void) const
	{
		return base.get_source();
	}

	std::wstring wait_timeout::iget_description(void) const
	{
		return base.get_description();
	}

	std::wstring wait_timeout::iget_system_message(void) const
	{
		return base.get_system_message();
	}
}
