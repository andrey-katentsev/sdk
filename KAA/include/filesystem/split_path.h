// 5/2/14

#pragma once

#include <string>

namespace KAA
{
	namespace filesystem
	{
		// INPUT:  C:/Temp/file.bin
		// OUTPUT: C:
		std::wstring split_drive(const std::wstring& path);

		// INPUT:  C:/Temp/file.bin
		// OUTPUT: C:/Temp/
		std::wstring split_directory(const std::wstring& path);

		// INPUT:  C:/Temp/file.bin
		// OUTPUT: file.bin
		std::wstring split_filename(const std::wstring& path);

		// INPUT:  C:/Temp/file.bin
		// OUTPUT: .bin
		std::wstring split_extension(const std::wstring& path);
	}
}
