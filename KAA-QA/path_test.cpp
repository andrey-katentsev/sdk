#include "gtest/gtest.h"

#include "../KAA/include/filesystem/path.h"

using KAA::filesystem::path::drive;
using KAA::filesystem::path::directory;
using KAA::filesystem::path::file;

namespace
{
	const auto lfs_path = std::wstring { LR"(D:\User\Hyperlink\eBooks\windows.txt)" };
	const auto lfs_drive = std::wstring { L"D:" };
	const auto lfs_directory = std::wstring { LR"(D:\User\Hyperlink\eBooks\)" };

	const auto filename = std::wstring { L"windows.txt" };
	const auto extension = std::wstring { L".txt" };
}

TEST(lfs_drive_path, from_string)
{
	ASSERT_NO_THROW(const auto root = drive(lfs_drive));
}

TEST(lfs_directory_path, from_string)
{
	ASSERT_NO_THROW(const auto path = directory(lfs_directory));
}

TEST(lfs_file_path, from_string)
{
	ASSERT_NO_THROW(const auto path = file(lfs_path));
}

TEST(extension, from_string)
{
	ASSERT_NO_THROW(const auto e = KAA::filesystem::path::extension(extension));
}
