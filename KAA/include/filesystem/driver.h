#pragma once

#include <memory>
#include <string>

#include "file.h"

namespace KAA
{
	namespace filesystem
	{
		class driver
		{
		public:
			// FUTURE: KAA: provide more meaningful names for m_ members.
			// FUTURE: KAA: remove default parameters.
			class mode
			{
			public:
				bool m_binary;
				bool m_random_access;
				bool m_read;
				bool m_write;
				bool m_append;
				bool m_truncate;

				mode(bool write = true, bool read = true, bool binary = true, bool random_access = false, bool append = false, bool truncate = false) :
				m_binary(binary),
				m_random_access(random_access),
				m_read(read),
				m_write(write),
				m_append(append),
				m_truncate(truncate)
				{}
			};

			class create_mode
			{
			public:
				bool m_in_memory; // create a file as temporary and if possible do not flush to disk
				bool m_temporary; // create a file as temporary; the file is deleted when the last file descriptor is closed
				bool m_not_exist; // raise an exception if the file specified by filename exists

				// default : new (not exists) persistent file
				create_mode(bool not_exist = true, bool in_memory = false, bool temporary = false) :
				m_in_memory(in_memory),
				m_temporary(temporary),
				m_not_exist(not_exist)
				{}
			};

			class share
			{
			public:
				bool m_read;
				bool m_write;

				share(bool read = true, bool write = true) :
				m_read(read),
				m_write(write)
				{}
			};

			class permission
			{
			public:
				bool m_read; // read permission
				bool m_write; // write permission

				permission(bool write = true, bool read = true) :
				m_read(read),
				m_write(write)
				{}
			};

			class access
			{
			public:
				access(bool read, bool write, bool exist);

				bool m_exist; // existence only
				permission m_permission;
			};

			virtual ~driver();

			void create_directory(const std::wstring&);
			void remove_directory(const std::wstring&);

			std::auto_ptr<file> open_file(const std::wstring&, const mode&, const share&) const;
			std::auto_ptr<file> create_file(const std::wstring&, const create_mode&, const mode&, const share&, const permission&);

			std::wstring get_temp_filename(void) const;

			void rename_file(const std::wstring& present_filename, const std::wstring& new_filename);
			void remove_file(const std::wstring&);

			void delete_file(const std::wstring&);

			void set_file_permissions(const std::wstring&, const permission&);
			access get_file_permissions(const std::wstring&);

			//bool is_path_exists(const std::wstring& path);

		private:
			virtual void icreate_directory(const std::wstring&) = 0;
			virtual void iremove_directory(const std::wstring&) = 0;

			virtual std::auto_ptr<file> iopen_file(const std::wstring&, const mode&, const share&) const = 0;
			virtual std::auto_ptr<file> icreate_file(const std::wstring&, const create_mode&, const mode&, const share&, const permission&) = 0;

			virtual std::wstring iget_temp_filename(void) const = 0;

			virtual void irename_file(const std::wstring&, const std::wstring&) = 0;
			virtual void iremove_file(const std::wstring&) = 0;

			virtual void iset_file_permissions(const std::wstring&, const permission&) = 0;
			virtual access iget_file_permissions(const std::wstring&) = 0;

			//bool iis_path_exists(const std::wstring& path);
		};
	}
}
