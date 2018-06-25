#pragma once

#include "directory_control.h"

namespace KAA
{
	namespace filesystem
	{
		// This API cannot be used in applications that execute in the Windows Runtime. For more information, see CRT functions not supported with /ZW.
		class crt_directory_control : public directory_control
		{
		private:
			path::directory iget_current_working_directory(void) const override;
			void iset_current_working_directory(const path::directory&) override;
		};
	}
}
