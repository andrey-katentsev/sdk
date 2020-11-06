#include "../../include/exception/wait_timeout.h"

namespace KAA
{
	wait_timeout::wait_timeout(std::string source, std::string description) :
	base(std::move(source), std::move(description), WAIT_TIMEOUT)
	{}

	std::string wait_timeout::iget_source(void) const
	{
		return base.get_source();
	}

	std::string wait_timeout::iget_description(void) const
	{
		return base.get_description();
	}

	std::string wait_timeout::iget_system_message(void) const
	{
		return base.get_system_message();
	}
}
