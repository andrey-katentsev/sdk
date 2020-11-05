//
// File: com_failure.h
// Description: exception class for component object model
// Created: May 25, 2013
// Author: Andrey A. Katentsev
//
// Copyright © Andrey A. Katentsev, 2013
//

#include <string>
#include "failure.h"
#include <windows.h>

namespace KAA
{
	class com_failure final : public failure
	{
	public:
		com_failure(std::string source, std::string description, HRESULT);
		com_failure(std::string source, std::string description, WORD status_code, WORD facility_code, bool success);

		operator HRESULT (void) const noexcept;

	private:
		std::string source;
		std::string description;
		WORD status_code;
		WORD facility_code;
		bool success;

		HRESULT get_error(void) const noexcept;

		std::string iget_source(void) const override;
		std::string iget_description(void) const override;
		std::string iget_system_message(void) const override;
	};
}
