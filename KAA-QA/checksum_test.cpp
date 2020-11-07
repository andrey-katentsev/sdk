#include "gtest/gtest.h"

#include "../KAA/include/checksum.h"

using namespace KAA::checksum;

TEST(CRC32, IEEE)
{
	const auto polynomial = 0x04c11db7;
	{
		const auto data = std::vector<uint8_t>(1U, 0);
		auto checksum = crc32(data.data(), data.size(), polynomial);
		const auto benchmark = 0xfa60fb57;
		EXPECT_EQ(benchmark, checksum);
	}
	{
		const auto data = std::vector<uint8_t>(1U, 1);
		auto checksum = crc32(data.data(), data.size(), polynomial);
		const auto benchmark = 0xfc43cdc0;
		EXPECT_EQ(benchmark, checksum);
	}
}
