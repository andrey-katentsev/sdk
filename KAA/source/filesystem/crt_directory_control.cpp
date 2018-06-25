#include "../../include/filesystem/crt_directory_control.h"

#include <stdexcept>

#include <direct.h>
#include <errno.h>

#include "../../include/exception/system_failure.h"
#include "../../include/filesystem/path.h"
#include "../../include/RAII/crt_heap_memory.h"
#include "../../include/RAII/invalid_parameter_handler.h"

namespace
{
	void allow_execution(const wchar_t*, const wchar_t*, const wchar_t*, unsigned int, uintptr_t) { return; }
}

namespace KAA
{
	namespace filesystem
	{
		path::directory crt_directory_control::iget_current_working_directory(void) const
		{
			const RAII::invalid_parameter_handler session(allow_execution);
			try
			{
				// MSDN: passing NULL as the buffer forces getcwd to allocate memory for the path, which allows the code to support file paths longer than _MAX_PATH, which are supported by NTFS.
				const KAA::RAII::crt_heap_memory path { _wgetcwd(nullptr, 0) };
				return path::directory { static_cast<const wchar_t*>(static_cast<const void*>(path)) };
			}
			catch (const std::invalid_argument&)
			{
				const errno_t error = *_errno();
				throw system_failure(__FUNCTIONW__, L"EXCEPTION: unable to get the current working directory, _wgetcwd function fails.", error);
			}
		}

		void crt_directory_control::iset_current_working_directory(const path::directory& path)
		{
			const RAII::invalid_parameter_handler session(allow_execution);
			if (0 != _wchdir(path.to_wstring().c_str()))
			{
				const errno_t error = *_errno();
				throw system_failure(__FUNCTIONW__, L"EXCEPTION: unable to change the current working directory, _wchdir function fails.", error);
			}
		}
	}
}
