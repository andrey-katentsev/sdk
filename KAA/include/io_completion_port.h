#pragma once

#include "../include/RAII/io_completion_port_handle.h"
#include "../include/io_completion_packet.h"

namespace KAA
{
	class io_completion_port
	{
	public:
		enum { number_processors_in_the_system = 0 };

		explicit io_completion_port(unsigned concurrent_threads);

		void associate_device(HANDLE device, DWORD key);

		io_completion_packet wait_for_a_pending_operation_to_complete(DWORD timeout) const;
		void post_packet(const io_completion_packet&);

	private:
		RAII::io_completion_port_handle handle;
	};
}
