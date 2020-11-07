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
				const errno_t code = _wsplitpath_s(path.c_str(), drive.data(), drive.size(), nullptr, 0, nullptr, 0, nullptr, 0);
				if(0 != code)
				{
					throw KAA::system_failure { __FUNCTION__, "cannot split the drive component from the path", code };
				}
				return drive.data();
			}
		}

		std::wstring split_directory(const std::wstring& path) // DEFECT: KAA: qualified directory.
		{
			KAA::RAII::invalid_parameter_handler session(allow_execution);
			{
				std::vector<wchar_t> drive(3, L'\0');
				std::vector<wchar_t> directory(path.length(), L'\0');
				const errno_t code = _wsplitpath_s(path.c_str(), drive.data(), drive.size(), directory.data(), directory.size(), nullptr, 0, nullptr, 0);
				if(0 != code)
				{
					throw KAA::system_failure { __FUNCTION__, "cannot split the qualified directory path from the path", code };
				}
				return std::wstring { drive.data() } + directory.data();
			}
		}

		std::wstring split_filename(const std::wstring& path) // DEFECT: KAA: qualified filename.
		{
			KAA::RAII::invalid_parameter_handler session(allow_execution);
			{
				std::vector<wchar_t> filename(path.length(), L'\0');
				std::vector<wchar_t> extension(5, L'\0');
				const errno_t code = _wsplitpath_s(path.c_str(), nullptr, 0, nullptr, 0, filename.data(), filename.size(), extension.data(), extension.size());
				if(0 != code)
				{
					throw KAA::system_failure { __FUNCTION__, "cannot split the qualified filename from the path", code };
				}
				return std::wstring { filename.data() } + extension.data();
			}
		}

		std::wstring split_extension(const std::wstring& path)
		{
			KAA::RAII::invalid_parameter_handler session(allow_execution);
			{
				std::vector<wchar_t> extension(5, L'\0');
				const errno_t code = _wsplitpath_s(path.c_str(), nullptr, 0, nullptr, 0, nullptr, 0, extension.data(), extension.size());
				if(0 != code)
				{
					throw KAA::system_failure { __FUNCTION__, "cannot split the extension component from the path", code };
				}
				return extension.data();
			}
		}
	}
}
