#pragma once

#include <windows.h>

namespace KAA
{
	struct io_completion_packet
	{
		DWORD bytes_transferred;
		ULONG_PTR key;
		OVERLAPPED* status;
	};
}
