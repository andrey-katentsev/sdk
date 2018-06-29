#include "gtest/gtest.h"

#include "../KAA/include/filesystem/path.h"

using KAA::filesystem::path::drive;
using KAA::filesystem::path::directory;
using KAA::filesystem::path::file;

namespace
{
	const auto lfs_path = std::wstring { LR"(D:\User\Hyperlink\eBooks\windows.txt)" };
	const auto lfs_drive = std::wstring { L"D:" };
	const auto lfs_directory = std::wstring { LR"(D:\User\Hyperlink\)" };
	const auto lfs_subdirectory = std::wstring { LR"(D:\User\Hyperlink\eBooks\)" };

	const auto lfs_inconsistent_path = std::wstring { LR"(D:\User/Hyperlink\eBooks/windows.txt)" };
	const auto lfs_inconsistent_subdirectory = std::wstring { LR"(D:/User\Hyperlink/eBooks\)" };

	const auto filename = std::wstring { L"windows.txt" };
	const auto extension = std::wstring { L".txt" };
}

TEST(lfs_drive_path, from_string)
{
	ASSERT_NO_THROW(const auto root = drive(lfs_drive));
}

TEST(lfs_drive_path, to_wstring)
{
	// ARRANGE
	const auto testee = drive(lfs_drive);
	// ACT
	const auto actual = testee.to_wstring();
	// ASSERT
	ASSERT_EQ(lfs_drive, actual);
}

TEST(lfs_directory_path, from_string)
{
	ASSERT_NO_THROW(const auto path = directory(lfs_directory));
}

TEST(lfs_directory_path, always_consistent)
{
	const auto path = directory(lfs_inconsistent_subdirectory);
	ASSERT_EQ(lfs_subdirectory, path.to_wstring());
}

TEST(lfs_directory_path, to_wstring)
{
	// ARRANGE
	const auto testee = directory(lfs_directory);
	// ACT
	const auto actual = testee.to_wstring();
	// ASSERT
	ASSERT_EQ(lfs_directory, actual);
}

TEST(lfs_directory_path, case_sensitive_comparison)
{
	{
		const auto A = directory(lfs_directory);
		const auto B = directory(lfs_directory);
		EXPECT_TRUE(A == B);
		EXPECT_FALSE(A != B);
	}
	{
		const auto A = directory(lfs_directory);
		const auto B = directory(lfs_subdirectory);
		EXPECT_TRUE(A != B);
		EXPECT_FALSE(A == B);
	}
}

TEST(lfs_directory_path, CRT_path)
{
	const auto CRT_directory = lfs_directory;
	const auto WinAPI_directory = std::wstring { lfs_directory.c_str(), lfs_directory.length() - 1 };
	EXPECT_EQ(CRT_directory, KAA::filesystem::path::make_CRT_directory_path(CRT_directory));
	EXPECT_EQ(CRT_directory, KAA::filesystem::path::make_CRT_directory_path(WinAPI_directory));
}

TEST(lfs_directory_path, WinAPI_path)
{
	const auto CRT_directory = lfs_directory;
	const auto WinAPI_directory = std::wstring { lfs_directory.c_str(), lfs_directory.length() - 1 };
	EXPECT_EQ(WinAPI_directory, KAA::filesystem::path::make_WinAPI_directory_path(CRT_directory));
	EXPECT_EQ(WinAPI_directory, KAA::filesystem::path::make_WinAPI_directory_path(WinAPI_directory));
}

TEST(lfs_directory_path, make_file_path)
{
	{
		const auto directory = KAA::filesystem::path::directory { KAA::filesystem::path::append_trailing_backslash(lfs_subdirectory) };
		const auto path = directory + filename;
		EXPECT_EQ(lfs_path, path.to_wstring());
	}
	{
		const auto directory = KAA::filesystem::path::directory { KAA::filesystem::path::remove_trailing_backslash(lfs_subdirectory) };
		const auto path = directory + filename;
		EXPECT_EQ(lfs_path, path.to_wstring());
	}
}

TEST(lfs_file_path, from_string)
{
	ASSERT_NO_THROW(const auto path = file(lfs_path));
}

TEST(lfs_file_path, always_consistent)
{
	const auto path = file(lfs_inconsistent_path);
	ASSERT_EQ(lfs_path, path.to_wstring());
}

TEST(lfs_file_path, to_wstring)
{;
	// ARRANGE
	const auto testee = file(lfs_path);
	// ACT
	const auto actual = testee.to_wstring();
	// ASSERT
	ASSERT_EQ(lfs_path, actual);
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
