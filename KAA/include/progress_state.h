// Feb 16, 2014

#pragma once

namespace KAA
{
	enum class progress_state_t
	{
		proceed, // PROGRESS_CONTINUE : ñontinue the operation
		cancel, // PROGRESS_CANCEL : ñancel the operation and rollback the changes
		stop, // PROGRESS_STOP : stop the operation, it can be restarted at a later time
		quiet, // PROGRESS_QUIET : continue the operation, but stop invoking callback to report progress
	};
}
