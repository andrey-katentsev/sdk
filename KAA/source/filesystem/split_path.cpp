#include "../../include/filesystem/split_path.h"

#include <vector>
#include <cstdlib>

#include "../../include/exception/system_failure.h"
#include "../../include/RAII/invalid_parameter_handler.h"

namespace
{
	void allow_execution(const wchar_t*, const wchar_t*, const wchar_t*, unsigned int, uintptr_t) { return; }
}

namespace KAA
{
	namespace filesystem
	{
		std::wstring split_drive(const std::wstring& path)
		{
			KAA::RAII::invalid_parameter_handler session(allow_execution);
			{
				std::vector<wchar_t> drive(3, L'\0');
				const errno_t code = _wsplitpath_s(path.c_str(), &drive[0], drive.size(), nullptr, 0, nullptr, 0, nullptr, 0);
				if(0 != code)
				{
					throw KAA::system_failure(__FUNCTIONW__, L"EXCEPTION: unable to split the drive component from the path, _wsplitpath_s function fails.", code);
				}
				return std::wstring(&drive[0]);
			}
		}

		std::wstring split_directory(const std::wstring& path) // DEFECT: KAA: qualified directory.
		{
			KAA::RAII::invalid_parameter_handler session(allow_execution);
			{
				std::vector<wchar_t> drive(3, L'\0');
				std::vector<wchar_t> directory(path.length(), L'\0');
				const errno_t code = _wsplitpath_s(path.c_str(), &drive[0], drive.size(), &directory[0], directory.size(), nullptr, 0, nullptr, 0);
				if(0 != code)
				{
					throw KAA::system_failure(__FUNCTIONW__, L"EXCEPTION: unable to split the qualified directory path from the path, _wsplitpath_s function fails.", code);
				}
				return std::wstring(&drive[0]) + std::wstring(&directory[0]);
			}
		}

		std::wstring split_filename(const std::wstring& path) // DEFECT: KAA: qualified filename.
		{
			KAA::RAII::invalid_parameter_handler session(allow_execution);
			{
				std::vector<wchar_t> filename(path.length(), L'\0');
				std::vector<wchar_t> extension(5, L'\0');
				const errno_t code = _wsplitpath_s(path.c_str(), nullptr, 0, nullptr, 0, &filename[0], filename.size(), &extension[0], extension.size());
				if(0 != code)
				{
					throw KAA::system_failure(__FUNCTIONW__, L"EXCEPTION: unable to split the qualified filename from the path, _wsplitpath_s function fails.", code);
				}
				return std::wstring(&filename[0]) + std::wstring(&extension[0]);
			}
		}

		std::wstring split_extension(const std::wstring& path)
		{
			KAA::RAII::invalid_parameter_handler session(allow_execution);
			{
				std::vector<wchar_t> extension(5, L'\0');
				const errno_t code = _wsplitpath_s(path.c_str(), nullptr, 0, nullptr, 0, nullptr, 0, &extension[0], extension.size());
				if(0 != code)
				{
					throw KAA::system_failure(__FUNCTIONW__, L"EXCEPTION: unable to split the extension component from the path, _wsplitpath_s function fails.", code);
				}
				return std::wstring(&extension[0]);
			}
		}
	}
}
