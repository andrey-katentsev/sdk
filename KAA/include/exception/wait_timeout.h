#pragma once

#include "failure.h"
#include "windows_api_failure.h"

namespace KAA
{
	class wait_timeout final : public failure
	{
	public:
		wait_timeout(std::wstring source, std::wstring description);

	private:
		windows_api_failure base;

		std::wstring iget_source(void) const override;
		std::wstring iget_description(void) const override;
		std::wstring iget_system_message(void) const override;
	};
}
