#include "gtest/gtest.h"

#include "../KAA/include/filesystem/in-memory_file_system.h"

using namespace KAA::filesystem;

TEST(in_memory_filesystem, create_directory)
{
	const auto directory = std::wstring { LR"(V:\root)" };
	in_memory_file_system filesystem;
	EXPECT_NO_THROW(filesystem.create_directory(directory));
	EXPECT_THROW(filesystem.create_directory(directory), std::logic_error);
}

TEST(in_memory_filesystem, remove_directory)
{
	const auto directory = std::wstring { LR"(V:\root)" };
	in_memory_file_system filesystem;
	filesystem.create_directory(directory);
	EXPECT_NO_THROW(filesystem.remove_directory(directory));
	EXPECT_THROW(filesystem.remove_directory(directory), std::logic_error);
}

TEST(in_memory_filesystem, get_temp_filename)
{
	const in_memory_file_system filesystem;
	const auto A = filesystem.get_temp_filename();
	const auto B = filesystem.get_temp_filename();
	const auto C = filesystem.get_temp_filename();
	EXPECT_NE(A, B);
	EXPECT_NE(A, C);
	EXPECT_NE(B, C);
}
