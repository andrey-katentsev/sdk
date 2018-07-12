#include "gtest/gtest.h"

#include "../KAA/include/md5.h"

using namespace KAA::cryptography;

TEST(md5, md5_ASCII)
{
	const auto data = std::string { "md5" };
	const auto digest = calculate_md5(data.c_str(), sizeof(decltype(data)::value_type) * data.length());
	const auto benchmark = md5 { 0x82ba23f6369bc21b, 0x1867b1d34f72f6aa };
	EXPECT_EQ(benchmark, digest);
}

TEST(md5, md4_ASCII)
{
	const auto data = std::string { "md4" };
	const auto digest = calculate_md5(data.c_str(), sizeof(decltype(data)::value_type) * data.length());
	const auto benchmark = md5 { 0xe9afc4a7f73b3dc9, 0x4f9fe32c0ce3644b };
	EXPECT_EQ(benchmark, digest);
}

TEST(md5, null)
{
	const auto digest = calculate_md5(nullptr, 0);
	const auto benchmark = md5 { 0x04b2008fd98c1dd4, 0x7e42f8ec980980e9 };
	EXPECT_EQ(benchmark, digest);
}

TEST(md5, to_wstring)
{
	{
		constexpr auto digest = md5 { 0x82ba23f6369bc21b, 0x1867b1d34f72f6aa };
		EXPECT_EQ(std::wstring { L"1bc29b36f623ba82aaf6724fd3b16718" }, to_wstring(digest));
	}
	{
		constexpr auto digest = md5 { 0xe9afc4a7f73b3dc9, 0x4f9fe32c0ce3644b };
		EXPECT_EQ(std::wstring { L"c93d3bf7a7c4afe94b64e30c2ce39f4f" }, to_wstring(digest));
	}
	{
		constexpr auto digest = md5 { 0x04b2008fd98c1dd4, 0x7e42f8ec980980e9 };
		EXPECT_EQ(std::wstring { L"d41d8cd98f00b204e9800998ecf8427e" }, to_wstring(digest));
	}
}
