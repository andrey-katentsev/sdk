#include "../../include/filesystem/crt_file_system.h"

#include <stdexcept>
#include <vector>

#include <direct.h>
#include <errno.h>
#include <fcntl.h>
#include <io.h>
#include <share.h>
#include <stdio.h>
#include <stdlib.h>

#include <sys\stat.h>

#include "../../include/exception/system_failure.h"
#include "../../include/filesystem/crt_file.h"
#include "../../include/filesystem/path.h"
#include "../../include/RAII/invalid_parameter_handler.h"

namespace
{
 void allow_execution(const wchar_t*, const wchar_t*, const wchar_t*, unsigned int, uintptr_t) { return; }

	/*
	_O_BINARY : Opens a file in binary (untranslated) mode. (See fopen for a description of binary mode.)
	_O_TEXT : Opens a file in text (translated) mode. (For more information, see Text and Binary Mode File I/O and fopen.)

	_O_RANDOM : Specifies primarily random access from disk.
	_O_SEQUENTIAL : Specifies primarily sequential access from disk.

	_O_RDONLY : Opens a file for reading only; cannot be specified with _O_RDWR or _O_WRONLY.
	_O_WRONLY : Opens a file for writing only; cannot be specified with _O_RDONLY or _O_RDWR.
	_O_RDWR : Opens a file for both reading and writing; cannot be specified with _O_RDONLY or _O_WRONLY.

	_O_APPEND : Repositions a file pointer to the end of the file before every write operation.
	_O_TRUNC : Opens a file and truncates it to zero length; the file must have write permission. You cannot specify this flag with _O_RDONLY. _O_TRUNC used with _O_CREAT opens an existing file or creates a new file.
	Note: The _O_TRUNC flag destroys the contents of the specified file.

	_O_NOINHERIT : Prevents creation of a shared file descriptor.

	_O_U16TEXT : Open the file in Unicode UTF-16 mode. This option is available in Visual C++ 2005.
	_O_U8TEXT : Open the file in Unicode UTF-8 mode. This option is available in Visual C++ 2005.
	_O_WTEXT : Open the file in Unicode mode. This option is available in Visual C++ 2005.
	*/
	int get_crt_open_flags(const KAA::filesystem::driver::mode& operations_allowed)
	{
		int flags = _O_NOINHERIT; // FUTURE: KAA: implement all flags support.
		flags |= operations_allowed.m_binary ? _O_BINARY : _O_TEXT;
		flags |= operations_allowed.m_random_access ? _O_RANDOM : _O_SEQUENTIAL;

		{
			if(operations_allowed.m_read && operations_allowed.m_write)
			{
				flags |= _O_RDWR;
			}
			else
			{
				flags |= operations_allowed.m_read ? _O_RDONLY : 0;
				flags |= operations_allowed.m_write ? _O_WRONLY : 0;
			}
		}

		flags |= operations_allowed.m_append ? _O_APPEND : 0;
		flags |= operations_allowed.m_truncate ? _O_TRUNC : 0;

		return flags;
	}

	/*
	_O_CREAT : Creates and opens new file for writing. Has no effect if file specified by filename exists.
	_O_CREAT| _O_SHORT_LIVED : Create a file as temporary and if possible do not flush to disk.
	_O_CREAT| _O_TEMPORARY : Create a file as temporary; the file is deleted when the last file descriptor is closed.
	_O_CREAT| _O_EXCL : Returns an error value if the file specified by filename exists. Applies only when used with _O_CREAT.
	*/
	int get_crt_create_flags(const KAA::filesystem::driver::create_mode lifetime, const KAA::filesystem::driver::mode& operations_allowed)
	{
		int flags = _O_CREAT;
		flags |= get_crt_open_flags(operations_allowed);

		flags |= lifetime.m_not_exist ? _O_EXCL : 0;

		if(lifetime.m_temporary && lifetime.m_in_memory)
		{
			flags |= _O_SHORT_LIVED;
		}
		else
		{
			flags |= lifetime.m_temporary ? _O_TEMPORARY : 0;
			flags |= lifetime.m_in_memory ? _O_SHORT_LIVED : 0;
		}

		return flags;
	}

	/*
	_SH_DENYRW : Denies read and write access to a file.
	_SH_DENYWR : Denies write access to a file.
	_SH_DENYRD : Denies read access to a file.
	_SH_DENYNO : Permits read and write access.
	*/
	int get_crt_share_flags(const KAA::filesystem::driver::share& sharing_allowed)
	{
		if(sharing_allowed.m_read && sharing_allowed.m_write)
			return _SH_DENYNO;

		if(sharing_allowed.m_read)
			return _SH_DENYWR;

		if(sharing_allowed.m_write)
			return _SH_DENYRD;

		return _SH_DENYRW;
	}

	/*
	_S_IWRITE : Writing permitted.
	_S_IREAD : Reading permitted.
	_S_IREAD | _S_IWRITE : Reading and writing permitted.
	*/
	int get_crt_permission_flags(const KAA::filesystem::driver::permission& attributes)
	{
		int flags = 0;
		flags |= attributes.m_read ? _S_IREAD : 0;
		flags |= attributes.m_write ? _S_IWRITE : 0;
		return flags;
	}

	enum crt_access : int
	{
		exist = 0x00,
		write = 0x02,
		read = 0x04
	};
}

namespace KAA
{
	namespace filesystem
	{
		void crt_file_system::icreate_directory(const path::directory& path)
		{
			const int code = _wmkdir(path.to_wstring().c_str());
			if(0 != code)
			{
				const errno_t error = *_errno();
				throw system_failure(__FUNCTIONW__, L"EXCEPTION: unable to create directory, _wmkdir function fails.", error);
			}
		}

		void crt_file_system::iremove_directory(const path::directory& path)
		{
			const int code = _wrmdir(path.to_wstring().c_str());
			if(0 != code)
			{
				const errno_t error = *_errno();
				throw system_failure(__FUNCTIONW__, L"EXCEPTION: unable to remove directory, _wrmdir function fails.", error);
			}
		}

		std::auto_ptr<file> crt_file_system::iopen_file(const std::wstring& path, const mode& operations_allowed, const share& sharing_allowed) const
		{
			RAII::invalid_parameter_handler session(allow_execution);
			const int open = get_crt_open_flags(operations_allowed);
			const int share = get_crt_share_flags(sharing_allowed);
			int handle = 0;
			const errno_t code = _wsopen_s(&handle, path.c_str(), open, share, 0);
			if(0 == code)
				return std::auto_ptr<file>(new crt_file(handle));
			else
				throw system_failure(__FUNCTIONW__, L"EXCEPTION: unable to open file, _wsopen_s function fails.", code);
		}

		std::auto_ptr<file> crt_file_system::icreate_file(const std::wstring& path, const create_mode& lifetime, const mode& operations_allowed, const share& sharing_allowed, const permission& attributes)
		{
			RAII::invalid_parameter_handler session(allow_execution);
			const int create = get_crt_create_flags(lifetime, operations_allowed);
			const int share = get_crt_share_flags(sharing_allowed);
			const int permissions = get_crt_permission_flags(attributes);
			int handle = 0;
			const errno_t code = _wsopen_s(&handle, path.c_str(), create, share, permissions);
			if(0 == code)
				return std::auto_ptr<file>(new crt_file(handle));
			else
				throw system_failure(__FUNCTIONW__, L"EXCEPTION: unable to create file, icreate_file function fails.", code);
		}

		std::wstring crt_file_system::iget_temp_filename(void) const
		{
			RAII::invalid_parameter_handler session(allow_execution);
			{
				const std::wstring filename_format(L"tmpXXXXXX");
				std::vector<wchar_t> buffer(filename_format.begin(), filename_format.end());
				buffer.push_back(L'\0');
				const errno_t code = _wmktemp_s(&buffer[0], buffer.size());
				if(0 != code)
					throw system_failure(__FUNCTIONW__, L"EXCEPTION: unable to create a unique file name, _wmktemp_s function fails.", code);
				return std::wstring(buffer.begin(), buffer.end());
			}
		}

		/*_fsize_t crt_file_system::iget_file_size(const file& handle) const
		{
			RAII::invalid_parameter_handler session(allow_execution);
			try
			{
				const crt_file& crt_handle = dynamic_cast<const crt_file&>(handle);
				const long size = _filelength(crt_handle.descriptor()); // DEFECT: KAA: 32-bit size.
				if(-1L == size)
					throw system_failure(*_errno());
				return size;
			}
			catch(const std::bad_cast&)
			{ throw std::invalid_argument(__FUNCTION__); }
		}*/

		void crt_file_system::irename_file(const std::wstring& present_filename, const std::wstring& new_filename)
		{
			if(0 != _wrename(present_filename.c_str(), new_filename.c_str()))
			{
				const errno_t error = *_errno();
				throw system_failure(__FUNCTIONW__, L"EXCEPTION: unable to rename file, _wrename function fails.", error);
			}
		}

		void crt_file_system::iremove_file(const std::wstring& path)
		{
			if(0 != _wremove(path.c_str()))
			{
				const errno_t error = *_errno();
				throw system_failure(__FUNCTIONW__, L"EXCEPTION: unable to remove file, _wremove function fails.", error);
			}
		}

		// FIX: KAA: check all and provide SESSION!
		// FUTURE: KAA: check for directories and rename.
		void crt_file_system::iset_file_permissions(const std::wstring& file_path, const permission& new_attributes)
		{
			if(0 != _wchmod(file_path.c_str(), get_crt_permission_flags(new_attributes)))
			{
				const errno_t error = *_errno();
				throw system_failure(__FUNCTIONW__, L"EXCEPTION: unable to set file permissions, _wchmod function fails.", error);
			}
		}

		bool is_access_allowed(const std::wstring& path, const crt_access requested_access)
		{
			switch(_waccess_s(path.c_str(), requested_access))
			{
			case 0:
				return true;
			case EACCES:
				return false;
			default:
				{
					const errno_t error = *_errno();
					throw system_failure(__FUNCTIONW__, L"EXCEPTION: unable to determine file permissions, _waccess_s function fails.", error);
				}
			}			
		}

		// FUTURE: KAA: not implemented.
		driver::access crt_file_system::iget_file_permissions(const std::wstring& file_path) const
		{
			RAII::invalid_parameter_handler session(allow_execution);
			{
				const bool is_exists = is_access_allowed(file_path, crt_access::exist);
				const bool is_read_permission = is_access_allowed(file_path, crt_access::read);
				const bool is_write_permission = is_access_allowed(file_path, crt_access::write);
				return access(is_read_permission, is_write_permission, is_exists);
			}
		}
	}
}
