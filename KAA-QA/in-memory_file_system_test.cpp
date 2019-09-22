#include "gtest/gtest.h"

#include "../KAA/include/filesystem/in-memory_file_system.h"

using namespace KAA::filesystem;

TEST(in_memory_filesystem, create_directory)
{
	const auto path = path::directory { LR"(V:\root)" };
	in_memory_file_system filesystem;
	EXPECT_NO_THROW(filesystem.create_directory(path));
	EXPECT_THROW(filesystem.create_directory(path), std::runtime_error);
	filesystem.remove_directory(path);
}

TEST(in_memory_filesystem, remove_directory)
{
	const auto path = path::directory { LR"(V:\root)" };
	in_memory_file_system filesystem;
	filesystem.create_directory(path);
	EXPECT_NO_THROW(filesystem.remove_directory(path));
	EXPECT_THROW(filesystem.remove_directory(path), std::runtime_error);
}

TEST(in_memory_filesystem, create_file)
{
	const auto path = path::file { LR"(A:\directory\file.dat)" };
	in_memory_file_system filesystem;
	driver::create_mode new_persistent_file;
	driver::mode sequential_binary_read_write;
	driver::share share_any_access;
	driver::permission full_access;
	EXPECT_NO_THROW(filesystem.create_file(path, new_persistent_file, sequential_binary_read_write, share_any_access, full_access));
	EXPECT_THROW(filesystem.create_file(path, new_persistent_file, sequential_binary_read_write, share_any_access, full_access), std::runtime_error);
	filesystem.remove_file(path);
}

TEST(in_memory_filesystem, get_temp_filename)
{
	const auto root = path::directory { LR"(V:\root)" };
	const in_memory_file_system filesystem;
	const auto A = filesystem.get_temp_filename(root);
	const auto B = filesystem.get_temp_filename(root);
	const auto C = filesystem.get_temp_filename(root);
	EXPECT_NE(A, B);
	EXPECT_NE(A, C);
	EXPECT_NE(B, C);
}

TEST(in_memory_filesystem, rename_file)
{
	const auto from = path::file { LR"(A:\directory\file.dat)" };
	const auto to = path::file { LR"(A:\directory\file.bin)" };
	in_memory_file_system filesystem;
	driver::create_mode new_persistent_file;
	driver::mode sequential_binary_read_write;
	driver::share share_any_access;
	driver::permission full_access;
	filesystem.create_file(from, new_persistent_file, sequential_binary_read_write, share_any_access, full_access);
	EXPECT_THROW(filesystem.rename_file(from, from), std::runtime_error);
	EXPECT_NO_THROW(filesystem.rename_file(from, to));
	EXPECT_THROW(filesystem.rename_file(from, to), std::runtime_error);
	filesystem.remove_file(to);
}

TEST(in_memory_filesystem, remove_file)
{
	const auto path = path::file { LR"(A:\directory\file.dat)" };
	in_memory_file_system filesystem;
	driver::create_mode new_persistent_file;
	driver::mode sequential_binary_read_write;
	driver::share share_any_access;
	driver::permission full_access;
	filesystem.create_file(path, new_persistent_file, sequential_binary_read_write, share_any_access, full_access);
	EXPECT_NO_THROW(filesystem.remove_file(path));
	EXPECT_THROW(filesystem.remove_file(path), std::runtime_error);
}

TEST(in_memory_filesystem, file_exists)
{
	const auto path = path::file { LR"(V:\directory\file.dat)" };
	in_memory_file_system filesystem;
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
