#include "gtest/gtest.h"

#include "../KAA/include/cryptography/random.h"
#include "../KAA/include/filesystem/crt_file_system.h"
#include "../KAA/include/filesystem/filesystem.h"
#include "../KAA/include/filesystem/path.h"

namespace
{
	const KAA::filesystem::path::file none(L"./bin/none.bin");
	const KAA::filesystem::path::file kibibyte(L"./bin/KiB.bin");

	const KAA::filesystem::driver::mode read_attributes_only(false, false);
	const KAA::filesystem::driver::mode sequential_binary_read_only(false, true);
	const KAA::filesystem::driver::mode sequential_binary_write_only(true, false);
	const KAA::filesystem::driver::mode sequential_binary_read_write(true, true);

	const KAA::filesystem::driver::share share_any_access;
}

using namespace KAA::filesystem;

TEST(file, get_size)
{
	crt_file_system filesystem;
	auto file = filesystem.open_file(kibibyte, read_attributes_only, share_any_access);
	EXPECT_EQ(1024U, file->get_size());
}

TEST(filesystem, file_exists)
{
	crt_file_system filesystem;
	EXPECT_FALSE(file_exists(filesystem, none));
	EXPECT_TRUE(file_exists(filesystem, kibibyte));
}

TEST(filesystem, get_file_size)
{
	crt_file_system filesystem;
	EXPECT_EQ(1024U, get_file_size(filesystem, kibibyte));
}

TEST(filesystem, DISABLED_set_file_size)
{
	crt_file_system filesystem;
	const auto size = KAA::cryptography::random() % (1024U + 1U);
	const path::file empty = L"./bin/empty.bin";
	EXPECT_NO_THROW(set_file_size(filesystem, empty, size));
	ASSERT_EQ(size, get_file_size(filesystem, empty));
	set_file_size(filesystem, empty, 0U);
}
