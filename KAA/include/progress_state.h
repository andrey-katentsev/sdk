// Feb 16, 2014

#pragma once

namespace KAA
{
	enum progress_state
	{
		progress_continue, // PROGRESS_CONTINUE : �ontinue the operation
		progress_cancel, // PROGRESS_CANCEL : �ancel the operation and rollback the changes
		progress_stop, // PROGRESS_STOP : stop the operation, it can be restarted at a later time
		progress_quiet, // PROGRESS_QUIET : continue the operation, but stop invoking callback to report progress
	};
}
