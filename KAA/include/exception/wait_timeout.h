#pragma once

#include "failure.h"
#include "windows_api_failure.h"

namespace KAA
{
	class wait_timeout final : public failure
	{
	public:
		wait_timeout(std::string source, std::string description);

	private:
		windows_api_failure base;

		std::string iget_source(void) const override;
		std::string iget_description(void) const override;
		std::string iget_system_message(void) const override;
	};
}
