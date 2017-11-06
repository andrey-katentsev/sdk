#include "../../include/RAII/io_completion_port_handle.h"
#include "../../include/exception/windows_api_failure.h"

namespace KAA
{
	namespace RAII
	{
		io_completion_port_handle::io_completion_port_handle(HANDLE raw_handle) :
		raw_handle(raw_handle)
		{
			if(nullptr == raw_handle)
			{
				const DWORD error = ::GetLastError();
				throw KAA::windows_api_failure(__FUNCTIONW__, L"Unable to create an I/O completion port.", error);
			}
		}

		io_completion_port_handle::~io_completion_port_handle()
		{
			::CloseHandle(raw_handle);
		}

		io_completion_port_handle::operator HANDLE (void) const
		{
			return raw_handle;
		}
	}
}
