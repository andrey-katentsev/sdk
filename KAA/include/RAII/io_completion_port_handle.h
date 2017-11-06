#pragma once

#include <windows.h>

namespace KAA
{
	namespace RAII
	{
		class io_completion_port_handle
		{
		public:
			explicit io_completion_port_handle(HANDLE);
			~io_completion_port_handle();

			operator HANDLE (void) const;

		private:
			HANDLE raw_handle;

			// FUTURE: C++11: move semantics, = delete.
			io_completion_port_handle(const io_completion_port_handle&);
			io_completion_port_handle(io_completion_port_handle&&);
			io_completion_port_handle& operator = (const io_completion_port_handle&);
			io_completion_port_handle& operator = (io_completion_port_handle&&);
		};
	}
}
