#include "gtest/gtest.h"

#include "../KAA/include/exception/system_failure.h"
#include "../KAA/include/filesystem/crt_file_system.h"
#include "../KAA/include/filesystem/path.h"

using namespace KAA::filesystem;

TEST(crt_filesystem, create_directory)
{
	const auto path = path::directory { LR"(.\crt_create_directory_test)" };
	crt_file_system filesystem;
	EXPECT_NO_THROW(filesystem.create_directory(path));
	EXPECT_THROW(filesystem.create_directory(path), KAA::system_failure);
	filesystem.remove_directory(path);
}

TEST(crt_filesystem, remove_directory)
{
	const auto path = path::directory { LR"(.\crt_remove_directory_test)" };
	crt_file_system filesystem;
	filesystem.create_directory(path);
	EXPECT_NO_THROW(filesystem.remove_directory(path));
	EXPECT_THROW(filesystem.remove_directory(path), KAA::system_failure);
}

TEST(crt_filesystem, create_file)
{
	const auto path = path::file { LR"(.\crt_create_file_test.dat)" };
	crt_file_system filesystem;
	driver::create_mode new_persistent_file;
	driver::mode sequential_binary_read_write;
	driver::share share_any_access;
	driver::permission full_access;
	EXPECT_NO_THROW(filesystem.create_file(path, new_persistent_file, sequential_binary_read_write, share_any_access, full_access));
	EXPECT_THROW(filesystem.create_file(path, new_persistent_file, sequential_binary_read_write, share_any_access, full_access), KAA::system_failure);
	filesystem.remove_file(path);
}

TEST(crt_filesystem, get_temp_filename)
{
	const driver::create_mode new_persistent_file;
	const driver::mode sequential_binary_read_write;
	const driver::share share_any_access;
	const driver::permission full_access;
	const auto root = path::directory { L"." };
	crt_file_system filesystem;
	const auto A = filesystem.get_temp_filename(root);
	{ auto file = filesystem.create_file(A, new_persistent_file, sequential_binary_read_write, share_any_access, full_access); }
	const auto B = filesystem.get_temp_filename(root);
	{ auto file = filesystem.create_file(B, new_persistent_file, sequential_binary_read_write, share_any_access, full_access); }
	const auto C = filesystem.get_temp_filename(root);
	filesystem.delete_file(A);
	filesystem.delete_file(B);
	EXPECT_NE(A, B);
	EXPECT_NE(A, C);
	EXPECT_NE(B, C);
}

TEST(crt_filesystem, rename_file)
{
	const auto from = path::file { LR"(.\crt_rename_file_test.dat)" };
	const auto to = path::file { LR"(.\crt_rename_file_test.bin)" };
	crt_file_system filesystem;
	driver::create_mode new_persistent_file;
	driver::mode sequential_binary_read_write;
	driver::share share_any_access;
	driver::permission full_access;
	filesystem.create_file(from, new_persistent_file, sequential_binary_read_write, share_any_access, full_access);
	EXPECT_NO_THROW(filesystem.rename_file(from, from));
	EXPECT_NO_THROW(filesystem.rename_file(from, to));
	EXPECT_THROW(filesystem.rename_file(from, to), KAA::system_failure);
	filesystem.remove_file(to);
}

TEST(crt_filesystem, remove_file)
{
	const auto path = path::file { LR"(.\crt_remove_file_test.dat)" };
	crt_file_system filesystem;
	driver::create_mode new_persistent_file;
	driver::mode sequential_binary_read_write;
	driver::share share_any_access;
	driver::permission full_access;
	filesystem.create_file(path, new_persistent_file, sequential_binary_read_write, share_any_access, full_access);
	EXPECT_NO_THROW(filesystem.remove_file(path));
	EXPECT_THROW(filesystem.remove_file(path), KAA::system_failure);
}

TEST(crt_filesystem, file_exists)
{
	const auto path = path::file { LR"(.\crt_file_exists_test.dat)" };
	crt_file_system filesystem;
	EXPECT_FALSE(filesystem.file_exists(path));
	{
		driver::create_mode new_persistent_file;
		driver::mode sequential_binary_read_write;
		driver::share share_any_access;
		driver::permission full_access;
		auto file = filesystem.create_file(path, new_persistent_file, sequential_binary_read_write, share_any_access, full_access);
	}
	ASSERT_TRUE(filesystem.file_exists(path));
	filesystem.remove_file(path);
	ASSERT_FALSE(filesystem.file_exists(path));
}
