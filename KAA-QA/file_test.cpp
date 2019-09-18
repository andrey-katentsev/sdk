#include "gtest/gtest.h"

#include "../KAA/include/filesystem/crt_file_system.h"
#include "../KAA/include/filesystem/path.h"

namespace
{
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
