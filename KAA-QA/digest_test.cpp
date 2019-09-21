#include "gtest/gtest.h"

#include "../KAA/include/cryptography/md5.h"
#include "../KAA/include/exception/windows_api_failure.h"

using namespace KAA::cryptography;

TEST(calculate_md5, data)
{
	{
		const auto data = std::string { "md5" };
		const auto digest = calculate_md5(data.c_str(), sizeof(decltype(data)::value_type) * data.length());
		const auto benchmark = md5_t { 0x82ba23f6369bc21b, 0x1867b1d34f72f6aa };
		EXPECT_EQ(benchmark, digest);
	}
	{
		const auto data = std::string { "md4" };
		const auto digest = calculate_md5(data.c_str(), sizeof(decltype(data)::value_type) * data.length());
		const auto benchmark = md5_t { 0xe9afc4a7f73b3dc9, 0x4f9fe32c0ce3644b };
		EXPECT_EQ(benchmark, digest);
	}
}

TEST(calculate_md5, null)
{
	const auto digest = calculate_md5(nullptr, 0);
	const auto benchmark = md5_t { 0x04b2008fd98c1dd4, 0x7e42f8ec980980e9 };
	EXPECT_EQ(benchmark, digest);
}

TEST(md5, empty)
{
	md5 digest;
	constexpr auto benchmark = md5_t { 0x04b2008fd98c1dd4, 0x7e42f8ec980980e9 };
	ASSERT_EQ(benchmark, digest.complete());
}

TEST(md5, constructor)
{
	md5 digest { {'m', 'd', '5'} };
	constexpr auto benchmark = md5_t { 0x82ba23f6369bc21b, 0x1867b1d34f72f6aa };
	ASSERT_EQ(benchmark, digest.complete());
}

TEST(md5, add_data)
{
	constexpr auto benchmark = md5_t { 0x82ba23f6369bc21b, 0x1867b1d34f72f6aa };
	{
		md5 digest;
		digest.add_data({'m', 'd', '5'});
		EXPECT_EQ(benchmark, digest.complete());
	}
	{
		md5 digest;
		digest.add_data({'m'});
		digest.add_data({'d'});
		digest.add_data({'5'});
		EXPECT_EQ(benchmark, digest.complete());
	}
}

TEST(md5, complete)
{
	md5 digest;
	digest.complete();
	EXPECT_THROW(digest.add_data({'m', 'd', '5'}), KAA::windows_api_failure);
}
