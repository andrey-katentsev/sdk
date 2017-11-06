#pragma once

#include <io.h>
#include <sys\types.h>

namespace KAA
{
	namespace filesystem
	{
		class file
		{
		public:
			enum origin
			{
				set, // beginning of the file
				current, // current position of the file pointer
				end // end of file
			};

			virtual ~file();

			size_t read(size_t, void*) const; // reads data from a file
			size_t write(const void*, size_t); // writes data to a file

			void commit(void); // flushes a file directly to disk

			_fsize_t get_size(void) const; // gets the length of a file in bytes
			void set_size(_fsize_t); // changes the size of a file

			_off_t tell(void) const; // get the position of the file pointer
			void seek(_off_t, origin); // moves a file pointer to the specified location

		private:
			virtual size_t iread(size_t, void*) const = 0;
			virtual size_t iwrite(const void*, size_t) = 0;

			virtual void icommit(void) = 0;

			virtual _fsize_t iget_size(void) const = 0;
			virtual void iset_size(_fsize_t) = 0;

			virtual _off_t itell(void) const = 0;
			virtual void iseek(_off_t, origin) = 0;
		};
	}
}
