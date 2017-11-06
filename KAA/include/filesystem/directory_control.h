#pragma once

#include <string>

namespace KAA
{
	namespace filesystem
	{
		class directory_control
		{
		public:
			virtual ~directory_control();

			std::wstring get_current_working_directory(void) const; // gets the current working directory
			void set_current_working_directory(const std::wstring&); // changes the current working directory

		private:
			virtual std::wstring iget_current_working_directory(void) const = 0;
			virtual void iset_current_working_directory(const std::wstring&) = 0;
		};
	}
}
