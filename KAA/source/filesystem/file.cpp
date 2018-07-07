#include "../../include/filesystem/file.h"

namespace KAA
{
	namespace filesystem
	{
		size_t file::read(const size_t bytes_to_read, void* buffer) const
		{
			return iread(bytes_to_read, buffer);
		}

		size_t file::write(const void* buffer, const size_t bytes_to_write)
		{
			return iwrite(buffer, bytes_to_write);
		}

		void file::commit(void)
		{
			return icommit();
		}

		_fsize_t file::get_size(void) const
		{
			return iget_size();
		}

		void file::set_size(const _fsize_t size)
		{
			return iset_size(size);
		}

		_off_t file::tell(void) const
		{
			return itell();
		}

		void file::seek(const _off_t offset, const origin from)
		{
			return iseek(offset, from);
		}
	}
}
