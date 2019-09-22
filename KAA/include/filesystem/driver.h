#pragma once

#include <memory>

#include "file.h"
#include "path.h"

namespace KAA
{
	namespace filesystem
	{
		class driver
		{
		public:
			// FUTURE: KAA: provide more meaningful names for m_ members.
			class mode
			{
			public:
				bool m_binary;
				bool m_random_access;
				bool m_read;
				bool m_write;
				bool m_append;
				bool m_truncate;

				// default: sequential (serial) binary read write
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

				// default: share any access (read / write)
				share(bool write = true, bool read = true) :
				m_read(read),
				m_write(write)
				{}
			};

			class permission
			{
			public:
				bool m_read; // read permission
				bool m_write; // write permission

				// default: full access (allow read / write)
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

			virtual ~driver() = default;

			void create_directory(const path::directory&);
			void remove_directory(const path::directory&);

			std::unique_ptr<file> open_file(const path::file&, const mode&, const share&) const;
			std::unique_ptr<file> create_file(const path::file&, const create_mode&, const mode&, const share&, const permission&);

			path::file get_temp_filename(const path::directory&) const;

			void rename_file(const path::file& from, const path::file& to);
			void remove_file(const path::file&);

			void delete_file(const path::file&);

			bool file_exists(const path::file&) const;

			void set_file_permissions(const path::file&, const permission&);
			access get_file_permissions(const path::file&) const;

		private:
			virtual void icreate_directory(const path::directory&) = 0;
			virtual void iremove_directory(const path::directory&) = 0;

			virtual std::unique_ptr<file> iopen_file(const path::file&, const mode&, const share&) const = 0;
			virtual std::unique_ptr<file> icreate_file(const path::file&, const create_mode&, const mode&, const share&, const permission&) = 0;

			virtual path::file iget_temp_filename(const path::directory&) const = 0;

			virtual void irename_file(const path::file&, const path::file&) = 0;
			virtual void iremove_file(const path::file&) = 0;

			virtual bool ifile_exists(const path::file&) const = 0;

			virtual void iset_file_permissions(const path::file&, const permission&) = 0;
			virtual access iget_file_permissions(const path::file&) const = 0;
		};
	}
}
