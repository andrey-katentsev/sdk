#include "gtest/gtest.h"

#include "../KAA/include/convert.h"

using namespace KAA::convert;

TEST(convert, long_to_wstring)
{
	constexpr auto zero = 0L;
	constexpr auto one = 1L;
	constexpr auto minus_one = -1L;
	constexpr auto positive = 128L;
	constexpr auto negative = -128L;

	EXPECT_EQ(std::wstring { L"0" }, to_wstring(zero));
	EXPECT_EQ(std::wstring { L"1" }, to_wstring(one));
	EXPECT_EQ(std::wstring { L"-1" }, to_wstring(minus_one));
	EXPECT_EQ(std::wstring { L"128" }, to_wstring(positive));
	EXPECT_EQ(std::wstring { L"-128" }, to_wstring(negative));
}

TEST(convert, long_to_wstring_hex)
{
	enum { hex = 16 };
	constexpr auto zero = 0L;
	constexpr auto one = 1L;
	constexpr auto minus_one = -1L;
	constexpr auto positive = 128L;
	constexpr auto negative = -128L;

	EXPECT_EQ(std::wstring { L"0" }, to_wstring(zero, hex));
	EXPECT_EQ(std::wstring { L"1" }, to_wstring(one, hex));
	EXPECT_EQ(std::wstring { L"ffffffff" }, to_wstring(minus_one, hex));
	EXPECT_EQ(std::wstring { L"80" }, to_wstring(positive, hex));
	EXPECT_EQ(std::wstring { L"ffffff80" }, to_wstring(negative, hex));
}

TEST(convert, wstring_to_long)
{
	const auto zero = std::wstring { L"0" };
	const auto one = std::wstring { L"1" };
	const auto minus_one = std::wstring { L"-1" };
	const auto positive = std::wstring { L"128" };
	const auto negative = std::wstring { L"-128" };

	EXPECT_EQ(0L, to_long(zero));
	EXPECT_EQ(1L, to_long(one));
	EXPECT_EQ(-1L, to_long(minus_one));
	EXPECT_EQ(128L, to_long(positive));
	EXPECT_EQ(-128L, to_long(negative));
}

TEST(convert, hex_wstring_to_long)
{
	const auto minus_one = std::wstring { L"ffffffff" };
	const auto positive = std::wstring { L"a80" };
	const auto negative = std::wstring { L"fffffa80" };

	EXPECT_EQ(0L, to_long(minus_one));
	EXPECT_EQ(0L, to_long(positive));
	EXPECT_EQ(0L, to_long(negative));
}
