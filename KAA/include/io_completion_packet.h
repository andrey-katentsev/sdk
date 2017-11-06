#pragma once

#include <windows.h>

namespace KAA
{
	struct io_completion_packet
	{
		DWORD bytes_transferred;
		DWORD key;
		OVERLAPPED* status;
	};
}
