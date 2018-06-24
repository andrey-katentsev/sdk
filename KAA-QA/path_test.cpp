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

TEST(extension, to_wstring)
{
	// ARRANGE
	const auto testee = KAA::filesystem::path::extension(extension);
	// ACT
	const auto actual = testee.to_wstring();
	// ASSERT
	ASSERT_EQ(extension, actual);
}

namespace
{
	const auto unc_path = std::wstring { LR"(\\HYPERLINK\eBooks\windows.txt)" };
	const auto unc_drive = std::wstring { };
	const auto unc_directory = std::wstring { LR"(\\HYPERLINK\eBooks\)" };
}

/*TEST(unc_drive_path, from_string)
{
	ASSERT_NO_THROW(const auto root = drive(unc_path));
}*/

TEST(unc_directory_path, from_string)
{
	ASSERT_NO_THROW(const auto path = directory(unc_directory));
}

TEST(unc_file_path, from_string)
{
	ASSERT_NO_THROW(const auto path = file(unc_path));
}

namespace
{
	const auto long_unc_path = std::wstring { LR"(\\?\D:\User\Hyperlink\eBooks\windows.txt)" };
	const auto long_unc_drive = std::wstring { };
	const auto long_unc_directory = std::wstring { LR"(\\?\D:\User\Hyperlink\eBooks\)" };
}

/*TEST(long_unc_drive_path, from_string)
{
	ASSERT_NO_THROW(const auto root = drive(long_unc_drive));
}*/

TEST(long_unc_directory_path, from_string)
{
	ASSERT_NO_THROW(const auto path = directory(long_unc_directory));
}

TEST(long_unc_file_path, from_string)
{
	ASSERT_NO_THROW(const auto path = file(long_unc_path));
}

namespace
{
	const auto uncw_path = std::wstring { LR"(\\?\UNC\HYPERLINK\eBooks\windows.txt)" };
	const auto uncw_drive = std::wstring { };
	const auto uncw_directory = std::wstring { LR"(\\?\UNC\HYPERLINK\eBooks\)" };
}

/*TEST(uncw_drive_path, from_string)
{
	ASSERT_NO_THROW(const auto root = drive(uncw_drive));
}*/

TEST(uncw_directory_path, from_string)
{
	ASSERT_NO_THROW(const auto path = directory(uncw_directory));
}

TEST(uncw_file_path, from_string)
{
	ASSERT_NO_THROW(const auto path = file(uncw_path));
}
