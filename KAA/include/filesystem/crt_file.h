#pragma once

#include "file.h"

namespace KAA
{
	namespace filesystem
	{
		class crt_file : public file
		{
		public:
			explicit crt_file(int descriptor);
			~crt_file();

			//int get_descriptor(void) const;

		private:
			int m_descriptor;

			size_t iread(size_t, void*) const override;
			size_t iwrite(const void*, size_t) override;
			
			void icommit(void) override;

			_fsize_t iget_size(void) const override;
			void iset_size(_fsize_t) override;

			_off_t itell(void) const override;
			void iseek(_off_t, origin) override;
		};
	}
}
