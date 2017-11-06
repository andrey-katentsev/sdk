/*
#include <fstream>
#include <iosfwd> // pos_type
#include <stdexcept>

namespace
{
	template<class T>
	//_fsize_t GetFileSize(std::basic_istream<T>& file)
	_fsize_t GetStreamSize(std::basic_istream<T>& file)
	{
		const std::wifstream::pos_type current = file.tellg();
		file.seekg(0, std::ios_base::end);
		const std::wifstream::pos_type end = file.tellg();
		file.seekg(current);
		return end;
	}
}

std::wifstream source;
source.exceptions(std::basic_ios::failbit | std::basic_ios::badbit);
source.open(file_path.c_str(), std::ios::binary | std::ios::in);
//const _fsize_t source_file_size = GetFileSize(source);

std::wifstream key;
key.exceptions(std::basic_ios::failbit | std::basic_ios::badbit);
key.open(key_path.c_str(), std::ios::binary | std::ios::in);
//GetFileSize(key);

std::wofstream destination;
destination.exceptions(std::basic_ios::failbit | std::basic_ios::badbit);
destination.open(file_path.c_str(), std::ios::binary | std::ios::in);
*/