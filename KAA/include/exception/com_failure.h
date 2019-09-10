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
		com_failure(std::wstring source, std::wstring description, HRESULT);
		com_failure(std::wstring source, std::wstring description, WORD status_code, WORD facility_code, bool is_success);

		operator HRESULT (void) const throw();

	private:
		std::wstring source;
		std::wstring description;
		WORD status_code;
		WORD facility_code;
		bool is_success;

		HRESULT get_error(void) const throw();

		std::wstring iget_source(void) const override;
		std::wstring iget_description(void) const override;
		std::wstring iget_system_message(void) const override;
	};
}
