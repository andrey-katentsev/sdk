#include "../../include/filesystem/crt_file.h"

#include <stdexcept>

#include <errno.h>
#include <io.h>
#include <stdio.h>

#include "../../include/exception/system_failure.h"
#include "../../include/RAII/invalid_parameter_handler.h"

namespace
{
	void allow_execution(const wchar_t*, const wchar_t*, const wchar_t*, unsigned int, uintptr_t) { return; }

	/*
	SEEK_SET : Beginning of the file.
	SEEK_CUR : Current position of the file pointer.
	SEEK_END : End of file.
	*/
	int get_crt_origin(const KAA::filesystem::file::origin position)
	{
		switch(position)
		{
		case KAA::filesystem::file::set:
			return SEEK_SET;
		case KAA::filesystem::file::current:
			return SEEK_CUR;
		case KAA::filesystem::file::end:
			return SEEK_END;
		default:
			throw std::invalid_argument(__FUNCTION__);
		}
	}
}

namespace KAA
{
	namespace filesystem
	{
		crt_file::crt_file(const int descriptor) : m_descriptor(descriptor)
		{}

		crt_file::~crt_file()
		{
			const RAII::invalid_parameter_handler session(allow_execution);
			_close(m_descriptor);
		}

		size_t crt_file::iread(const size_t bytes_to_read, void* buffer) const
		{
			const RAII::invalid_parameter_handler session(allow_execution);
			const int bytes_read = _read(m_descriptor, buffer, bytes_to_read); // DEFECT: 32-bit size.
			if(-1 == bytes_read)
			{
				const errno_t error = *_errno();
				throw system_failure { __FUNCTION__, "cannot read data from a file", error };
			}
			return bytes_read;
		}

		size_t crt_file::iwrite(const void* buffer, const size_t bytes_to_write)
		{
			const RAII::invalid_parameter_handler session(allow_execution);
			const int bytes_written = _write(m_descriptor, buffer, bytes_to_write); // DEFECT: 32-bit size.
			if(-1 == bytes_written)
			{
				const errno_t error = *_errno();
				throw system_failure { __FUNCTION__, "cannot write data to a file", error };
			}
			return bytes_written;
		}

		void crt_file::icommit(void)
		{
			const RAII::invalid_parameter_handler session(allow_execution);
			const int code = _commit(m_descriptor);
			if(-1 == code)
			{
				const errno_t error = *_errno();
				throw system_failure { __FUNCTION__, "cannot flush a file directly to disk", error };
			}
		}

		_fsize_t crt_file::iget_size(void) const
		{
			const RAII::invalid_parameter_handler session(allow_execution);
			const long size = _filelength(m_descriptor); // DEFECT: KAA: 32-bit size.
			if(-1L == size)
			{
				const errno_t error = *_errno();
				throw system_failure { __FUNCTION__, "cannot get the length of a file", error };
			}
			return size;
		}

		void crt_file::iset_size(const _fsize_t size)
		{
			const RAII::invalid_parameter_handler session(allow_execution);
			if(0 != _chsize(m_descriptor, size)) // DEFECT: KAA: 32-bit size.
			{
				const errno_t error = *_errno();
				throw system_failure { __FUNCTION__, "cannot change the size of a file", error };
			}
		}

		_off_t crt_file::itell(void) const
		{
			const RAII::invalid_parameter_handler session(allow_execution);
			const long current_position = _tell(m_descriptor); // DEFECT: 32-bit offset.
			if(-1L == current_position)
			{
				const errno_t error = *_errno();
				throw system_failure { __FUNCTION__, "cannot get the position of the file pointer", error };
			}
			return current_position;
		}

		void crt_file::iseek(const _off_t offset, const origin from)
		{
			const RAII::invalid_parameter_handler session(allow_execution);
			const long new_position = _lseek(m_descriptor, offset, get_crt_origin(from)); // DEFECT: 32-bit offset.
			if(-1L == new_position)
			{
				const errno_t error = *_errno();
				throw system_failure { __FUNCTION__, "cannot move a file pointer to the specified location", error };
			}
		}
	}
}
