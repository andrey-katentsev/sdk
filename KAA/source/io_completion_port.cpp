#include "../include/io_completion_port.h"
#include "../include/exception/wait_timeout.h"
#include "../include/exception/windows_api_failure.h"

namespace KAA
{
	io_completion_port::io_completion_port(unsigned concurrent_threads) :
	handle(::CreateIoCompletionPort(INVALID_HANDLE_VALUE, nullptr, 0, concurrent_threads))
	{}

	void io_completion_port::associate_device(HANDLE device, DWORD key)
	{
		const HANDLE raw_handle = ::CreateIoCompletionPort(device, handle, key, 0);
		if(raw_handle != handle)
		{
			const DWORD error = ::GetLastError();
			throw windows_api_failure(__FUNCTIONW__, L"Unable to associate an I/O completion port with a specified device.", error);
		}
	}

	io_completion_packet io_completion_port::wait_for_a_pending_operation_to_complete(const DWORD timeout) const
	{
		io_completion_packet packet = { 0 };
		if(0 == ::GetQueuedCompletionStatus(handle, &packet.bytes_transferred, &packet.key, &packet.status, timeout))
		{
			const DWORD error = ::GetLastError();
			if(nullptr != packet.status)
			{
				// I/O request error.
			}
			else
			{
				if(WAIT_TIMEOUT == error)
				{
					throw wait_timeout(__FUNCTIONW__, L"There is no complete I/O operations.");
				}
				else
				{
					// Invalid ::GetQueuedCompletionStatus call.
				}
			}

			throw windows_api_failure(__FUNCTIONW__, L"Unable to dequeue an I/O completion packet from the specified I/O completion port.", error);
		}

		return packet;
	}

	void io_completion_port::post_packet(const io_completion_packet& packet)
	{
		if(0 == ::PostQueuedCompletionStatus(handle, packet.bytes_transferred, packet.key, packet.status))
		{
			const DWORD error = ::GetLastError();
			throw windows_api_failure(__FUNCTIONW__, L"Unable to post an I/O completion packet to an I/O completion port.", error);
		}
	}
}
