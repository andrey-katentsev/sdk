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
