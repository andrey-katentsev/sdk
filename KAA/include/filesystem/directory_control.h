#pragma once

#include <string>

namespace KAA
{
	namespace filesystem
	{
		namespace path
		{
			class directory;
		}

		class directory_control
		{
		public:
			virtual ~directory_control();

			path::directory get_current_working_directory(void) const; // gets the current working directory
			void set_current_working_directory(const path::directory&); // changes the current working directory

		private:
			virtual path::directory iget_current_working_directory(void) const = 0;
			virtual void iset_current_working_directory(const path::directory&) = 0;
		};
	}
}
